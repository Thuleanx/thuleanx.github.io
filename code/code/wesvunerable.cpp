#include <bits/stdc++.h>
using namespace std;

const int N = 10000;
int n, m;
bool vis[N];
vector<int> adj[N];

int dfs(int v) {
	int ans = 1;
	vis[v] = 1;
	for (int w : adj[v]) if (!vis[w])
		ans += dfs(w);
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>m;
	for (int i = 0; i < m; i++) {
		int a, b; cin>>a>>b;
		adj[--a].push_back(--b);
		adj[b].push_back(a);
	}

	long long res = 0;
	for (int v = 0; v < n; v++) {
		memset(vis, 0, sizeof(vis));
		vis[v] = 1;
		
		vector<long long> sz;
		for (int w : adj[v]) if (!vis[w])
			sz.push_back(dfs(w));

		long long c = 0;
		for (long long x : sz) {
			res += c*x; c += x;
		}
	}

	cout << 2*res << endl;
	

	return 0;
}
