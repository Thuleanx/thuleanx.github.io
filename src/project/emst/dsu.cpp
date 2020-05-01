#ifndef DSU
#define DSU
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;
int dsu[N], sz[N];
void init() {
	f(i,0,N) dsu[i] = i, sz[i] = 1;
}
int root(int i) { return dsu[i] = dsu[i] == i ? i : root(dsu[i]); }
void merge(int i, int j) {
	i = root(i); j = root(j);
	if (i == j) return;
	if (sz[i] < sz[j]) swap(i,j);
	dsu[j] = i; sz[i] += sz[j];
}
#endif
