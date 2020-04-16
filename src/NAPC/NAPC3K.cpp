
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple
#define sz(a) a.size()

using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi  = vector<int>;

const int oo = 1e9+7;
const ll ool = 1e18;

ll modpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b&1) res = res*a%oo;
		a = a*a%oo;
		b /=2;
	}
	return res;
}

template<class T> T maxflow(vector<unordered_map<int, T>> &graph, int source, int sink) {
	assert(source != sink);
	T flow = 0;
	vi par(sz(graph)), q = par;

	for (;;) {
		f(i,0,sz(graph)) par[i] = -1;
		par[source] = 0;
		int ptr = 1;
		q[0] = source;
		f(i,0,ptr) {
			int x = q[i];
			for (auto e : graph[x]) {
				if (par[e.first] == -1 && e.second > 0) {
					par[e.first] = x;
					q[ptr++] = e.first;
					if (e.first == sink) goto out;
				}
			}
		}
		return flow;
out: 
		T inc = numeric_limits<T>::max();
		for (int y = sink; y != source; y = par[y])
			inc = min(inc, graph[par[y]][y]);

		flow += inc;
		for (int y = sink; y != source; y = par[y]) {
			int p = par[y];
			if ((graph[p][y] -= inc) <= 0) graph[p].erase(y);
			graph[y][p] += inc;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n; cin>>n;
	vector<unordered_map<int, ll>> graph(2*n+2);

	int ff[2*n], d[2*n], c[2*n], mark[2*n];
	bool vis[2*n], cyc[2*n], tut[2*n];
	f(i,0,2*n) d[i] = tut[i] = cyc[i] = vis[i] = 0, mark[i] = 0, c[i] = 3;
	f(i,0,2*n) {
		cin>>ff[i]; ff[i]--;
		d[ff[i]]++;
	}

	f(i,0,2*n) {
		vector<int> g;
		int x = -1;
		for (int j = i; !vis[j]; j = ff[j]) {
			vis[j] = 1;
			g.push_back(j);
			if (vis[ff[j]]) x = ff[j];
		}
		if (find(g.begin(), g.end(), x) != g.end()) {
			int y = -1;
			do {
				y = g.back(); g.pop_back();
				cyc[y] = 1;
			} while (y != x);
		}
	}

	queue<int> pq;
	f(i,0,2*n) if (d[i] == 0) {
		pq.push(i);
	}
	while (pq.size()) {
		int v = pq.front(); pq.pop();
		c[v] = !mark[v];
		if (c[v]) mark[ff[v]]++;

		if (--d[ff[v]] == 0 || cyc[ff[v]]) {
			if (!cyc[ff[v]]) pq.push(ff[v]);	
			else if (c[v]) tut[ff[v]] = 1, c[ff[v]] = 0;	
		}
	}
	
	f(i,0,2*n) if (tut[i]) {
		for (int z = 1, j = ff[i]; !tut[j]; j = ff[j], z ^= 1)
			c[j] = z;
	}

	f(i,0,2*n) if (c[i] == 3) 
		for (int z = 1, j = ff[i]; c[j] == 3; j = ff[j], z ^= 1)
			c[j] = z;

	stringstream ss;
	f(i,0,2*n) if (c[i]) ss << i+1 << " ";
	cout << ss.str();

	return 0;
}
