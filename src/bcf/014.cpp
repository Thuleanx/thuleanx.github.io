
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

int cnt(string s) {
	int ans = 0;
	f(i,0,s.length()) if (s[i] == '?')
		ans++;
	return ans;
}

void obtainList(int j, string &s, vector<string> &res) {
	bool gf = 0;
	f(i,j,s.length()) if (s[i] == '?') {
		f(c,i==0 && s.length() > 1,10) {
			s[i] = '0' + c;
			obtainList(i+1, s, res);
			s[i] = '?';
		}
		gf = 1;
		break;
	}
	if (!gf) res.push_back(s);
}

bool match(string s, string r) {
	if (s.length() != r.length()) return 0;
	f(i,0,s.length()) if (s[i] != r[i] && s[i] != '?')
		return 0;
	return 1;
}

void solve() {
	string a, b, c, d;
	cin>>a>>d>>b>>d>>c;

	string res[3] = {a,b,c};
	sort(res, res+3, [&](string x, string y) {
		return cnt(x) < cnt(y);
	});

	vector<string> ls0, ls1;
	obtainList(0, res[0], ls0);
	obtainList(0, res[1], ls1);

	ll ans = 0;
	for (string x : ls0) for (string y : ls1) {
		int xx = stoi(x), yy = stoi(y);
		int z = xx^yy;
		if (match(res[2], to_string(z)))
			ans++;
	}
	cout << ans << endl;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	solve();

	return 0;
}
