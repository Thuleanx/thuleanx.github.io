#include <bits/stdc++.h>
using namespace std;

const int N = 2e5;

int a[N];
struct BIT {
	long long tree[N];
	BIT() {
		for (int i = 0; i < N; i++)
			tree[i] = 0;
	}
	void add(int v, int x) {
		for (; v < N; v |= v+1)
			tree[v] += x;
	}
	long long sum(int v) {
		long long ans = 0;
		for (; v >= 0; v = (v&(v+1))-1)
			ans += tree[v];
		return ans;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);


	int t; cin>>t;
	stringstream ss;

	BIT tree;
	while (t--) {
		int n, q; 
		cin>>n>>q;
		while (q--) {
			int tp, x, y;
			cin>>tp>>x>>y;
			if (tp == 1) {
				x--;
				tree.add(x,-a[x]);
				a[x] = y;
				tree.add(x,a[x]);
			} else
				ss << tree.sum(y-1) - tree.sum(x-2) << endl;
		}
	}
	cout << ss.str();
	return 0;
}
