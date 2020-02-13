#include <bits/stdc++.h>
using namespace std;

const int N = 2e5;
int n,m,T;
bool vis[N];
vector<int> adj[N], rev[N], can;

void dfs(int v) {
	vis[v] = 1;
	for (int w : adj[v]) if (!vis[w] && w != T)
		dfs(w);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>m>>T;

	for (int i = 0; i < m; i++) {
		int v, w; cin>>v>>w;
		if (w == T) can.push_back(v);

		rev[v].push_back(w);
		adj[w].push_back(v);
	}

	for (int v : can)
		for (int w : adj[v]) if (w != T && !vis[w])
			dfs(w);


	stringstream ss;
	int cnt = 0;

	sort(begin(can),end(can));


	for (int v : can) if (!vis[v]) {
		cnt++;
		ss << v << endl;
	}


	cout << cnt << endl << ss.str();



	return 0;
}
