

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5, M = 24;
const long long oo = 1e18;

#define f(i,a,b) for (int i = a; i <b ; i++)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple

int n,m,k;
vector<int> adj[N];
int a[N], b[N], c[N];

bool sig[N]; 
int req[N], rev[N];
vector<int> ls;

vector<pair<int, long long>> edges[N];

vector<long long> dp[1<<(M/2)];

void run(int v) {
	long long dist[n];
	f(i,0,n) dist[i] = oo;

	priority_queue<pair<int,long long>, vector<pair<int,long long >>,
		greater<pair<int,long long>> > pq;
	pq.push(mp(v,0));
	dist[v] = 0;

	while (pq.size()) {
		auto pp = pq.top(); pq.pop();
		int u = pp.first;
		long long cost = pp.second;

		if (dist[u] != cost) continue;
		if (sig[u] && u != v) continue;

		for (int e : adj[u]) {
			int w = a[e]^b[e]^u;
			if (dist[w] > cost + c[e]) {
				dist[w] = cost + c[e];
				pq.push(mp(w,dist[w]));
			}
		}
	}
	for (int u : ls) if (dist[u] != oo && u != v) {
		/* cout << v << " " << u << " " << dist[u] << endl; */
		edges[v].push_back(mp(u, dist[u]));
	}
	if (dist[n-1] != oo) {
		/* cout << v << " " << n-1 << " " << dist[n-1] << endl; */
		edges[v].push_back(mp(n-1,dist[n-1]));
	}
}

bool up(int mask, int j, long long cost) {
	if (!dp[mask].size()) dp[mask] = vector<long long>(M,oo);
	if (dp[mask][j] > cost) {
		dp[mask][j] = cost;
		return 1;
	}
	return 0;
}

long long query(int mask, int j) {
	if (!dp[mask].size()) return oo;
	return dp[mask][j];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>m>>k;
	f(i,0,n) req[i] = -1;
	f(i,0,m) {
		cin>>a[i]>>b[i]>>c[i];
		if (a[i] == b[i]) continue;
		adj[--a[i]].push_back(i);
		adj[--b[i]].push_back(i);
	}
	f(i,0,k) {
		int x, y; cin>>x>>y;
		req[--y] = --x;
		sig[y] = sig[x] = 1;

		rev[x] = ls.size();
		ls.push_back(x); 	
		rev[y] = ls.size();
		ls.push_back(y);
	}
	// got all significant vertices
	run(0);
	for (int v : ls) run(v);
	return 0;

	long long ans = oo;
	for (auto pp : edges[0]) {
		int w = pp.first; long long cost = pp.second;
		if (w == n-1) 
			ans = cost;
		else if (req[w] == -1)
			up(1<<(rev[w]/2), rev[w], cost);
	}

	f(mask,0,1<<k) if (dp[mask].size()) {
		priority_queue<pair<int,long long>, vector<pair<int,long long >>,
			greater<pair<int,long long>>> pq;
		f(j,0,2*k) if (dp[mask][j] != oo)
			pq.push(mp(j,dp[mask][j]));
		while (pq.size()) {
			int j; 
			{
				auto pp = pq.top(); pq.pop();
				j = pp.first; 
				if (dp[mask][j] != pp.second) continue;
			}
			for (auto pp : edges[ls[j]]) {
				int w = pp.first; long long cost = pp.second;
				if (w == n-1) {
					ans = min(ans, cost + dp[mask][j]);
				} else if (req[w] == -1 || (mask>>(rev[req[w]]/2)&1)) {
					int ww = rev[w];
					int nmask = ww&1?mask:mask|(1<<(ww/2));

					if (up(nmask, ww, dp[mask][j] + cost) && nmask == mask)
						pq.push(mp(ww, dp[mask][j] + cost));
				}
			}
		}
		/* f(j,0,2*k) if (dp[mask][j] != oo) */
		/* 	cout << bitset<2>(mask) << " " << j << " = " << dp[mask][j] << endl; */
			
	}

	cout << (ans==oo?-1:ans) << endl;

	return 0;
}
