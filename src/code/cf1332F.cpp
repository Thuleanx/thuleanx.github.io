#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple

using ll = long long;

const int mod = 998244353, N = 3e5+7;
int n;
ll dp[N][2][2];
vector<int> adj[N];

void run(int v, int p) {
	for (int w : adj[v]) if (w != p) 
		run(w, v);
	f(j,0,2) f(k,0,2) dp[v][j][k] = 1;
	for (int w : adj[v]) if (w != p) {
	// 00	
		dp[v][0][0] = dp[v][0][0] * ((dp[w][0][0] + dp[w][0][1] + dp[w][1][1]) % mod) % mod;
	// 10
		dp[v][1][0] = dp[v][1][0] * ((dp[w][0][0] + dp[w][0][1] + dp[w][1][1]) % mod) % mod;
	// 01
		dp[v][0][1] = dp[v][0][1] * ((2*dp[w][0][0] + 2*dp[w][0][1] + dp[w][1][0] + 2*dp[w][1][1])%mod) % mod;
	// 11
		dp[v][1][1] = dp[v][1][1] * ((2*dp[w][0][0] + 2*dp[w][0][1] + dp[w][1][1])%mod) % mod;
	}
	dp[v][0][1] += mod-dp[v][0][0];
	dp[v][1][1] += mod-dp[v][1][0];
	f(j,0,2) f(k,0,2)
		dp[v][j][k] %= mod;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n;
	f(i,0,n-1) {
		int x,y; cin>>x>>y;
		adj[--x].push_back(--y);
		adj[y].push_back(x);
	}
	run(0,-1);

	ll ans = (mod + dp[0][0][0] + dp[0][0][1] + dp[0][1][1] - 1) % mod;
	cout << ans << endl;


	return 0;
}
