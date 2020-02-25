#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
const long long oo = 1e18;
int n, q;
long long x[N], y[N];

struct SegTree {
	bool mx, which;
	int tree[N<<2];
	SegTree(bool mx, bool which) : mx(mx), which(which) { }
	int comb(int a, int b) {
		if (a == -1) return b;
		if (b == -1) return a;
		if (which) return (x[a] < x[b])^mx ? a:b;
		return (y[a]<y[b])^mx?a:b;
	}
	void build() {
		for (int i = 0; i < n; i++)
			tree[i+n] = i;
		for (int i = n-1; i > 0; i--)
			tree[i] = comb(tree[i<<1],tree[i<<1|1]);
	}
	int query(int l, int r) {
		int ans = -1;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l&1) ans = comb(ans, tree[l++]);
			if (r&1) ans = comb(ans, tree[--r]);
		}
		return ans;
	}
	long long queryx(int l, int r) {
		return getval(query(l,r));
	}
	long long getval(int i) {
		if (i==-1) return mx ? -oo : oo;
		return which?x[i]:y[i];
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>q;
	for (int i = 0 ;i  < n; i++)
		cin>>x[i]>>y[i];
	SegTree xmin(0,0), xmax(1,0), ymin(0,1), ymax(1,1);
	xmin.build(); ymin.build(); xmax.build(); ymax.build();
	stringstream ss;
	while (q--) {
		int l, r; cin>>l>>r;
		l--;

		long long ans = oo;
		for (int i : {xmin.query(l,r), xmax.query(l,r), ymin.query(l,r), ymax.query(l,r)}) {
			ans = min(ans,
					max(  max(xmax.queryx(l,i), xmax.queryx(i+1,r))
					- min(xmin.queryx(l,i), xmin.queryx(i+1,r)),
					max(ymax.queryx(l,i), ymax.queryx(i+1,r))
					- min(ymin.queryx(l,i), ymin.queryx(i+1,r))));
		}
		ss << ans << endl;
	}
	cout << ss.str();

	return 0;
}
