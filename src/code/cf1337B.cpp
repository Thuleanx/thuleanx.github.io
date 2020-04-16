
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple
#define sz(a) a.size()
#define sq(a) ((a)*(a))

using ld = long double;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi  = vector<int>;

const int oo = 1e9+7;
const ll loo = 4e18;

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

const int N = 2e5;
int n[3];
int a[3][N];

ll eval(ll x, ll y, ll z) {
	return sq(x-y) + sq(y-z) + sq(x-z);
}

int solve() {
	f(j,0,3) cin>>n[j];
	f(j,0,3) f(i,0,n[j]) cin>>a[j][i];
	f(j,0,3) sort(a[j], a[j]+n[j]);

	ll best = loo;

	int se[] = {0,1,2};
	do {
		int j = 0, k = 0;
		f(i,0,n[se[0]]) { //middle

			// higher
			while (j < n[se[1]] && a[se[0]][i] > a[se[1]][j]) j++;
			if (j == n[se[1]]) break;
			assert(a[se[0]][i] <= a[se[1]][j]);

			// lower
			while (k < n[se[2]]-1 && a[se[0]][i] >= a[se[2]][k+1]) k++;

			if (a[se[2]][k] <= a[se[0]][i])
				best = min(best, eval(a[se[0]][i], a[se[1]][j], a[se[2]][k]));
		}
	} while (next_permutation(se,se+3));

	cout << best << endl;

	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	while (t--) 
		solve();

	return 0;
}
