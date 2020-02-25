#include <bits/stdc++.h>
using namespace std;

const int N  = 13; // the godnumber
const long double oo = 1e18;

using point = tuple<int,int,int>;
#define x(p) get<0>(p)
#define y(p) get<1>(p)
#define z(p) get<2>(p)
#define cnt(x) __builtin_popcountll(x)
#define re(a,b) a = min(a,b)

point operator - (point a, point b) {
	return make_tuple(x(a)-x(b), y(a)-y(b), z(a)-z(b));
}

long double len(point a) {
	return sqrt(1LL*x(a)*x(a) + 1LL*y(a)*y(a) + 1LL*z(a)*z(a));
}

int n;
point l[N];
vector<point> c[N];
long double dp[N][N];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n;
	point s;
	int mx,my,mz; cin>>mx>>my>>mz;
	s = make_tuple(mx,my,mz);

	
	for (int i = 0; i < n; i++) {
		int K; cin>>K;
		cin>>mx>>my>>mz;
		l[i] = make_tuple(mx,my,mz);
		for (int j = 0; j < K; j++) {
			cin>>mx>>my>>mz;
			c[i].emplace_back(make_tuple(mx,my,mz));
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			dp[i][j] = oo;
	for (int i = 0; i < n; i++) {
		int K = c[i].size();
		
		long double dps[1<<K][K];
		for (int m = 0; m < (1<<K); m++)
			for (int j = 0; j < K; j++)
				dps[m][j] = oo;
		for (int j = 0; j < K; j++)
			dps[1<<j][j] = len(l[i] - c[i][j]);
		for (int m = 0; m < (1<<K); m++)
		for (int j = 0; j < K; j++) if (dps[m][j] != oo)
			for (int k = 0; k < K; k++) if (!(m>>k&1))
				re(dps[m|(1<<k)][k], dps[m][j] + len(c[i][j] - c[i][k]));


		for (int j = 0; j < K; j++) {
			for (int k = 0; k < n; k++) if (k == i)
				re(dp[i][k], dps[(1<<K)-1][j]);
			else re(dp[i][k], dps[(1<<K)-1][j] + len(c[i][j] - l[k])); // to next lever
		}
	}


	long double dpb[1<<n][n];
	for (int m = 0; m < (1<<n); m++)
	for (int i = 0; i < n; i++)
		dpb[m][i] = oo;
	
	for (int i = 0; i < n; i++)
		dpb[1<<i][i] = len(l[i] - s);

	long double ans = oo;

	for (int m = 0; m < (1<<n); m++)
	for (int i = 0; i < n; i++) if (dpb[m][i] != oo) {
		for (int j = 0; j < n; j++) if (!(m>>j&1))
			re(dpb[m|(1<<j)][j], dpb[m][i] + dp[i][j]);
	}

	for (int i = 0; i < n; i++)
		re(ans, dpb[(1<<n)-1][i] + dp[i][i]);

	cout << setprecision(40) << ans << endl;

	return 0;
}
