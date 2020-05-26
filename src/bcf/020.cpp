
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


const int N = 1e5;
int n; ll m;
ll a[N];

ll gcd(ll a, ll b) {
	return a?gcd(b%a, a):b;
}

int solve() {
	cin>>n>>m;
	f(i,0,n) cin>>a[i];

	ll g = 0;
	f(i,0,n) g = gcd(g, a[i]-1);

	vector<ll> fre;

	// find all 2 free divisors
	for (ll p = 1; p*p <= g; p++) if (g % p == 0) {
		if (p&1) fre.push_back(p);
		if ((g/p&1) && p*p != g) fre.push_back(g/p);
	}

	ll ans = 0;

	for (ll x : fre) {
		while (x < m) {
			ans += m-x;	
			x *= 2;
		}
	}

	cout << ans << endl;

	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	solve();

	return 0;
}
