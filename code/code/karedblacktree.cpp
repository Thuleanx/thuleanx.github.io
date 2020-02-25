#include <bits/stdc++.h>
using namespace std;

const int N = 2e5, M = 300, mod = 1e9+7;
int n, m;
bool red[N], vis[N];
vector<int> adj[N];

vector<int> comb(vector<int> &a, vector<int> &b) {
	int sa = a.size(), sb = b.size();
	vector<int> sol(sa+sb-1);
	for (int i = 0; i < sa; i++)
		for (int j = 0; j < sb; j++)
			sol[i+j] = (sol[i+j] + 1LL*a[i]*b[j])%mod;
	return sol;
}

vector<int> add(vector<int> a, vector<int> b) {
	vector<int> c(a.size());
	for (int i = 0; i < a.size(); i++)
		c[i] = a[i] + b[i];
	return c;
}

vector<vector<int>> run(int v) {
	vector<vector<int>> dp(2, vector<int>(2,0));
	dp[0][0] = dp[1][1] = 1;
	vis[v] = 1;

	for (int w : adj[v]) if (!vis[v] && red[w]) {
		vector<vector<int>> dp2 = run(w);

		// res[0] = comb(dp[0], dp2[0]) + comb(dp[0], dp2[1])
		// res[1] = comb(dp[1], dp2[0])
		
		vector<vector<int>> res(2);
		res[0] = add(comb(dp[0], dp2[0]), comb(dp[0], dp2[1]));
		res[1] = comb(dp[1], dp2[0]);

		dp = res;
	}

	return dp;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin>>n>>m;
	for (int i = 1; i < n; i++) {
		int p; cin>>p; p--;
		adj[p].push_back(i);
		adj[i].push_back(p);
	}

	for (int i = 0; i < m; i++) {
		int c; cin>>c;
		red[--c] = 1;
	}

	vector<int> sol(m+1,0);
	for (int i = 0; i < n; i++) if (red[i] && !vis[i]) {
		vector<vector<int>> dp = run(i);
		sol = add(sol, dp[0]);
		sol = add(sol, dp[1]);
	}

	stringstream ss;
	for (int i = 0; i <= m; i++)
		ss << sol[i] << " \n"[i==m];
	cout << ss.str();

	return 0;
}
