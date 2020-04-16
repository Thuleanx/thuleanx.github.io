// 1322C https://codeforces.com/problemset/problem/1322/C
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

const int N = 5e5, K = 7;
int n,m;
int fid[N][K];
ll a[N];
vi adj[N], rev[N];
stringstream ss;

int solve() {
	cin>>n>>m;
	f(i,0,n) adj[i].clear(), rev[i].clear();
	
	f(i,0,n) cin>>a[i];
	f(i,0,n) f(j,0,K) fid[i][j] = i;
	f(i,0,n) f(j,0,K) swap(fid[i][j], fid[uniform_int_distribution<int>(0, i)(rng)][j]);

	map<array<ll,K>,ll> fi;
	f(i,0,m) {
		int x,y; cin>>x>>y;
		adj[--x].push_back(--y);
		rev[y].push_back(x);
	}
	
	ll g = 0;
	f(i,0,n) {
		array<ll,K> ash;
		f(j,0,K) ash[j] = 0;
		bool gd = 0;
		for (int w : rev[i]) {
			gd = 1;
			f(j,0,K) ash[j] ^= fid[w][j]+1;
		}
		if (gd) fi[ash] += a[i];
	}
	for (auto pp : fi) 
		g = gcd(g, pp.second);
	ss << g << endl;
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	while (t--) solve();
	cout << ss.str();

	return 0;
}
