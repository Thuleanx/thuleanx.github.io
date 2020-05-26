
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

const int oo = 1e9+7;
const ll loo = 1e18;

ll modpow(ll a, ll b, ll mod = oo) {
	ll res = 1;
	while (b) {
		if (b&1) res = res*a%mod;
		a = a*a%mod;
		b /=2;
	}
	return res;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// use uniform_int_distribution<int>(0, i)(rng)

ll pq, x, m;

int solve() {
	
	cin>>pq>>x>>m;

	for (ll p = 0; p < m; p++) {
		ll q = modpow(pq*modpow(p, m-2,m)%m, m-2, m);
		if (q == 0) q = 1;
		if (p * modpow(q,m-2,m) % m == pq && p >= x*q && p < (x+1) * q) {
			cout << p << " " << q << endl;
			return 0;
		}
	}
	cout << -1 << endl;

	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	solve();

	return 0;
}
