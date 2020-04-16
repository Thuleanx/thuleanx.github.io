// 1326E https://codeforces.com/problemset/problem/1326/E
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

const int N = 3e5;
int n;
int p[N], q[N], pos[N], ans[N];

struct SegTree {
	int h = 20;
	vi t, d;
	SegTree(): t(vi(N<<1, 0)), d(t) {}
	void apply(int p, int value) {
		t[p] += value;
		if (p < N) d[p] += value;
	}
	void build(int p) {
		while (p>1) p>>=1, t[p] = min(t[p<<1], t[p<<1|1]) + d[p];
	}
	void push(int p) {
		for (int s = h; s > 0; --s) {
			int i = p>>s;
			if (d[i] != 0) {
				apply(i<<1, d[i]);
				apply(i<<1|1, d[i]);
				d[i] = 0;
			}
		}
	}
	void inc(int l, int r, int value) { // [l, r)
		l += N; r += N;
		int l0 = l, r0 = r;
		for (; l < r; l >>= 1, r >>= 1) {
			if (l&1) apply(l++, value);
			if (r&1) apply(--r, value);
		}
		build(l0); build(r0-1);
	}
	int query(int l, int r) { // [l, r)
		l += N; r += N;
		push(l); push(r-1);
		int res = oo;
		for (; l < r; l >>= 1, r >>= 1) {
			if (l&1) res = min(res, t[l++]);
			if (r&1) res = min(res, t[--r]);
		}
		return res;
	}
};

int solve() {
	cin>>n;
	f(i,0,n) {
		cin>>p[i];
		pos[--p[i]] = i;
	}
	SegTree ds;
	auto tr = [&](int z) {
		ds.inc(0, pos[z]+1, -1);
		if (ds.query(0,N)>=0) return 1;
		else {
			ds.inc(0, pos[z]+1, 1);
			return 0;
		}
	};
	f(i,0,n) {
		cin>>q[i]; 
		ans[i] = i?ans[i-1]:n-1;
		while (tr(ans[i])) ans[i]--;
		ds.inc(0, --q[i]+1,1);
	}
	stringstream ss;
	f(i,0,n) ss << ans[i]+1 << " "; 
	cout << ss.str() << endl;
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	solve();

	return 0;
}
