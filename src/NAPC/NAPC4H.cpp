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
using ld = long double;

const int oo = 1e9+7;
const ll ool = 1e18;

ll modpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b&1) res = res*a%oo;
		a = a*a%oo;
		b /=2;
	}
	return res;
}


using point = complex<ld>;
#define x real()
#define y imag()

ld cross(point a, point b) { 
	return (conj(a)*b).y;
}
ld dot(point a, point b) {
	return (conj(a)*b).x;
}

const int N = 3000;
int n, m;
bool vis[N][N];
point p[N];
ld dist[N][N];
ld dp[N][N][2];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	while (t--) {
		cin>>n;
		f(i,0,n) {
			int a,b; cin>>a>>b;
			p[i] = point(a,b);
		}
		f(i,0,n) f(j,0,n) vis[i][j] = 0;

		cin>>m;
		f(i,0,m) {
			int a,b; cin>>a>>b;
			vis[--a][--b] = 1;
			vis[b][a] = 1;
		}
		f(i,0,n) f(j,0,n) dist[i][j] = abs(p[i]-p[j]);
		f(i,0,n) f(j,0,n) f(k,0,2) dp[i][j][k] = -ool;
		f(i,0,n) dp[i][i][0] = dp[i][i][1] = 0;

		ld ans = 0;
		f(d,0,n) f(i,0,n) f(k,0,2) {
			int j = (i-d+n)%n;
			if (dp[i][j][k] == ool) continue;
			ans = max(ans, dp[i][j][k]);
			for (int z = (i+1)%n; z != j; z = (z+1)%n) if (vis[z][k?j:i]) {
				dp[i][z][1] = max(dp[i][z][1], dp[i][j][k] + (k ? dist[j][z] : dist[i][z])); 
				dp[z][j][0] = max(dp[z][j][0], dp[i][j][k] + (k ? dist[j][z] : dist[i][z]));
			}
		}

		cout << setprecision(80) << ans << endl;
	}

	return 0;
}
