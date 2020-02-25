#include <bits/stdc++.h>
using namespace std;

const int N = 1e5, M = 40;
int n, m;
bool vis[M], matched[M];
map<string, int> names;
bool edges[M][M];
vector<pair<int,int>> ee;
vector<int> adj[M];

int dfs(int i, vector<pair<int,int>> matching, bool vis[]) {
	if (i == matching.size()) {
		int cnt = 0;
		for (int j = 0; j < m; j++) cnt += vis[j];
		for (int j = 0; j < m; j++) if (!matched[j]) {
			bool include = 1;
			for (int k : adj[j]) include &= !vis[k];
			cnt += include;
		}
		return cnt;
	}

	int x = matching[i].first, y = matching[i].second;
	vis[x] = 1; vis[y] = 0;
	int best = dfs(i+1, matching, vis);
	vis[x] = 0; vis[y] = 1;
	best = max(best, dfs(i+1,matching,vis));
	vis[x] = vis[y] = 0;
	best = max(best, dfs(i+1,matching,vis));

	return best;
}



int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>m;	
	int p = 0;
	for (int i = 0; i < n; i++) {
		int tp; cin>>tp;
		if (tp == 2) {
			string s; cin>>s;
			if (!names.count(s))
				names[s] = p++;
			vis[names[s]] = 1;
		}
		if (tp == 1 || i == n-1) {
			for (int j = 0; j < m; j++)
				for (int k = 0; k < m; k++)
					if (vis[j] && vis[k] && j != k)
						edges[j][k] = 1;
			for (int j = 0; j < m; j++)
				vis[j] = 0;
		}
	}

	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			if (edges[i][j] && i < j) {
				ee.push_back(pair<int,int>(i,j));
				cout << i << " " << j << endl;
				adj[i].push_back(j);
				adj[j].push_back(i);
			}

	vector<pair<int,int>> matching;
	for (auto pp : ee) {
		if (!matched[pp.first] && !matched[pp.second]) {
			matching.push_back(pp);
			matched[pp.first] = matched[pp.second] = 1;
		}
	}

	cout << dfs(0, matching, vis) << endl;

	return 0;
}
