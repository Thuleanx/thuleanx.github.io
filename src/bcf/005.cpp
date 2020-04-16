// 1105E https://codeforces.com/problemset/problem/1105/E
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

const int N = 40, NH = 20;
int n,m;

unordered_map<ll, int> rev;
int dp[1<<NH][2];
ll gr;
ll adj[N];
map<string, int> id;

int gen(string s) {
	if (id.count(s)) return id[s];
	int sz = id.size();
	id[s] = sz;
	return sz;
}

int run(ll mask, int j) {
	if (dp[mask][j] != -1) return dp[mask][j];
	ll s = mask&-mask;
	ll xans = j?adj[rev[s]+n/2]>>n/2 : adj[rev[s]];
	return dp[mask][j] = max(run(mask - s, j), 1 + run(mask - (mask&xans), j));
}

int solve() {
	cin>>m>>n;
	f(i,0,n) rev[1LL<<i]=i;
	f(i,0,n) adj[i] = 1LL<<i;
	while (m--) {
		int tp; cin>>tp;
		if (tp == 2) {
			string s; cin>>s;
			gr |= 1LL << gen(s);
		} else {
			f(z,0,n) if (gr >> z & 1)
				adj[z] |= gr;
			gr = 0;
		}
	}
	f(z,0,n) if (gr >> z & 1)
		adj[z] |= gr;
	f(i,0,1<<NH) f(j,0,2) dp[i][j] = -1;

	dp[0][0] = dp[0][1] = 0;
	int ans = 0;
	f(i,0,1LL<<n/2) if (run(i,0) == __builtin_popcountll(i)) {
		ll tot = i;
		f(j,0,n/2) if (i>>j&1) tot |= adj[j];
		tot |= (1LL<<(n/2))-1;	
		tot = (1LL<<n)-1-tot;
		ans=max(ans,run(i,0) + run(tot>>n/2,1));
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

