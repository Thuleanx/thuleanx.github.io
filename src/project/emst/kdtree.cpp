#include <bits/stdc++.h>
#include "poly.cpp"
using namespace std;

using ld = long double;
#define f(i,a,b) for (int i = a; i < b; i++)
#define IN(i,a,b) (a<=i && i<=b)

// for 2d computation is much faster if this is represented as a complex number
// for 3d the same is true if you represent points as quaternions
using point = array<ld, DIM>;  

struct knode {
	int di, i;
	point p;
	knode *lt, *rt;		

	knode(int di, int i, point p, knode *lt, knode *rt) : di(di), i(i), p(p), lt(lt), rt(rt) {}
	~knode() {
		delete lt;
		delete rt;
	}
	ld dist(point q) { return q[di] - p[di]; }
};

knode* insert(point p, int i, knode* cur, int di) {
	if (cur == NULL)
		return new knode(di, i, p, NULL, NULL);
	else if (cur->p == p)
		exit(11111);
	else if (cur->dist(p) < 0) // left 
		cur->lt = insert(p, i, cur->lt, (di+1)%DIM);	
	else 
		cur->rt = insert(p, i, cur->rt, (di+1)%DIM);
	return cur;
}

knode* findMin(knode* cur, int di) {
	if (cur == NULL)
		return NULL;
	knode* best = cur;
	if (cur->lt) {
		knode* cp = findMin(cur->lt, di);
		if (cp->p[di] < best->p[di]) best = cp;
	}
	if (cur->rt && di != cur->di) {
		knode* cp = findMin(cur->rt, di);
		if (cp->p[di] < best->p[di]) best = cp;
	}
	return best;
}

knode* erase(point p, knode* cur) {
	if (cur == NULL)
		exit(22222);
	if (cur->p == p) {
		if (cur->rt) {
			knode* small = findMin(cur->rt, cur->di);
			cur->p = small->p;
			cur->i = small->i;
			cur->rt = erase(cur->p, cur->rt);
		} else if (cur->lt) {
			knode* small = findMin(cur->lt, cur->di);
			cur->p = small->p;
			cur->i = small->i;
			cur->rt = erase(cur->p, cur->lt);
			cur->lt = NULL;
		} else return NULL;
	} else if (cur->dist(p) < 0)
		cur->lt = erase(p, cur->lt);
	else cur->rt = erase(p, cur->rt);
	return cur;
}

knode* relax(point p, knode* best, ld &best_dist, knode* other) {
	if (other == NULL) return best;
	ld d = dist2(p, other->p);
	if (d < best_dist) {
		best_dist = d;
		return other;
	}
	return best;
}

knode* near(point p, knode* cur, poly rect, knode* best, ld best_dist) {
	if (cur == NULL || rect.dist2(p) > best_dist) 
		return best;
	best = relax(p, best, best_dist, cur);
	int op = p[cur->di] < cur->p[cur->di];
	// go for closer rectangles
	f(_,0,2) {
		if (op) best = relax(p, best, best_dist, near(p, cur->lt, rect.cut(cur->di, cur->p[cur->di], 0), best, best_dist));
		else	best = relax(p, best, best_dist, near(p, cur->rt, rect.cut(cur->di, cur->p[cur->di], 1), best, best_dist));
		op ^= 1;
	}
	return best;
}

void trav(knode* cur) {
	if (cur == NULL) return ;
	cout << cur->i << ": ";
	f(j,0,DIM) cout << cur->p[j] << " ,"[j==DIM-1];
	if (cur->lt)
		trav(cur->lt); 
	if (cur->rt)
		trav(cur->rt);
}

/* mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); */

/* int main() { */
/* 	int n; cin>>n; */
/* 	point p[n]; */
/* 	f(i,0,n) f(j,0,DIM) cin>>p[i][j]; */
	
/* 	knode* root = NULL; */
/* 	f(i,0,n) swap(p[i], p[uniform_int_distribution<int>(0, i)(rng)]); */
/* 	f(i,1,n) root = insert(p[i], i, root, 0); */

/* 	trav(root); */
/* 	cout << endl << "ERASE: "; */
/* 	f(j,0,DIM) cout << p[1][j] << " \n"[j==DIM-1]; */
/* 	root = erase(p[1], root); */
/* 	cout << endl; */
/* 	trav(root); */

/* 	return 0; */
/* } */
