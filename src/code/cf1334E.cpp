
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple
#define sz(a) a.size()

using ld = long double;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi  = vector<int>;

const int oo =  998244353;
const ll loo = 1e18;

ll modpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b&1) res = res*a%oo;
		a = a*a%oo;
		b /=2;
	}
	return res;
}

ll D;
unordered_map<ll,ll> pr;
vector<ll> prdiv;

const ll mod = 998244353;
const int N = 2e5;
ll fi[N], gi[N];

ll prime(ll a) {
	if (pr.count(a)) return pr[a];
	for (ll p : prdiv) if (a % p == 0)
		return pr[a] = p;
	return 0;
}

ll gcd(ll a, ll b) { return a?gcd(b%a,a):b; }

ll paths(ll a) {
	ll ans = 1;
	int cnt = 0;
	while (a>1) {
		int subcnt = 0;
		ll p = prime(a);
		while (a%p==0) {
			subcnt++;
			a /= p;
		}
		ans = ans * gi[subcnt] % mod;
		cnt += subcnt;
	}
	ans = ans * fi[cnt] % mod;
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	fi[0] = 1;
	f(i,1,N) fi[i] = fi[i-1]*i%mod;
	gi[N-1] = modpow(fi[N-1], mod-2);
	fr(i,0,N-1) gi[i] = gi[i+1]*(i+1)%mod;

	cin>>D;	
	{
		ll M = D;
		for (ll j = 2; j*j <= M; j++) if (M%j==0) {
			while (M%j==0) M/=j;
			prdiv.push_back(j);
		}
		if (M) prdiv.push_back(M);
	}

	int q; cin>>q;
	stringstream ss;
	while (q--) {
		ll u, v; cin>>u>>v;
		ll g = gcd(u, v);
		ss << paths(u/g)*paths(v/g)%mod << endl;
	}
	cout << ss.str();


	return 0;
}
