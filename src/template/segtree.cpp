#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple

using vi = vector<int>;

const int oo = 1e9;

struct SegTree {
	int N;
	vi tree;
	SegTree(int N) : N(N), tree(vi(N<<1, -oo)) {}
	int cob(int a, int b) { return max(a, b); }
	void build() {
		fr(i,1,N) tree[i] = cob(tree[i<<1], tree[i<<1|1]);
	}
	void update(int pos, int val) {
		for (tree[pos += N] = val; pos; pos >>= 1)
			tree[pos>>1] = cob(tree[pos], tree[pos^1]);
	}
	int query(int a, int b) { // [a, b)
		int res = -oo;
		for (a += N, b += N; a < b; a >>= 1, b >>= 1) {
			if (a&1) res = cob(res, tree[a++]);
			if (b&1) res = cob(tree[--b], res);
		}
		return res;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	return 0;
}
