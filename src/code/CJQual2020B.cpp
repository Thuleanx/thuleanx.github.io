
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

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	stringstream ss;

	int p = 0;
	while (t--) {
		string s; cin>>s;
		int n = s.length();

		int cnt = 0;
		ss << "Case #" << ++p << ": ";
		f(i,0,n) {
			while (cnt > s[i]-'0') {
				ss << ')';
				cnt--;
			}
			while (cnt < s[i]-'0') {
				ss << '(';
				cnt++;
			}
			ss << s[i];
		}
		while (cnt--) ss << ')';
		ss << endl;
	}
	cout << ss.str();

	return 0;
}
