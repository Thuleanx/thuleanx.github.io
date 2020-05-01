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

const int N = 1e3;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// use uniform_int_distribution<int>(0, i)(rng)

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	freopen("record.txt", "r", stdin);

	stringstream BF, Geo, DB;
	int n = 10;
	while (n <= N) {
		f(_,0,10) {
			ld x, y, z; cin>>x>>y>>z;
			BF << n << " " <<setprecision(40) <<  x << endl;	
			Geo << n << " " << setprecision(40) << y << endl;	
			DB << n << " " << setprecision(40) << z << endl;	
		}
		n *= 10;
	}
	cout << BF.str() << endl;
	freopen("BFresult.txt", "w", stdout);
	cout << BF.str() << endl;
	freopen("Georesult.txt", "w", stdout);
	cout << Geo.str() << endl;
	freopen("DBresult.txt", "w", stdout);
	cout << DB.str() << endl;


	return 0;
}
