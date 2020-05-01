
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
	string s;
	getline(cin,s);
	int n = s.length();
	int ans = n;
	fr(p,1,n) {
		bool gd = 1;
		f(i,p,n) if (s[i] != s[i-p]) gd = 0;
		if (gd) ans = p;	
	}
	cout << ans << endl;

}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string s;
	int t; cin>>t; getline(cin, s);
	while (t--) solve();

	return 0;
}
