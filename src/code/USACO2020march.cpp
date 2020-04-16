#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;

const int N = 2e5;
int n, m;
vi adj[N];
int dsu[N], sz[N], low[N];
void init() {
	f(i,0,N) dsu[i] = i, sz[i] = 1, low[i] = i;
}
int root(int v) { return dsu[v] = dsu[v] == v ? v : root(dsu[v]); }
void merge(int i, int j) {
	i = root(i); j = root(j);
	if (i == j) return; 
	if (sz[i] < sz[j]) swap(i, j);
	dsu[j] = i; sz[i] += sz[j];

	low[i] = min(low[i], low[j]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	/* freopen("haircut.in", "r", stdin); */
	/* freopen("haircut.out", "w", stdout); */

	cin>>n>>m;
	f(i,0,m) {
		int a, b; cin>>a>>b;
		adj[--b].push_back(--a);
	}
	init();
	f(i,0,n) if (adj[i].size()) {
		int w = adj[i][0];
		for (int ww : adj[i]) if (ww != w) merge(ww, w);
	}

	map<int,int> col;
	vector<pii> ds;
	f(i,0,n) if (dsu[i] == i)
		ds.push_back(pii(low[i], i));
	sort(begin(ds),end(ds));

	int p = 0;
	for (auto pp : ds) col[pp.second] = ++p;

	stringstream ss;
	f(i,0,n) ss << col[root(i)] << endl;
	cout << ss.str();

	return 0;
}
