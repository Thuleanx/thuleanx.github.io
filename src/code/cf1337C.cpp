
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

const int oo = 998244353;
const ll loo = 1e18;

ll modpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b&1) res = res*a%oo;
		a = a*a%oo;
		b /=2;
	}
	return res;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// use uniform_int_distribution<int>(0, i)(rng)

const int N = 3001;
int n, m;
string s, t;
vector<ll> dp[N][N];

void add(ll &a, ll b) {
	a += b;
	if (a>=oo) a -= oo;
}

ll run(int i, int j, int k) {
	if (dp[i][j][k] != -1) return dp[i][j][k];

	if (i == m && j == m) {
		int num = k;
		if (num == n) return dp[i][j][k] = 0;
		
		dp[i][j][k] = 0;
		if (s[num] == t.back()) add(dp[i][j][k], run(m-1,m-1,k));
		add(dp[i][j][k], 2*run(i,j,k+1)%oo);
		return dp[i][j][k];
	}

	int num = j-i+1+k; // how many letters

	if (num == n) return dp[i][j][k] = i == 0 && j == m-1;

	dp[i][j][k] = (i==0&&j==m-1);

	if (i && s[num] == t[i-1]) add(dp[i][j][k], run(i-1, j, k));

	if (j < m-1 && s[num] == t[j+1]) add(dp[i][j][k], run(i, j+1, k));

	if (j == m-1) add(dp[i][j][k], run(i,j,k+1));

	return dp[i][j][k];
}

int solve() {
	cin>>s>>t;
	n = s.length(); m = t.length();

	f(i,0,m+1) f(j,0,m+1) dp[i][j] = vector<ll>(1,-1);
	f(i,0,m) {
		dp[i][m-1] = vector<ll>(n+1,-1);
		dp[m][m] = vector<ll>(n+1,-1);
	}

	ll ans = 0;
	f(i,0,m) if (s[0] == t[i]) ans = (ans +  2*run(i,i,0)%oo) % oo;
	ans = (ans+2*run(m,m,1)%oo)%oo;

	cout << ans << endl;

	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	solve();

	return 0;
}
