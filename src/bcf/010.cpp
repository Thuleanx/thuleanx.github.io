
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

int solve1(ll R) {
	f(i,R,2e9+1-R) f(j,R,2e9+1-R) {
		cout << ll(i-1e9) << " " << ll(j-1e9) << endl;
		fflush(stdout);
		string s; cin>>s;
		if (s == "WRONG") exit(0);
		if (s == "CENTER") return 0;
	}
	return 0;
}

bool in(ll x, ll y, pair<ll, ll> center, ll R) {
	ll dx = center.first - x, dy = center.second - y;
	return R*R >= dx*dx + dy*dy;
}

int solve2(ll R) {
	int r = 50;
	vector<pair<ll,ll>> centers;
	vector<int> ans;
	vector<pll> gr = {mp(r,R), mp(R,r)};
	for (pll pp : gr) {
		centers.push_back(mp(pp.first, pp.second));
		centers.push_back(mp(2e9-pp.first, pp.second));
		centers.push_back(mp(pp.first, 2e9-pp.second));
		centers.push_back(mp(2e9-pp.first, 2e9-pp.second));
	}
	f(i,0,centers.size()) {
		cout << ll(centers[i].first-1e9) << " " << ll(centers[i].second-1e9) << endl;
		fflush(stdout);
		string s; cin>>s;
		if (s == "CENTER") return 0;
		if (s == "HIT") ans.push_back(1);
		else ans.push_back(0);
	}
	
	f(i,R,2e9+1-R) f(j,R,2e9+1-R) {
		bool ba = 0;
		f(z,0,ans.size()) {
			if (in(i,j,centers[z],R) && !ans[z]) ba = 1;
			if (!in(i,j,centers[z],R) && ans[z]) ba = 1;
		}
		if (ba) continue;
		cout << ll(i-1e9) << " " << ll(j-1e9) << endl;
		fflush(stdout);
		string s; cin>>s;
		if (s == "CENTER") return 0;
	}

	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int T, A, B;
	cin>>T>>A>>B;
	while (T--) {
		if (A == 1e9-5) solve1(A);
		else if (A == 1e9-50) solve2(A);
	}

	return 0;
}
