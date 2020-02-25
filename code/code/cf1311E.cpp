#include <bits/stdc++.h>
using namespace std;

const int N = 5007, oo = 1e9;
int madp[N], midp[N];
#define f(i,a,b) for (int i = a; i < b; i++)
#define IN(i,a,b) (a<=i&&i<=b)
int parent[N];
int v;

void dfs(int num, int desir, int p) {
	assert(IN(desir,midp[num],madp[num]));
	if (num == 0) return;
	int th = v;
	parent[v++] = p;
	
	if (num == 1) return;


	desir -= num-1;
	for (int d = 0; d < num; d++) {
		int dd = num-d-1;

		// min left -> something to the right
		if (IN(desir - midp[d], midp[dd], madp[dd])) {
			dfs(d,midp[d],th);
			dfs(dd,desir-midp[d],th);
			break;
		}
		// min right -> something to the right
		if (IN(desir-madp[d], midp[dd], madp[dd])) {
			dfs(d,madp[d],th);
			dfs(dd,desir-madp[d],th);
			break;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	f(i,0,N) midp[i] = oo, madp[i] = -1;
	f(i,0,2) midp[i] = madp[i] = 0;

	for (int i = 2; i < N; i++) {
		for (int d = 0; d < i; d++) {
			int dd = i-d-1;
			// min
			midp[i] = min(midp[i], midp[d] + midp[dd] + i - 1);
			// max
			madp[i] = max(madp[i], madp[d] + madp[dd] + i - 1);
		}
	}

	int t; cin>>t;

	stringstream ss;
	while (t--) {
		int n, d;
		cin>>n>>d;	
		if (IN(d, midp[n], madp[n])) {
			v = 0;
			dfs(n, d, -1);
			ss << "YES" << endl;
			for (int i = 1; i < n; i++)
				ss << parent[i]+1 << " \n"[i==n-1];
		} else ss << "NO" << endl;
	}
	cout << ss.str();

	return 0;
}
