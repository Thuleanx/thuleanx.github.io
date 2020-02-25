#include <bits/stdc++.h>
using namespace std;

const int N = 1e5, M = 101;

int n;
int a[N];
int tree[N<<1];
vector<int> pos[M];

int gcd(int a, int b) {
	return a?gcd(b%a, a):b;
}
void build() {
	for (int i = 0; i < N; i++)
		tree[i+N] = a[i];
	for (int i = N-1; i >= 1; i--)
		tree[i] = gcd(tree[i<<1], tree[i<<1|1]);
}

int query(int l, int r) {
	int res = 0; r++;
	for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
		if (l&1) res = gcd(res, tree[l++]);
		if (r&1) res = gcd(res, tree[--r]);
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n;
	for (int i = 0; i < n; i++) {
		cin>>a[i];
		for (int x = 1; x <= a[i]; x++)
			if (a[i] % x == 0) pos[x].emplace_back(i);
	}
	build();

	int cnt = 0;
	for (int x = 1; x <= 100; x++) {
		for (int i = 0; i < pos[x].size(); i++) {
			int j = i+1;
			while (j < pos[x].size() && pos[x][j] == pos[x][j-1]+1) j++;
			int res = query(pos[x][i], pos[x][j-1]);
			if (res == x) {
				cnt++;
				break;
			}
			i = j-1;
		}
	}

	cout << cnt << endl;

	return 0;
}
