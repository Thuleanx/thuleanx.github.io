#include <bits/stdc++.h>
using namespace std;

using point = complex<long long>;
#define x real()
#define y imag()

long long len(point a) {
	return ceil(sqrt(a.x * a.x + a.y * a.y));
}

const int mN = 1002, mM = 101, mE = 2e5;
const long long oo = 1e18;

int ee = 0;
int C[mM];
point pos[mN];
vector<int> adj[mN];
int a[mE], b[mE], c[mE];

void addEdge(int v, int w, int mode) {
	adj[v].push_back(ee);
	adj[w].push_back(ee);
	a[ee] = v; b[ee] = w; c[ee] = mode;
	ee++;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int rx, ry;
	cin>>rx>>ry;
	point you = point(rx,ry);
	
	cin>>rx>>ry;
	point dest = point(rx,ry);

	int B, T, N;
	cin>>B>>C[0]>>T; B++;

	for (int i = 1; i <= T; i++)
		cin>>C[i];
	cin>>N;
	N+=2;

	long long dp[N][B];
	for (int i = 0; i < N; i++)
		for (int b = 0; b < B; b++)
			dp[i][b] = oo;

	pos[0] = you; pos[N-1] = dest;
	for (int i = 1; i < N-1; i++) {
		addEdge(0, i, 0); addEdge(i, N-1, 0);
		cin>>rx>>ry;
		pos[i] = point(rx,ry);
		int sz; cin>>sz;
		while (sz--) {
			cin>>rx>>ry;
			addEdge(i, rx+1, ry);
		}
	}
	addEdge(0, N-1, 0);

	dp[0][0] = 0;
	for (int ba = 0; ba < B; ba++) {
		for (int v = 0; v < N; v++) if (dp[v][ba] != oo) {
			for (int e : adj[v]) {
				int w = a[e]^b[e]^v;

				long long di = len(pos[w]-pos[v]);
				if (ba + di < B) {
					dp[w][ba+di] = min(dp[w][ba+di], dp[v][ba] + di * C[c[e]]);
				}
			}
		}
	}

	long long ans = oo;
	for (int b = 0; b < B; b++)
		ans = min(ans, dp[N-1][b]);
	if (ans == oo)
		cout << -1 << endl;
	else cout << ans << endl;


	return 0;
}
