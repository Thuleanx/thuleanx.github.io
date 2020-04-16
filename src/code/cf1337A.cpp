
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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// use uniform_int_distribution<int>(0, i)(rng)

const int N = 2e5;
int n, k;
int subsz[N], dep[N];
vi adj[N];

int dfs(int v, int p) {
	dep[v] = p==-1?0:dep[p]+1;
	subsz[v] = 1;
	for (int w : adj[v]) if (w != p)
		subsz[v] += dfs(w,v);
	return subsz[v];
}

int solve() {
	cin>>n>>k;

	f(i,0,n-1) {
		int x,y; cin>>x>>y;
		adj[--x].push_back(--y);
		adj[y].push_back(x);
	}
	
	dfs(0,-1);

	vector<ll> pq;
	f(i,0,n) pq.push_back(dep[i] - subsz[i] + 1);
	sort(begin(pq),end(pq));


	ll ans = 0;
	while (k--) {
		ans += pq.back();
		pq.pop_back();
	}

	cout << ans << endl;

	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	solve();	

	return 0;
}
