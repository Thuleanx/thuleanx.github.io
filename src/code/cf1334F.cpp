
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

ll modpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b&1) res = res*a%oo;
		a = a*a%oo;
		b /=2;
	}
	return res;
}

const int N = 5e5;
struct BIT {
	ll tree[N];
	BIT() {
		f(i,0,N) tree[i] = 0;
	}
	void add(int i, ll b) {
		for (; i >= 0; i = (i&(i+1))-1)
			tree[i] += b;
	}
	ll sum(int i) {
		ll res = 0;
		for (; i < N; i |= i+1) res += tree[i];
		return res;
	}
};

int n, m;
int id[N];
ll a[N], p[N], b[N], fi[N], prex[N];
unordered_map<ll,ll> dp;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n;
	f(i,0,n) cin>>a[i];
	f(i,0,n) cin>>p[i];
	cin>>m;
	f(i,0,m) cin>>b[i];
	prex[0] = 0;
	f(i,1,n) prex[i] = prex[i-1]+a[i-1];

	f(i,0,n) id[i] = std::lower_bound(b, b+m, a[i]) - b;

	BIT ds;
	ll res = loo;
	dp[m] = 0;
	fr(i,0,n) {
		if (id[i] != m && b[id[i]] == a[i] && dp.count(id[i]+1)) {
			int j = id[i];
			ll ask = dp[i+1] + 

		} else fi[i] = -1;
		ds.add(id[i]-1, p[i]);
	}
	if (dp.count(0))
		res = dp[0] + ds.sum(0);

	if (res < loo) {
		cout << "YES" << endl;
		cout << res << endl;
	} else cout << "NO" << endl;


	return 0;
}
