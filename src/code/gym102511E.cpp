#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define mp make_pair

const int N = 5e5;
int n,m,t;
vector<int> adj[N], g[N];
bool bridge[N], vis[N], rem[N];
int a[N], b[N], dsu[N], sz[N], arr[N], wi[N];

int root(int x) { return dsu[x] == x ? x : root(dsu[x]); }
void merge(int a, int b) {
	a = root(a); b = root(b);
	if (sz[a] < sz[b]) swap(a,b);
	dsu[b] = a; sz[a] += sz[b];
}
int dfs0(int v, int ee) {
	vis[v] = 1;
	arr[v] = t++;
	int dbe = arr[v];
	for (int e : adj[v]) {
		int w = a[e]^b[e]^v;
		if (!vis[w]) dbe = min(dbe, dfs0(w,e));
		else if (e != ee) dbe = min(dbe, arr[w]);
	}
	if (dbe == arr[v] && ee != -1) bridge[ee] = 1;
	else if (ee != -1) merge(a[ee], b[ee]);
	return dbe;
}
void build() {
	f(i,0,n) dsu[i] = i, sz[i] = 1;
	f(i,0,n) if (!vis[i]) dfs0(i,-1);
	f(e,0,m) if (root(a[e]) != root(b[e])) {
		g[root(a[e])].push_back(e);
		g[root(b[e])].push_back(e);
	}
}

void dfs1(int v, vector<int> &edges, vector<int> &lone) {
	vis[v] = 1;
	lone.push_back(v);
	for (int e : adj[v]) {
		int w = a[e]^b[e]^v;
		int ww = root(w);
		if (sz[ww] > 1)
			edges.push_back(e);
		else if (!vis[ww]) dfs1(ww, edges, lone);
	}
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>m;
	f(e,0,m) {
		cin>>a[e]>>b[e];
		adj[--a[e]].push_back(e);
		adj[--b[e]].push_back(e);
	}
	f(i,0,n) wi[i] = adj[i].size();
	build();
	f(i,0,N) vis[i] = 0;

	vector<pair<int,int>> res;
	f(i,0,n) if (sz[root(i)] == 1 && !vis[i]) {
		vector<int> edges, lone;
		dfs1(i,edges,lone);
		if (edges.size() == 1) {
			int e = edges[0];
			if (vis[b[e]]) swap(a[e], b[e]);
			res.push_back(mp(b[e], a[e]));
		} else if (!edges.size()) {
			for (int v : lone) if (adj[v].size() == 1) {
				for (int e : adj[v]) {
					int w = a[e]^b[e]^v;
					res.push_back(mp(v,w));
				}
			}
		} else {
			queue<int> pq;
			for (int x : lone) if (adj[x].size() == 1) pq.push(x);
			while (pq.size()) {
				int v = pq.front(); pq.pop();
				rem[v] = 1;
				for (int e : adj[v]) {
					int w = a[e]^b[e]^v;
					if (--wi[w] == 1) pq.push(w);
				}
			}
			for (int v : lone) if (!rem[v]) {
				for (int e : adj[v]) {
					int w = a[e]^b[e]^v;
					if (rem[w]) res.push_back(mp(v,w));
				}
			}

		}
	}
	sort(begin(res),end(res));

	stringstream ss;
	ss << res.size() << endl;
	for (auto pp : res) {
		int v = pp.first, w = pp.second;
		ss << v+1 << " " << w+1 << endl;
	}
	cout << ss.str();

				

	return 0;
}
