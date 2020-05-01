
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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// use uniform_int_distribution<int>(0, i)(rng)

void solve() {
	int n, m; cin>>n>>m;
	int a[n];
	f(i,0,n) cin>>a[i];

	ll fi[n];
	f(i,0,n) fi[i] = (a[i] + (i?fi[i-1]:0));

	ll ans = 0;
	f(i,0,n) if (a[i] == m) {
		ll res = a[i];
		int j = i-1;
		while (j >= 0 && a[j] > a[i])
			res += a[j--];
		j = i+1;
		while (j < n && a[j] > a[i])
			res += a[j++];
		ans = max(ans, res);
	}

	cout << ans << endl;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	while (t--)
		solve();

	return 0;
}
