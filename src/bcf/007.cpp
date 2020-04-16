// 101239H https://codeforces.com/gym/101239
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

#define sq(a) ((a)*(a))

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// use uniform_int_distribution<int>(0, i)(rng)

const int N = 1e5;
ld ans[N], r[N];

ld solve(int n, ll w, ll h) {
	if (ans[n] != -1) return ans[n];
	if (n == 0)
		return ans[n] = sq(ld(w+h)/2);
	else {
		ld lo = 0, hi = 1;
		auto fi = [&](ld x) {
			ld hx = x*h, delta = (1-x)*w; 
			return solve(n-1,w,h)*x*x + sq((hx+delta+h)/2) - sq(hx)/2;
		};
		f(_,0,200) {
			ld m1 = (lo*2+hi)/3, m2 = (lo+2*hi)/3;
			if (fi(m1) > fi(m2))	lo = m1;
			else					hi = m2;
		}
		r[n] = lo;
		return ans[n] = fi(lo);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n; ll w, h;
	cin>>w>>h>>n;
	f(i,0,N) ans[i] = -1;

	solve(n,w,h);
	cout << setprecision(40) << ans[n] << endl;
	vector<ld> res;
	ld x = 1;
	fr(i,1,n+1) {
		x *= r[i];
		res.push_back(x);
	}
	reverse(begin(res),end(res));
	f(i,0,res.size()) if (i < 10)
		cout << setprecision(40) << res[i]*w << endl;

	return 0;
}
