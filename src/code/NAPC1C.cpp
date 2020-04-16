#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define mp make_pair
using ll = long long;
using VL = vector<ll>;
using vi = vector<int>;
const ll INF = numeric_limits<ll>::max()/4;

const ll oo = 1e18;

struct MCMF {
	int n;
	vector<VL> cap, cost;
	MCMF(int n) : n(n), cap(n, VL(n)), cost(n, VL(n)) {}
	long long maxflow(int s, int t) {
		ll d[n], p[n];
		ll res = 0;
		while (1) {
			f(i,0,n) d[i] = oo, p[i] = -1;
			d[s] = 0;
			f(i,0,n-1) f(j,0,n) f(k,0,n) {
				if (cap[j][k] > 0 && d[j] < oo && d[k] > d[j] + cost[j][k]) {
					d[k] = d[j] + cost[j][k];
					p[k] = j;
				}
			}
			if (d[t] == oo) break;
			ll sd = oo;
			int w = t;
			while (w != s) {
				sd = min(sd, cap[p[w]][w]);
				w = p[w];
			}
			res += sd * d[t];
			w = t;
			while (w != s) {
				cap[p[w]][w] -= sd;
				cap[w][p[w]] += sd;
				w = p[w];
			}
		}
		return res;
	}
	void addEdge(int u, int v, ll cap, ll cost) {
		this->cap[u][v] = cap;
		this->cost[u][v] = cost;
		this->cost[v][u] = -cost;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, k; cin>>n>>k; n++;

	MCMF ds(2*n+3);
	int s = 2*n, t = 2*n+1, ss = 2*n+2;

	f(i,0,n) {
		ds.addEdge(s, i, (!i ? k : 1), 0); // yeah you can use the free one edge
		f(j,i+1,n) {
			int x; cin>>x;
			ds.addEdge(i, j+n, 1, x);
		}
		ds.addEdge(i+n, t, 1, 0);
	}

	cout << ds.maxflow(s,t) << endl;

	return 0;
}
