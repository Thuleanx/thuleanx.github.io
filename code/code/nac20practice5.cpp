#include <bits/stdc++.h>
using namespace std;

const int N = 2e5;

int n;
int a[N];
vector<int> adj[N];

struct Node {
	Node *lt, *rt;
	int lo, hi, value, lazy;
	Node(int lo, int hi) : lo(lo), hi(hi) { value = lazy = 0; }
	void add(int l, int r, int x) {
		cout << lo << " " << hi << " " << l << " " << r << endl;
		if (r < lo || l > hi) return;
		if (l <= lo && hi <= r) {
			cout << "back" << endl;
			value += x;
			lazy += x;
		} else {
			push(); 
			assert(lt); assert(rt);
			lt->add(l,r,x); rt->add(l,r,x);
			value = lt->value + rt->value;
		}
	}
	int query(int l, int r) {
		if (r < lo || l > hi) return 0;
		if (l <= lo && hi <= r) return value;
		push();
		return lt->query(l,r) + rt->query(l,r);
	}
	int upper_bound(int x) {
		if (lo == hi) return x<value?lo:N;
		push();
		if (lt->value <= x) return rt->upper_bound(x - lt->value);
		return lt->upper_bound(x);
	}
	void push() {
		if (!lt && lo != hi) {
			int mid = lo+hi>>1;
			lt = new Node(lo, mid); 
			rt = new Node(mid+1, hi);
		}
		if (lt && lazy) lt->add(lo,hi,lazy), rt->add(lo, hi, lazy), lazy = 0;
	}
};

pair<Node*, vector<pair<int,int>>> dfs(int v) {
	Node* ds = new Node(0,N-1); vector<pair<int,int>> ac;
	cout << v << endl;
	for (int w : adj[v]) {
		Node *ds2; vector<pair<int,int>> ac2;
		tie(ds2,ac2) = dfs(w);
		if (ac2.size() > ac.size()) {
			swap(ac,ac2); 
			swap(ds,ds2);
		}
		for (auto pp : ac2) {
			ds->add(pp.first, N-1, pp.second);
			ac.push_back({pp.first,pp.second});
		}
	}
	
	int x = ds->query(0, a[v]-1);
	ac.emplace_back(a[v], 1);
	ds->add(a[v],N-1,1);
	int y = ds->upper_bound(x+1);
	if (y < N) {
		ac.emplace_back(y, -1);
		ds->add(y,N-1,-1);
	}
	cout << "end" << endl;
	return make_pair(ds, ac);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n;
	map<int,int> comp;
	for (int i = 0; i < n; i++) {
		int p;
		cin>>a[i]>>p;
		comp[a[i]] = 0;	
		if (p--) adj[p].push_back(i);
	}
	int p = 0;
	for (auto pp : comp) 
		comp[pp.first] = p++;
	for (int i = 0; i < n; i++)
		a[i] = comp[a[i]];
	Node* ds; vector<pair<int,int>> r;
	tie(ds, r) = dfs(0);
	int ans = 0;
	for (auto pp : r)
		ans = max(ans, ds->query(0, pp.first));
	cout << "HI" << endl;
	cout << ans << endl;

	return 0;
}
