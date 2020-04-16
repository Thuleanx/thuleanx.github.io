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

const int N = 30;

int d,m;
ll cnt[N], dp[N];

void add(ll &a, ll b) {
	a += b;
	if (a >= m) a -= m;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	stringstream ss;
	while (t--) {
		cin>>d>>m;
		
		f(z,0,N) {
			ll lo = 1<<z, hi = 1<<(z+1);
			if (lo > d) cnt[z] = 0;
			else cnt[z] = min(hi-lo, d-lo+1);
		}

		ll ans = 0;
		f(i,0,N) {
			dp[i] = cnt[i];
			f(j,0,i) add(dp[i], dp[j]*cnt[i]%m);
			add(ans, dp[i]);
		}

		ss << ans << endl;
	}
	cout << ss.str();

	return 0;
}
