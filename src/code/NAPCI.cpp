
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple
#define sz(a) a.size()

using ll = long long;
using vi = vector<int>;

const int mod = 1e9+7;  
ll modpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b&1) res = res*a%mod;
		a = a*a%mod;
		b /=2;
	}
	return res;
}

ll maxflow(vector<unordered_map<int, ll>>& graph, int source ,int sink) {
	assert(source != sink);
	ll flow = 0;

	vi par(sz(graph)), q = par; 

	for (;;) {
		f(i,0,par.size()) par[i] = -1;
		par[source] = 0;
		int ptr = 1;
		q[0] = source;


		f(i,0,ptr) {
			int x = q[i];
			for (auto e : graph[x]) {
				if (par[e.first] == -1 && e.second > 0) {
					par[e.first] = x;
					q[ptr++] = e.first;
					if (e.first == sink) {
						goto out;
					}
				}
			}
		}

		return flow;

		out: 
		ll inc = numeric_limits<ll>::max();
		for (int y = sink; y != source; y = par[y])
			inc = min(inc, graph[par[y]][y]);
		flow += inc;
		for (int y  = sink; y != source; y = par[y]) {
			int p = par[y];
			if ((graph[p][y] -= inc) <= 0) graph[p].erase(y);
			graph[y][p] += inc;
		}
	}
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m; cin>>n>>m;
	char a[n][m];

	char bf[] = {'^','>','v','<'};
	int dg = 0;
	f(i,0,n) f(j,0,m) {
		cin>>a[i][j];
		char c; cin>>c;
		int k = 0;
		while (bf[k] != c) k++;
		dg = (dg + k)%4;
	}

	int di[] = {1,-1,0,0};
	int dj[] = {0,0,1,-1};

	vector<unordered_map<int,ll>> graph(n*m+2);
	int source = n*m, sink = n*m+1;

	auto addEdge = [&](int i, int j, ll cost) {
		graph[i][j] += cost;
	};

	f(i,0,n) f(j,0,m) {
		if ((i+j)&1) {
			addEdge(i*m+j, sink, 1);
		} else {
			addEdge(source, i*m+j, 1);
			f(k,0,4) {
				int ni = i+di[k], nj = j+dj[k];
				if (IN(ni,0,n-1) && IN(nj,0,m-1) && a[i][j] != a[ni][nj]) {
					addEdge(i*m+j, ni*m+nj,1);
				}
			}
		}
	}

	int mf = maxflow(graph, source, sink);
	if (mf*2 == n*m) cout << mf - (dg != 0) << endl;
	else cout << mf << endl;

	return 0;
}
