
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
using ld = long double;

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

int n, w, u, v, t1, t2;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>w>>u>>v>>t1>>t2;

	ld offset = 0;
	map<ld, int> cnt;

	f(i,0,n) {
		char dir; cin>>dir;
		int m; cin>>m;

		f(j,0,m) {
			int l, p; cin>>l>>p;
			
			ld b = ld(p*(dir=='W'?1:-1))/u - offset - ld(w)/v,
			   e = ld(p*(dir=='W'?1:-1) + l)/u - offset; 

			assert(b<=e);
			cnt[b]++; cnt[e]--;
		}
		offset += ld(w) / v;
	}

	ld last = t1;
	int c = 0;

	ld ans = 0;
	for (auto pp : cnt) if (pp.first <= t2) {
		if (c == 0) ans = max(ans, pp.first - last);
		c += pp.second;
		last = max(last, pp.first);
	}
	if (!c) ans = max(ans, t2 - last); 

	cout << setprecision(40) << ans << endl;

	return 0;
}
