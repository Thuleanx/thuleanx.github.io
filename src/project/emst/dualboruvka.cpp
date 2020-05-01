#include <bits/stdc++.h>
#include "fairsplittree.cpp"
#include "dsu.cpp"
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define mp make_pair

using ld = long double;
using point = array<ld, DIM>;


int init_dfs(fairnode* cur) {
	cur->complete = cur->lt == NULL;
	if (cur->lt) cur->i = init_dfs(cur->lt);
	if (cur->rt) cur->i = init_dfs(cur->rt);
	return cur->i;
}

void pull(fairnode* Q) {
	if (Q->lt) {
		Q->complete |= Q->lt->complete && Q->rt->complete && root(Q->lt->i) == root(Q->rt->i);
	}
}

void update(fairnode* Q, vector<ld> &d) {
	if (Q == NULL) return;
	
	d[root(Q->i)] = loo; // reset d(C_q)

	if (Q->d == loo) return;
	update(Q->lt, d); update(Q->rt,d);
	pull(Q); 
	Q->d = loo;
}

void revolve(fairnode* Q, fairnode* R, vector<ld> &d, vector<pair<int,int>> &con);
void revolve2(fairnode* Q, fairnode* R, vector<ld> &d, vector<pair<int,int>> &con);

int cnt = 0;

ld boundUpdate(fairnode* Q, vector<ld> &d) {
	if (Q->lt == NULL) return d[root(Q->i)];
	return max(boundUpdate(Q->lt, d), boundUpdate(Q->rt, d));
}

// findComponentNeighbors
void FCN(fairnode* Q, fairnode* R, vector<ld> &d, vector<pair<int,int>> &con) {
	pull(Q); pull(R);
	if (Q->complete && R->complete && root(Q->i) == root(R->i)) {
		return;
	} else if (dbox2(Q->R, R->R) > Q->d) {
		return;
	} else if (Q->lt == NULL && R->lt == NULL) { 
		ld dist = dist2(pi[Q->i], pi[R->i]);
		if (dist < d[root(Q->i)]) {
			con[root(Q->i)] = make_pair(Q->i, R->i);
			d[root(Q->i)] = dist;
		}
		Q->d = d[root(Q->i)];
	} else if (Q->lt == NULL) revolve(Q,R,d,con);
	else if (R->lt == NULL) revolve2(Q,R,d,con);
	else {
		revolve(Q->lt,R,d,con);
		revolve(Q->rt,R,d,con);
	}
	if (Q->lt) Q->d = max(Q->lt->d, Q->rt->d);
	pull(Q); pull(R);
	cnt++;
}

void revolve(fairnode* Q, fairnode* R, vector<ld> &d, vector<pair<int,int>> &con) {
	int z = dbox2(Q->R, R->lt->R) < dbox2(Q->R, R->rt->R);
	f(_,0,2) {
		if (z)	FCN(Q, R->lt, d, con);
		else	FCN(Q, R->rt, d, con);
		z ^= 1;
	}
	if (Q->lt) Q->d = max(Q->lt->d, Q->rt->d);
}

void revolve2(fairnode* Q, fairnode* R, vector<ld> &d, vector<pair<int,int>> &con) {
	int z = dbox2(Q->lt->R, R->R) < dbox2(Q->rt->R, R->R);
	f(_,0,2) {
		if (z)	FCN(Q->lt, R, d, con);
		else	FCN(Q->rt, R, d, con);
		z ^= 1;
	}
	if (Q->lt) Q->d = max(Q->lt->d, Q->rt->d);
}


ld dualboruvkakdtree() {
	int n = pi.size();

	vector<vector<int>> L(DIM, vector<int>(n));
	f(i,0,n) f(j,0,DIM)
		L[j][i] = i;

	f(j,0,DIM) sort(begin(L[j]), end(L[j]), [&](int i, int k) {
		return pi[i][j] < pi[k][j];
	});

	poly R = poly(pi);
	fairnode* rootnode = new fairnode(R);
	split(rootnode, L);

	init();
	init_dfs(rootnode);

	ld ans = 0;

	vector<int> forest;
	f(i,0,n) forest.push_back(i);
	vector<ld> d(n, loo);
	vector<pair<int,int>> edges(n);

	while (sz[root(0)] < n) {
		FCN(rootnode, rootnode, d, edges);

		// at least halves the number of components
		for (int x : forest) {
			auto pp = edges[x];
			int v = pp.first, w = pp.second;
			if (root(v) != root(w)) {
				ans += sqrt(d[root(v)]);
				merge(v, w);
			}
		}
		vector<int> nxtforest;
		for (int x : forest) if (root(x) == x)
			nxtforest.push_back(x);
		forest = nxtforest;

		// reset distances and update complete
		update(rootnode, d);
	}

	return ans;
}

int main() {
	int n; cin>>n;
	pi = vector<point>(n);
	f(i,0,n) f(j,0,DIM) cin>>pi[i][j];

	cout << setprecision(40) << dualboruvkakdtree() << endl;

	return 0;
}
