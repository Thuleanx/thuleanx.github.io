
#include <bits/stdc++.h>
using namespace std;

#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define f(i,a,b) for (int i = a; i < b; i++)
#define IN(i,a,b) (a<=i&&i<=b)

const int oo = 1e9;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, q, k;
	cin>>n>>m>>q>>k;

	vector<int> adj[n];
	queue<int> pq;
	int dist[n];
	f(i,0,n) dist[i] = oo;

	f(i,0,q) {
		int x; cin>>x;
		pq.push(--x);
		dist[x] = 0;
	}

	f(i,0,m) {
		int v,w; cin>>v>>w;
		adj[--v].push_back(--w);
		adj[w].push_back(v);
	}

	while (pq.size()) {
		int v = pq.front(); pq.pop();
		for (int w : adj[v]) if (dist[w] == oo) {
			dist[w] = dist[v]+1;
			pq.push(w);
		}
	}

	stringstream ss;
	f(i,0,n) {
		int ans = 0;
		f(z,1,n+1) {
			if (dist[i] <= 0) break;	
			dist[i] -= z*k;
			ans++;
		}
		ss << ans << " ";
	}
	cout << ss.str();

	return 0;
}
