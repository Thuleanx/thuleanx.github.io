// 101239 G https://codeforces.com/gym/101239/attachments
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
const int K = 90;
ll l, v1, v2, t, s;

int solve() {
	cin>>l>>v1>>v2>>t>>s;	

	ll z = (v2-v1-1)/t;

	vector<pll> d;	
	for (ll x = 1; v1 + x*t < v2; x++) {
		ll lo = x+1, hi = z;	

		ll val = l/s/(v2-x*t);

		while (lo <= hi) {
			ll mid = lo+hi>>1;
			ll valo = l/s/(v2-mid*t);
			if (valo == val) 
				lo = mid+1;
			else hi = mid-1;
		}
		d.push_back(pll(val, lo-x));
		x = hi;
	}
	d.push_back(pll(oo, 1));
	reverse(begin(d),end(d));

	ll ans;
	for (ans = 0; ans <= K; ans++) {
		__int128 sum = 0;

		int n = d.size();
		f(i,0,n) {
			ll z = max(0LL, ans-d[i].first);
			__int128 add = __int128(1)<<z;
			sum += add*d[i].second;
		}
			
		if (sum <= __int128(1)<<ans)
			break;
	}
	if (ans==K+1) cout << "impossible" << endl;
	else cout << ans << endl;


	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	while (t--) solve();
	
	return 0;
}
