#include <bits/stdc++.h>
using namespace std;

#define IN(i,a,b) (a<=i && i<=b)

const int N = 1e5;
int n, t = 0, q;
int l[N], r[N];
vector<int> adj[N];

void dfs(int v, int p) {
	l[v] = t++;
	for (int w : adj[v]) if (w != p)
		dfs(w, v);
	r[v] = t++;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>q;
	for (int i = 0;i  < n-1; i++) {
		int v, w; cin>>v>>w;
		adj[--v].push_back(--w);
		adj[w].push_back(v);
	}

	dfs(0, -1);

	stringstream ss;
	while (q--) {
		int a,b,c,d; cin>>a>>b>>c>>d; 
		a--; b--; c--; d--;
	}
	cout << ss.str();


	return 0;
}
