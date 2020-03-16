
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5, oo = 1e9;
int n, m, k;
int a[N];
vector<int> adj[N];
int dist[N];
bool mul[N];

#define f(i,a,b) for (int i = a; i < b; i++)

void SSSP(int s) {
	queue<int> pq;
	pq.push(s);
	f(i,0,n) dist[i] = oo;
	dist[s] = 0;

	f(i,0,n) mul[i] = 0;

	while (pq.size()) {
		int v = pq.front(); pq.pop();
		for (int w : adj[v]) {
			if (dist[w] == oo) {
				dist[w] = dist[v] + 1;
				pq.push(w);
			} else if (dist[w] == dist[v] + 1)
				mul[w] = 1;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>m;
	f(_,0,m) {
		int a, b; cin>>a>>b;
		adj[--b].push_back(--a);
	}
	cin>>k;
	f(i,0,k) {
		cin>>a[i];
		a[i]--;
	}
	int s = a[0], t = a[k-1];
	SSSP(t);
	int mini = 0, maxi = 0;
	f(i,0,k-1) {
		mini += dist[a[i+1]] != dist[a[i]]-1;
		maxi += dist[a[i+1]] != dist[a[i]]-1 || mul[a[i]];
	}
	cout << mini << " " << maxi << endl;
	
	return 0;
}
