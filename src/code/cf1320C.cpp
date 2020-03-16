#include <bits/stdc++.h>
using namespace std;

const int N = 1e6+7;
const long long oo = 1e18;
int n, m, p;

#define f(i,a,b) for (int i = a; i < b; i++)
#define mp make_pair
#define mt make_tuple


struct SegTree {
	long long tree[N<<2], lazy[N<<2];
	SegTree () {
		f(i,0,N<<2) tree[i] = -oo, lazy[i] = 0;
	}
	void add(int i, int lo, int hi, int l, int r, long long amt) {
		if (lo > hi) return ;
		push(i);
		if (lo > r || hi < l) return ;
		if (l <= lo && hi <= r) {
			lazy[i] += amt;
			push(i);
		} else {
			int mid = lo+hi>>1;
			add(i<<1, lo, mid, l, r, amt);
			add(i<<1|1, mid+1, hi, l, r, amt);
			tree[i] = max(tree[i<<1],tree[i<<1|1]);
		}
	}
	long long query(int i, int lo, int hi, int l, int r) {
		if (lo > hi) return -oo;
		push(i);
		if (lo > r || hi < l) return -oo;
		if (l <= lo && hi <= r)
			return tree[i];
		else {
			int mid = lo+hi>>1;
			return max(query(i<<1, lo, mid, l, r), query(i<<1|1, mid+1, hi, l, r));
		}
	}
	void push(int v) {
		if (lazy[v]) {
			tree[v] += lazy[v];
			if ((v<<1) < (N<<2)) {
				lazy[v<<1] += lazy[v];
				lazy[v<<1|1] += lazy[v];
			}
			lazy[v] = 0;
		}
	}
	void add(int lo, int hi, long long amt) { 
		add(1,0,N-1,lo,hi,amt); 
	}
	long long query(int lo, int hi) { return query(1,0,N-1,lo,hi); }
	void sett(int i, long long amt) {
		add(i,i,amt-query(i,i));
	}
};

long long a[N];
tuple<int,int,int> c[N];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>m>>p;
	SegTree ds;
	f(i,0,N) a[i] = oo;
	f(i,0,n) {
		int x, y; cin>>x>>y;
		a[x] = min(a[x],(long long) y);
	}
	f(i,0,m) {
		int x,y; cin>>x>>y;
		if (ds.query(x,x) < -y)
			ds.sett(x,-y);	
	}
	f(i,0,p) {
		int x, y, z; cin>>x>>y>>z;
		c[i] = mt(x,y,z);
	}
	sort(c,c+p);
	int z = 0;

	long long ans = -oo;
	f(i,0,N) if (a[i] != oo) {
		while (z < p && get<0>(c[z]) < i) {
			ds.add(get<1>(c[z])+1,N-1,get<2>(c[z]));
			z++;
		}
		ans = max(ans,ds.query(0,N-1)-a[i]);
	}
	cout << ans << endl;
	
	return 0;
}
