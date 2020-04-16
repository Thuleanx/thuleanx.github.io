
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple
#define sz(a) a.size()

using ld = long double;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi  = vector<int>;

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

int solve() {
	int n, m, t;
	cin>>n>>m>>t;

	ld pi[n], a[n][n], b[n][m];

	f(i,0,n) cin>>pi[i];
	f(i,0,n) f(j,0,n) cin>>a[i][j];
	f(i,0,n) f(j,0,m) cin>>b[i][j];

	int sym[t];
	f(i,0,t) cin>>sym[i];

	ld dp[t][n];
	f(i,0,n) dp[0][i] = pi[i] * b[i][sym[0]];

	f(z,1,t) f(i,0,n) {
		dp[z][i] = 0;
		f(j,0,n) dp[z][i] += dp[z-1][j] * a[j][i];
		dp[z][i] *= b[i][sym[z]];
	}

	f(z,0,t) f(i,0,n)
		cout << dp[z][i] << " \n"[i==n-1];

	return 0;
}

int solve2() {
	int n, m, t;
	cin>>n>>m>>t;

	ld pi[n], a[n][n], b[n][m];

	f(i,0,n) cin>>pi[i];
	f(i,0,n) f(j,0,n) cin>>a[i][j];
	f(i,0,n) f(j,0,m) cin>>b[i][j];

	int sym[t];
	f(i,0,t) cin>>sym[i];

	ld dp[t][n];
	int rev[t][n];
	f(i,0,n) dp[0][i] = pi[i] * b[i][sym[0]], rev[0][i] = 0;

	f(z,1,t) f(i,0,n) {
		dp[z][i] = rev[z][i] = 0;
		f(j,0,n) {
			if (dp[z][i] < dp[z-1][j] * a[j][i]) {
				dp[z][i] = dp[z-1][j] * a[j][i];
				rev[z][i] = j;
			}
		}
		dp[z][i] *= b[i][sym[z]];
	}

	f(z,0,t) f(i,0,n)
		cout << dp[z][i] << " \n"[i==n-1];

	vi ans;
	int z = 0;
	f(i,0,n) if (dp[t-1][i] > dp[t-1][z]) z = i;

	fr(i,0,t) {
		ans.push_back(z);
		z = rev[i][z];
	}

	while (ans.size()) {
		cout << ans.back() << " ";
		ans.pop_back();
	}
	cout << endl;

	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	solve();

	return 0;
}

