
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

	int p = 0;
	stringstream ss;
	while (t--) {
		int n; cin>>n;

		int a[n][n];
		f(i,0,n) f(j,0,n)
			cin>>a[i][j];

		int k = 0;
		f(i,0,n) k += a[i][i];

		ss << "Case #" << ++p << ": " << k;
		f(z,0,2) {
			int x = 0;
			f(i,0,n) {
				vi cnt(n,0);
				f(j,0,n) cnt[a[i][j]-1]++;
				if (find(begin(cnt),end(cnt),0) != cnt.end()) x++;
			}
			ss << " " << x;
			f(i,0,n) f(j,0,i) swap(a[i][j], a[j][i]);
		}
		ss << endl;

	}
	cout << ss.str();

	return 0;
}
