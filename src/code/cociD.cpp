
#include <bits/stdc++.h>
using namespace std;

#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define f(i,a,b) for (int i = a; i < b; i++)
#define IN(i,a,b) (a<=i&&i<=b)

const int N = 500, NN = 1e6, NT = N*N<<2, oo = 1e9;
int n,m,p;
int di[] = {1,0};
int dj[] = {0,1};
int a[N][N];

struct Edge {
	int a, b, cap, flow;
	Edge() {}
	Edge(int a, int b, int cap) : a(a), b(b), cap(cap) {}
	int other(int v) { return v^a^b; }
	int residual(int v) { return v == b ? cap-flow : flow; }
	void push(int v, int x) { if (v == b) flow += x; else flow -= x; }
};

Edge edges[NN];
vector<int> adj[N*N<<2];

int maxflow(int s, int t) {
	int in_flow[NT], edge_to[NT];
	int flow = 0;
	while (1) {
		memset(in_flow, 0, sizeof(in_flow));
		memset(edge_to, -1, sizeof(edge_to));

		in_flow[s] = oo;
		queue<int> pq;
		pq.push(s);

		while (!pq.empty()) {
			int v = pq.front(); pq.pop();
			for (int e : adj[v]) {
				int w = edges[e].a^edges[e].b^v;
				if (in_flow[v] && edges[e].residual(w) && !in_flow[w]) {
					in_flow[w] = min(in_flow[v], edges[e].residual(w));
					edge_to[w] = e;
					if (w == t) {
						while (edge_to[w] != -1) {
							int e = edge_to[w], u = edges[e].a^edges[e].b^w;
							edges[e].push(w, in_flow[t]);
							w=u;
						}	
						flow += in_flow[t];
						goto endbfs;
					} else pq.push(w);
				}
			}
		}
		endbfs: if (edge_to[t] == -1) 
			break;
	}
	return flow;
}

bool good(int i, int j) {
	return IN(i,0,n-1) && IN(j,0,m-1) && a[i][j];
}

void addEdge(int v, int w, int cp) {
	adj[v].push_back(p);
	adj[w].push_back(p);
	edges[p++] = Edge(v,w,cp);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>m;
	f(i,0,n) {
		string s; cin>>s;
		f(j,0,m) a[i][j] = s[j] == '0';
	}

	int s = 3*N*N, t = 3*N*N+1;
	vector<int> touch[n][m];
	f(k,0,2) f(i,0,n) f(j,0,m) if (good(i,j)) {
		int v = i*m+j+k*n*m;
		if (!good(i-di[k], j-dj[k])) {
			int z = 0;
			while (good(i+di[k]*z, j+dj[k]*z)) {
				touch[i+di[k]*z][j+dj[k]*z].push_back(v);
				z++;
			}
			if (k) addEdge(v,t,1);
			else addEdge(s,v,1);
		}
	}

	f(i,0,n) f(j,0,m) if (touch[i][j].size()>1)
		addEdge(touch[i][j][0], touch[i][j][1], oo);

	int ans = maxflow(s,t);
	stringstream ss;
	ss << ans << endl;
	for (int x : {s,t}) 
	for (int e : adj[x]) if (edges[e].flow) {
		int w = edges[e].other(s);
		int i = w / m % n, j = w % m, k = w >= n*m;
		ss << i+1 << " " << j+1 << " " << (k?"DESNO":"DOLJE") << endl;
	}
	cout << ss.str();

	return 0;
}
