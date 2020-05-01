// https://codingcompetitions.withgoogle.com/codejam/round/000000000019fef2/00000000002d5b64
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

int solve() {
	int R,S; cin>>R>>S;
	int n = R*S;
	int a[n];
	f(i,0,n) a[i] = i % R; 

	int num = 0;
	stringstream ss;
	/* f(i,0,n) cout << a[i] << " \n"[i==n-1]; */
	while (1) {
		bool gd = 1;
		f(i,0,n) if (a[i] != i/S) gd = 0 ;
		if (gd) break;

		if (a[0] == a[1]) {
			int j = 0;
			while (j < n && a[j] == a[0]) j++;
			num++;
			ss << j << " " << n - j << endl;
			break;
		}

		int z = 0;
		while (1+z < n && a[1+z] == a[1]) z++;

		bool found = 0;
		fr(i,z,n-1) {
			if (a[i] == a[0] && a[i+1] == a[1]) {
				ss << 1+z << " " << i-z << endl;

				int b[n];
				f(j,0,n) b[j] = a[j];
				f(j,0,i-z) b[j] = a[j+(1+z)];

				f(j,i-z,i+1) b[j] = a[j-(i-z)];

				f(j,0,n) a[j] = b[j];

				found = 1;
				break;
			}
		}
		num++;
		if (!found) {
			ss << 1 << " " << n-1 << endl;
			break;
		}
		/* f(i,0,n) cout << a[i] << " \n"[i==n-1]; */
	}

	cout << num << endl;
	cout << ss.str();

	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int T; cin>>T;
	int p = 0;

	while (T--) {
		cout << "Case #" << ++p << ": ";
		solve();
	}

	return 0;
}
