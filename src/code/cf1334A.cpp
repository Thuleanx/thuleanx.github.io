
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
	while (t--) {
		int n; cin>>n;
		int p[n], c[n];
		f(i,0,n) cin>>p[i]>>c[i];
		bool gd = p[0] >= c[0];
		f(i,1,n) {
			gd &= p[i]>=p[i-1];
			gd &= c[i]>= c[i-1];
			gd &= p[i]-p[i-1] >= c[i]-c[i-1];
		}
		ss << (gd?"YES":"NO") << endl;
	}
	cout << ss.str();

	return 0;
}
