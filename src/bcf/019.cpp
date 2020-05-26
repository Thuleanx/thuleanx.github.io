
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

const int N = 5e2, R = 1e4;
int n, m, k;
vi adj[N];
ld p[N][R], c[N][R];

void solve() {
	cin>>n>>m;

	f(i,0,m) {
		int x,y; cin>>x>>y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	cin>>k;

	f(i,0,N) f(j,0,R) c[i][j] = loo;

	f(i,0,k) {
		int x; cin>>x;
		p[x][0] = 1;
	}

	c[0][0] = p[0][0];

	ld ans = c[n-1][0];

	f(z,0,R-1) {
		f(i,0,n) for (int w : adj[i]) 
			p[w][z+1] += p[i][z] / (adj[i].size());
		f(i,0,n) for (int w : adj[i]) 
			c[w][z+1] = min(c[w][z+1], c[i][z] + p[w][z+1]);
		ans = min(ans, c[n-1][z+1]);
	}

	cout << setprecision(40) << ans << endl;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	solve();

	return 0;
}
