
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

	while (1) {
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
					if (e.first == sink) {
						goto out;
					}
				}
			}
		}
		return flow;

out: 
		T inc = numeric_limits<T>::max();
		for (int y = sink; y != source; y = par[y]) {
			inc = min(inc, graph[par[y]][y]);
		}

		flow += inc;
		for (int y = sink; y != source; y = par[y]) {
			int p = par[y];
			if ((graph[p][y]-=inc)<=0) graph[p].erase(y);
			graph[y][p] += inc;
		}
	}
}

int z = 4;
map<tuple<int,int,int>, int> id;

int gen(int i, int j, int zz) {
	if (id.count(mt(i,j,zz))) return id[mt(i,j,zz)];
	return id[mt(i,j,zz)] = z++;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, k; cin>>n>>m>>k;

	vector<unordered_map<int,ll>> graph(2e6);
	int s = 0, t = 1, ss = 2, tt = 3;

	graph[s][tt] = n; graph[ss][t] = m; graph[t][s] = oo;

	f(i,0,n) graph[s][4+i] = oo, graph[ss][4+i] = 1;
	f(j,0,m) graph[4+j+n][t] = oo, graph[4+j+n][tt] = 1;
	z = n+m+4;

	int p[k],sa[k],la[k];
	f(i,0,k) {
		cin>>p[i]>>sa[i]>>la[i];
		p[i]--; sa[i]--; la[i]--;
		graph[4+p[i]][gen(p[i],la[i],0)] = 1;
		graph[gen(p[i],la[i],0)][gen(sa[i],la[i],1)] = oo;
		graph[gen(sa[i],la[i],1)][4+sa[i]+n] = 1;
	}

	int ans = maxflow<ll>(graph, ss, tt);
	if (ans < n+m) {
		cout << -1 << endl;
	} else {
		stringstream ssr;
		int cnt = 0;
		set<tuple<int,int,int>> used;
		f(i,0,k) if (!used.count(mt(p[i],sa[i],la[i]))) {
			used.insert(mt(p[i],sa[i],la[i]));
			if (graph[gen(sa[i],la[i],1)][gen(p[i],la[i],0)]) {
				cnt++;
				ssr << i+1 << " ";
			}
		}
		cout << cnt << endl;
		cout << ssr.str();
	}

	return 0;
}
