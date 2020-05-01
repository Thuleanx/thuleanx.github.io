#include <bits/stdc++.h>
#include "kdtree.cpp"
#include "dsu.cpp"
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define mt make_tuple
#define mp make_pair

using ld = long double;
using point = array<ld, DIM>;
using pdd = pair<ld,ld>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// use uniform_int_distribution<int>(0, i)(rng)

int n;
bool frag[N];
point p[N];
ld den[N];
using pii = pair<int,int>;
using vi = vector<int>;

int get_closest(knode* root, int i) {
	knode* clo = near(p[i], root, poly(), NULL, loo);
	return clo->i;
}

ld naive() {
	knode* root = NULL;
	f(i,1,n) root = insert(p[i], i, root, 0);
	priority_queue<tuple<ld,int,int>> pq;
	frag[0] = 1;
	{
		int c = get_closest(root, 0);
		pq.push(mt(-dist2(p[c], p[0]), 0, c));
	}
	ld cost = 0;
	f(_,0,n-1) {
		while (frag[get<2>(pq.top())]) {
			auto pp = pq.top(); pq.pop();
			int x = get<1>(pp);
			int i = get_closest(root, x);
			pq.push(mt(-dist2(p[i], p[x]), x, i));
		}
		auto pp = pq.top();
		int x = get<1>(pp), y = get<2>(pp);
		cost += sqrt(-get<0>(pp));
		frag[y] = 1;
		root = erase(p[y], root); 
		if (root != NULL) {
			int i = get_closest(root, y);
			pq.push(mt(-dist2(p[i], p[y]), y, i));
		}
	}
	return cost;
}

ld multifragment(int m0) {
	f(i,0,n) den[i] = 0;
	int q[n];
	f(i,0,n) q[i] = i;
	sort(q,q+n,[&](int i, int j) { 
		return den[i] < den[j];
	});
	init();

	knode* node = NULL;
	f(i,0,n) node = insert(p[i], i, node, 0);

	priority_queue<tuple<ld,int,int>> pq;

	ld ans = 0;

	int num = 0;
	f(z,0,n) if (!frag[q[z]]) {
		node = erase(p[q[z]], node);
		{
			frag[q[z]] = 1; num++;
			if (num == n) break;
			int c = get_closest(node, q[z]);
			pq.push(mt(-dist2(p[q[z]], p[c]), q[z], c));
		}
		for (int cnt = 0; cnt < m0 && num < n; ) {
			cnt = 0;
			while (cnt < m0 && root(get<1>(pq.top())) == root(get<2>(pq.top()))) {
				auto pp = pq.top(); pq.pop();
				int x = get<1>(pp);
				int i = get_closest(node, x);
				pq.push(mt(-dist2(p[x],p[i]), x, i));
				cnt++;
			}
			if (cnt == m0) break;
			auto pp = pq.top();
			int x = get<1>(pp), y = get<2>(pp);
			ans += sqrt(-get<0>(pp));
			merge(x, y);
			if (frag[y]) 
				break;
			frag[y] = 1; num++;
			node = erase(p[y], node);
			if (node != NULL) {
				int i = get_closest(node, y);
				pq.push(mt(-dist2(p[y], p[i]), y, i));
			}
		}
	}
	node = NULL;
	priority_queue<pii> pq2; 
	vi gr[n];
	f(i,0,n) {
		node = insert(p[i], i, node, 0);
		if (root(i) == i) pq2.push(pii(-sz[i], i));
		gr[root(i)].push_back(i);
	}

	// should be O(n\log{n}*complexity of insert and delete into kd tree)
	while (pq2.size()>1) {
		auto pp = pq2.top(); pq2.pop();
		int i = pp.second;
		if (sz[root(i)] != -pp.first) continue;
		for (int x : gr[i]) 
			node = erase(p[x], node);
		pair<ld, int> best = mp(oo, -1);
		for (int x : gr[i]) {
			int y = get_closest(node, x);
			best = min(best, mp(ld(-dist2(p[x],p[y])), y));
		}
		for (int x : gr[i]) 
			node = insert(p[x], x, node, 0);
		ans += -best.first;
		merge(i, best.second);
		int z = i;
		if (sz[i] < sz[root(best.second)])
			z = root(best.second);
		pq2.push(mp(-sz[z], z));
	}

	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n;
	f(i,0,n) f(j,0,DIM) cin>>p[i][j];
	
	// randomize
	f(i,0,n) {
		swap(p[i], p[uniform_int_distribution<int>(0,i)(rng)]);
	}

	/* cout << setprecision(40) << naive() << endl; */
	cout << setprecision(40) << multifragment(30) << endl;

	return 0;
}
