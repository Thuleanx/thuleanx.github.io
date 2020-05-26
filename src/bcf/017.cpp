
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

const int N = 2e5;
int n, k, c;
int a[N];
vector<int> pos[N];

struct BIT {
	ll tree[N];
	BIT() {
		f(i,0,N) tree[i] = 0;
	}
	void add(int i, ll val) {
		for (; i < N; i |= i+1)
			tree[i] += val;
	}
	ll sum(int i) {
		ll res = 0;
		for (; i >= 0; i = (i&(i+1))-1)
			res += tree[i];
		return res;
	}
};

int solve() {
	cin>>n>>c>>k;
	f(i,0,n) {
		cin>>a[i];
		pos[--a[i]].push_back(i);
	}

	ll best = 0;

	BIT ds;
	f(z,0,c) {
		for (int x : pos[z])
			ds.add(x, 1);

		for (int x : pos[z]) {
			int lo = x, hi = n-1;

			while (lo <= hi) {
				int mid = lo+hi>>1;
				if ((mid - x + 1) - (ds.sum(mid) - ds.sum(x-1)) <= k)
					lo = mid+1;
				else hi = mid-1;
			}

			best = max(best, (ds.sum(hi) - ds.sum(x-1)));
		}

		for (int x : pos[z])
			ds.add(x, -1);
	}

	cout << best << endl;

	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	solve();

	return 0;
}
