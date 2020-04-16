#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
using ll = long long;
using vi = vector<int>;

const int N = 2e5;
int n;
int a[N];
vi pos[N];

struct BIT {
	int tree[N];
	BIT() { f(i,0,N) tree[i] = 0; }
	void add(int i, int x) {
		for (; i < N; i |= i+1) 
			tree[i] += x;
	}
	int sum(int i) {
		int ans = 0;
		for (; i >= 0; i = (i&(i+1))-1)
			ans += tree[i];
		return ans;
	}
	void clear() {
		f(i,0,N) tree[i] = 0;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	freopen("haircut.in", "r", stdin);
	freopen("haircut.out", "w", stdout);

	cin>>n;
	f(i,0,n) cin>>a[i];

	ll ans = 0;
	BIT ds;
	f(i,0,n) {
		ans += i - ds.sum(a[i]);
		ds.add(a[i], 1);
	}
	ds.clear();
	f(i,0,n) pos[a[i]].push_back(i); 	

	stringstream ss;
	ll res[n+1];
	fr(i,0,n+1) {
		for (int j : pos[i]) ans -= ds.sum(j);
		for (int j : pos[i]) ds.add(j, 1);
		res[i] = ans;
	}
	f(i,0,n) ss << res[i] << endl;
	cout << ss.str();

	return 0;
}
