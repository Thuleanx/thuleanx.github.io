#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i>=a; i--)
#define mt make_tuple 
#define mp make_pair


const int N = 5e5, K = 22;
int n, k;
int pos[N];
int p[N][K], vis[N], cyc[N];
vector<int> adj[N];

int dfsCycle(int v, int d = 1) {
	vis[v] = 1;
	for (int w : adj[v]) {
		int z = vis[w] == 1 ? d : (vis[w] == 2 ? 0 : dfsCycle(w,d+1));
		if (z) {
			cyc[v] = z;
			return z;
		}
	}
	vis[v] = 2;
	return cyc[v];
}

int ff[N], g[N], sz[N], a[N];

int get(int i, int d) {
	fr(k,0,K) if (d>>k&1) i = p[i][k];
	return i;
}

int dfs(int v, int r, int d = 0) {
	sz[v] = 1;
	if (d) {
		int vv = get(v,k+1);
		if (!cyc[vv]) ff[vv]--;
		else {
			if (k - d + 1 >= cyc[r]) {
				a[r]++;
			} else {
				ff[r]++; ff[vv]--;
				if (pos[vv] < pos[r])
					a[r]++;
			}
		}
	}
	for (int w : adj[v]) if (!cyc[w])
		sz[v] += dfs(w, r, d+1);
	return sz[v];
}

int acrue(int v) {
	for (int w : adj[v]) if (!cyc[w]) {
		acrue(w);
		if (!cyc[v]) ff[v] += ff[w];
	}
	return ff[v];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>k;
	f(i,0,n) cin>>p[i][0];
	f(i,0,n) adj[--p[i][0]].push_back(i);
	f(k,1,K) f(i,0,n) p[i][k] = p[p[i][k-1]][k-1];

	f(i,0,n) if (!vis[i])
		dfsCycle(i);
	f(i,0,n) vis[i] = 0;
	f(i,0,n) if (!vis[i] && cyc[i]) {
		pos[i] = 0;
		vis[i] = 1;
		for (int j = p[i][0], pj = i; i != j; j = p[j][0], pj = p[pj][0]) {
			pos[j] = pos[pj]+1;
			vis[j] = 1;
		}
	}

	f(v,0,n) if (cyc[v]) {
		dfs(v, v); acrue(v); }
	f(i,0,n) if (!cyc[i]) g[i] = sz[i] + ff[i];
	f(i,0,n) vis[i] = 0;
	f(i,0,n) if (!vis[i] && cyc[i]) {
		int j = i;	
		int sum = 0, ad = 0;
		do {
			ad += a[j];
			j = p[j][0];
		} while (j != i);
		sum = ad;
		do {
			sum += ff[j];
			g[j] = sum + min(k+1,cyc[j]); 
			vis[j] = 1;
			j = p[j][0];
		} while (j != i);
	}

	stringstream ss;
	f(i,0,n) ss << g[i] << endl;
	cout << ss.str();
	

	return 0;
}
