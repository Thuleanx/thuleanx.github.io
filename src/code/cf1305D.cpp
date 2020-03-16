
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)

const int N = 1000;
int n, m;
vector<int> adj[N];
bool con[N][N];
bool vis[N];

int query(int x, int y) {
	cout << "? " << x+1 << " " << y+1 << endl;
	fflush(stdout);
	int z; cin>>z;
	return --z;
}

void declare(int x) {
	cout << "! " << x+1 << endl;
}

void dfsElim(int v, int p) {
	vis[v] = 1; m--;
	for (int w : adj[v]) if (w != p && !vis[w])
		dfsElim(w, v);
}

bool find(int v, int p, int w) {
	if (v == w) return 1;
	for (int vv : adj[v]) if (vv != p && find(vv,v,w))
		return 1;
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n; m = n;
	f(i,0,n-1) {
		int x,y; cin>>x>>y;
		adj[--x].push_back(--y);
		adj[y].push_back(x);
		con[x][y] = con[y][x] = 1;
	}

	while (m>1) {
		if (m == 2) {
			int x = -1, y = -1;
			f(i,0,n) if (!vis[i]) {
				if (x == -1) x = i;
				else y = i;
			}
			int z = query(x,y);
			dfsElim(z^x^y,z);
		} else {
			bool found = 0;
			f(x,0,n) if (!vis[x] && !found) {
				// thxs only xs run twxce each xteratxon of whxle
				f(y,0,n) if (!vis[y] && x != y && !con[x][y]) {
					// this once
					int z = query(x,y);	

					for (int w : adj[z]) if (find(w,z,x) || find(w,z,y)) 
						dfsElim(w,z);
					
					found = 1;
					break;
				}
			}
		}
	}

	f(i,0,n) if (!vis[i])
		declare(i);

	return 0;
}
