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

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	stringstream ss;
	while (t--) {
		ll n, l, r;
		cin>>n>>l>>r; l--; r--;
	
		int j = 1; ll m = 0;
		while (m + 2*(n-j) < l)
			m += 2*(n-j++);

		int cnt = 0;
		while (cnt+m <= r) {
			if (cnt+m == r && r == n*(n-1)) {
				ss << 1;
				break;
			}
			f(z,j+1,n+1) {
				if (cnt+m >= l && cnt+m <= r) ss << j << " ";
				cnt++;
				if (cnt+m >= l && cnt+m <= r) ss << z << " ";
				cnt++;
			}
			j++;
		}
		ss << endl;
	}
	cout << ss.str();
	
	return 0;
}
