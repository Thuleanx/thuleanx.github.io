// https://codingcompetitions.withgoogle.com/codejam/round/000000000019fef2/00000000002d5b62

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

char dir[] = {'N', 'S', 'E', 'W'};

// op is dir ^ 1
int solve() {
	ll x, y; cin>>x>>y;
	bool zap = x < 0,  zip = y < 0;
	x = abs(x); y = abs(y);

	string s;
	while (x || y) {
		if (!((x&1) ^ (y&1))) {
			cout << "IMPOSSIBLE" << endl;
			return 0;
		}
		if (x&1) {
			if (x-1 == 0 && y == 0)
				x--, s += 'W';
			else if ((((x+1)/2&1) ^ (y/2&1)))
				x++, s += 'E';
			else x--, s += 'W';
		} else {
			if (y-1 == 0 && x == 0)
				y--, s += 'S';
			else if (((y+1)/2&1) ^ (x/2&1))
				y++, s += 'N';
			else y--, s += 'S';
		}
		x /= 2; y /= 2;
	}
	f(i,0,s.length()) {
		if (!zap && (s[i] == 'E' || s[i] == 'W'))
			s[i] = s[i] == 'E' ? 'W' : 'E';
		if (!zip && (s[i] == 'N' || s[i] == 'S'))
			s[i] = s[i] == 'N' ? 'S' : 'N';
	}
	cout << s << endl;

	return 0;
}

int solve2() {
	ll x, y; cin>>x>>y;
	bool zap = x < 0, zip = y < 0;
	x = abs(x); y = abs(y);
	string s;
	while (x | y) {
		if ( (x&1) && (y&1) ) {
			cout << "IMPOSSIBLE" << endl;
			return 0;
		}
	}

	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	int p = 0;
	while (t--) {
		cout << "Case #" << ++p << ": ";
		solve();
	}

	return 0;
}
