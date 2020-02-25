#include <bits/stdc++.h>
using namespace std;

const int N = 5e4;
int n, m;
vector<int> adj[N];
bool vis[N];

int dfsReach(int v) {
	int ans = 1;
	vis[v] = 1;
	for (int w : adj[v])
		if (!vis[w])
			ans += dfsReach(w);
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>m;
	for (int i =0 ;i < m; i++) {
		int x, y; cin>>x>>y;
		adj[--y].push_back(--x);
	}

	long long ans = 0;
	for (int i = 0; i < n; i++) if (!vis[i]) {
		int sz = dfsReach(i)
		ans += 1LL*sz*(sz-1);
	}
	cout << ans << endl;
	
	return 0;
}
