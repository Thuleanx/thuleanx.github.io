
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i>=a; i--)
#define IN(i,a,b) (a<=(i) && (i)<=b)
#define mp make_pair
#define mt make_tuple

const int N = 3e5, oo = 1e9;
int n;
int a[N], b[N], c[N];

struct SegTreeMin {
	int t[N<<1];
	SegTreeMin() { f(i,0,N) t[i+N] = i; }
	int comb(int i, int j) { return a[i] < a[j] ? i : j; }
	void build() {  for (int i = n - 1; i > 0; --i) t[i] = comb(t[i<<1], t[i<<1|1]); }
	void modify(int p, int value) {  // set value at position p
		for (a[p] = value; p > 1; p >>= 1) t[p>>1] = comb(t[p], t[p^1]);
	}
	int query(int l, int r) {  // sum on interval [l, r)
		int res = 0;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l&1) res = comb(res, t[l++]);
			if (r&1) res = comb(res, t[--r]);
		}
		return res;
	}
};

struct SegTreeMax {
	int t[N<<1];
	SegTreeMax() { f(i,0,N) t[i+N] = i; }
	int comb(int i, int j) { return b[i] > b[j] ? i : j; }
	void build() {  for (int i = n - 1; i > 0; --i) t[i] = comb(t[i<<1], t[i<<1|1]); }
	void modify(int p, int value) {  // set value at position p
		for (b[p] = value; p > 1; p >>= 1) t[p>>1] = comb(t[p], t[p^1]);
	}
	int query(int l, int r) {  // sum on interval [l, r)
		int res = 0;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l&1) res = comb(res, t[l++]);
			if (r&1) res = comb(res, t[--r]);
		}
		return res;
	}
};

void init() {
	f(i,0,N) a[i] = oo, b[i] = -oo;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	stringstream ss;

	SegTreeMin ds1;
	SegTreeMax ds2;
	while (t--) {
		cin>>n;
		f(i,0,n) cin>>a[i];
		f(i,0,n) b[i]  = a[i], c[i] = a[i];

		ds1.build(); 
		ds2.build();


		priority_queue<tuple<int,int,int>> pq;
		pq.push(mt(0,0,-1)); // -weight, to, from

		long long ans = 0;

		bool vis[n];
		f(i,0,n) vis[i] = 0;

		auto query = [&](int v) {
			int l = ds2.query(0, v); // left of v, which ones are highest
			int r = ds1.query(v, n); // right of v, which ones are lowest
			return c[v] - b[l] < a[r] - c[v] ? l : r;
		};

		while (pq.size()) {
			auto pp = pq.top(); pq.pop();
			int wei = get<0>(pp), to = get<1>(pp), from = get<2>(pp);

			if (!vis[to]) {
				ans += wei; vis[to] = 1;
				cout << ds1.query(1, n) << endl;
				ds1.modify(to, oo);
				ds2.modify(to, -oo);

				// update to
				int w = query(to);
				cout << to << " " << w << endl;

				if (!vis[w]) pq.push(mt( -(w < to ? c[to]-c[w] : c[w]-c[to]) , w, to ));
			}
			
			// update from
			if (from != -1) {
				int w = query(from);
				if (!vis[w]) pq.push(mt( -(w < from ? c[from]-c[w] : c[w]-c[from]) , w, from ));
			}
		}

		ss << ans << endl;
	}
	cout << ss.str();
		

	return 0;
}
