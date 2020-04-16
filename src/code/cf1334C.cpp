
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple
#define sz(a) a.size()
#define re(a,b) a=min(a,b)

using ld = long double;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi  = vector<int>;

const int oo = 1e9+7;
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

const int N = 3e5;
int n;
ll a[N], b[N];
ll dp[N][2][2];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t; cin>>t;
	stringstream ss;
	while (t--) {
		cin>>n;
		f(i,0,n) cin>>a[i]>>b[i];
		
		if (n == 1) {
			ss << a[0] << endl;
		} else if (n == 2) {
			ss << min(a[0] + max(0LL, a[1]-b[0]), a[1] + max(0LL, a[0]-b[1])) << endl;
		} else {
			f(i,0,n) f(j,0,2) f(k,0,2) dp[i][j][k] = loo;

			dp[0][0][0] = dp[0][1][0] = 0;

			ll ans = loo;

			f(i,0,n) f(j,0,2) f(k,0,2) if (dp[i][j][k] < loo) {
				if (i != n-1) {
					f(nj,0,2) re(dp[i+1][nj][k|(nj!=j)], dp[i][j][k] + max(0LL, a[i]-(!j?b[(i-1+n)%n]:0)));
				} else if (k) re(ans, dp[i][j][k] + max(0LL, a[i]-(!j?b[i-1]:0)));
			}
			ss << ans << endl;
		}
	}
	cout << ss.str();

	return 0;
}
