// 1329B https://codeforces.com/contest/1329/problem/B

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

const int N = 35;
int n, m;
ll cnt[N], dp[N];

int solve() {
	cin>>n>>m;	
	f(z,0,N) {
		ll lo = 1LL<<z, hi = 1LL<<z+1;		
		hi = min(hi, (ll) (n+1));
		cnt[z] = lo>n ? 0 : hi - lo;
	}
	ll ans = 0;
	f(i,0,N) {
		dp[i] = cnt[i] % m;
		f(j,0,i) dp[i] = (dp[i] + dp[j] * cnt[i] % m) % m;
		ans = (ans + dp[i]) % m;
	}
	cout << ans << endl;
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	while (t--)
		solve();

	return 0;
}
