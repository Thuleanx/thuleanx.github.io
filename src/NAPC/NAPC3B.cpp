
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

	string s;
	getline(cin,s);
	stringstream ss(s);
	int a, b; cin>>a>>b;
	
	vector<string> vc;
	vector<int> cul;
	while (ss>>s) {
		vc.push_back(s);
		cul.push_back(s.length() + (cul.size()?cul.back():0));
	}

	stringstream ssr;
	int n = cul.size();
	f(z,a,b+1) {
		int ans = 0;
		for (int i = 0; i < n; ) {
			ans += cul[i] - (i?cul[i-1]:0) + (i?1:0);
			int lo = i, hi = n-1;
			while (lo <= hi) {
				int mid = lo+hi>>1;
				if (cul[mid] - (i?cul[i-1]:0) + mid - i <= z)
					lo = mid+1;
				else hi = mid-1;
			}
			i = hi + 1;
		}
		ssr << ans << endl;
	}
	cout << ssr.str();


	return 0;
}
