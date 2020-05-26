
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
const ll loo = 1e18+3;

ll modpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b&1) res = res*a%loo;
		a = a*a%loo;
		b /= 2;
	}
	return res;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// use uniform_int_distribution<int>(0, i)(rng)

const int N = 1e6;
ll n, k;
vi adj[N];

ll choose2(ll n) {
	return n*(n-1)/2;
}

ll choose3(ll n) {
	return 1LL*(n)*(n-1)*(n-2)/6;
}

int solve() {
	cin>>n>>k;
	f(i,0,k) {
		int x, y; cin>>x>>y;
		adj[--x].push_back(--y);
		adj[y].push_back(x);
	}


	ll ans = choose3(n) - 1LL * (n-2) * k;
	f(i,0,n) ans += choose2(adj[i].size());
	cout << ans << endl;

	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	solve();

	return 0;
}
