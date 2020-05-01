#include <bits/stdc++.h>
#include "WSPD.cpp"
#include "fairsplittree.cpp"
#include "dsu.cpp"
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define mp make_pair

using ld = long double;
using point = array<ld, DIM>;

void BCP(fairnode* a, fairnode *b, int &v, int &w, ld &D) {
	if ((a->i != -1) && (b->i != -1)) {
		ld dist = dist2(pi[a->i], pi[b->i]);
		if (dist < D) {
			D = dist;
			v = a->i; w = b->i;
		}
	} else {
		if (a->R.diam2() < b->R.diam2()) swap(a, b);
		ld L = dbox2(a->lt->R,b->R),
		   R = dbox2(a->rt->R,b->R);
		// explore the more promising subtree first
		int cur = L<R;
		f(_,0,2) {
			if (cur && L < D) BCP(a->lt, b, v, w, D);
			if (!cur && R < D) BCP(a->rt, b, v, w, D);
		}
	}
}

int getrep(fairnode* cur) {
	if (cur->i != -1) return cur->i;
	else return cur->i = getrep(cur->lt);
}

ld geomst2() {
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
	cout << "FIN BUILDING TREE" << endl;

	vector<pair<fairnode*, fairnode*>> wspd;
	dfsFindWSPD(rootnode, wspd);

	priority_queue<pair<ld, int>> pq;
	int m = wspd.size();

	bool computedBCP[m];
	f(i,0,m) {
		pq.push(mp(-dbox2(wspd[i].first->R, wspd[i].second->R), i));
		computedBCP[i] = 0;
	}
	ld bcp[m];

	ld ans = 0;
	init();
	while (pq.size()) {
		auto pp = pq.top(); pq.pop();
		int i = pp.second;

		int a = getrep(wspd[i].first), b = getrep(wspd[i].second);
		if (root(a) != root(b)) {
			if (computedBCP[i]) {
				ans += sqrt(bcp[i]);
				merge(a, b);
			} else {
				int u, v; ld D = loo;
				BCP(wspd[i].first, wspd[i].second, u, v, D);
				
				pq.push(mp(-D, i));

				bcp[i] = D;
				computedBCP[i] = 1;
			}
		}
	}
	

	return ans;
}

int main() {
	int n; cin>>n;
	pi = vector<point>(n);
	f(i,0,n) f(j,0,DIM) cin>>pi[i][j];

	cout << setprecision(40) << geomst2() << endl;

	return 0;
}

