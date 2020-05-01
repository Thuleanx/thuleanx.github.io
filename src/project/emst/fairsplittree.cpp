#ifndef FST
#define FST

#include <bits/stdc++.h>
#include "doubly_linked_list.cpp"
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define mp make_pair

using ld = long double;
using point = array<ld, DIM>;

vector<point> pi;
vector<int> gr;
vector<node*> refe[DIM];

struct fairnode {
	fairnode *lt, *rt;
	poly R;
	int i;

	/*
	 * This information is only used in the dualboruvka algorithm
	 */
	ld d = loo;
	bool complete = 0;

	fairnode(poly R) : R(R) {
		i = -1;
		lt = rt = NULL;
	}
};

poly computeR(doublylinked L[]) {
	poly R;
	f(i,0,DIM) R.lo[i] = pi[L[i].fi->i][i], R.hi[i] = pi[L[i].la->i][i];
	return R;
}


/* L[i][j] -> the jth in the ith dimension */
void split(fairnode* cur, vector<vector<int>> &L) {
	int n = L[0].size();	
	if (!gr.size()) {
		gr = vector<int>(n, oo);
		f(i,0,DIM) refe[i] = vector<node*>(n, NULL);
	}
	if (n == 1) {
		cur->i = L[0][0];
		return;
	}
	for (int x : L[0]) gr[x] = oo;

	int g = 1;
	vector<fairnode*> cursors;

	compute: {
		doublylinked L2[DIM];
		f(i,0,DIM) for (int x : L[i]) refe[i][x] = L2[i].addLast(x);

		poly R = cur->R; 
		// compute R(L)
		while (2*n > L[0].size()) {
			int d = 0;
			f(i,0,DIM) if (R.hi[i] - R.lo[i] > R.hi[d] - R.lo[d]) d = i;

			ld h = (R.hi[d] + R.lo[d]) / 2;

			node* lt = L2[d].fi, *rt = L2[d].la; 
			int bi = 1;
			while (pi[lt->i][d] < h && pi[rt->i][d] > h) {
				if (bi) lt = lt->nxt;
				else	rt = rt->pa;
				bi ^= 1;	
			}

			bool goright = 0;
			poly RL, RR;
			RL.reset();
			RR.reset();

			if (pi[lt->i][d] >= h) {
				lt = L2[d].fi;					
				
				while (pi[lt->i][d] < h) {
					gr[lt->i] = g-1;	
					RL.add(pi[lt->i]);
					f(j,0,DIM) L2[j].erase(refe[j][lt->i]);
					lt = lt->nxt;
					n--;
				}
				RR = computeR(L2);
				goright = 1;
			} else {
				rt = L2[d].la;

				while (pi[rt->i][d] > h) {
					gr[rt->i] = g-1;
					RR.add(pi[rt->i]);
					f(j,0,DIM) L2[j].erase(refe[j][rt->i]);
					rt = rt->pa;
					n--;
				}
				RL = computeR(L2);
			}

			cur->lt = new fairnode(RL);
			cur->rt = new fairnode(RR);

			if (goright) {
				cursors.push_back(cur->lt);
				cur = cur->rt;	
				R = RR;
			} else {
				cursors.push_back(cur->rt);
				cur = cur->lt;
				R = RL;
			}
			g++;
		}
		cursors.push_back(cur);
	}
	n = L[0].size();

	for (int x : L[0]) if (gr[x] == oo)
		gr[x] = g-1;
	vector<vector<vector<int>>> dorime(g,vector<vector<int>>(DIM));
	f(j,0,DIM) f(i,0,n)
		dorime[gr[L[j][i]]][j].push_back(L[j][i]);

	f(i,0,g) split(cursors[i], dorime[i]);

	/* return dorime; */
}

bool well_separated(fairnode* a, fairnode* b) {
	ld balldist = dball(a->R, b->R);
	return balldist * balldist  >= 4*max(a->R.diam2(), b->R.diam2());
}

#endif
