#ifndef WSPD
#define WSPD

#include <bits/stdc++.h>
#include "fairsplittree.cpp"
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define mp make_pair

void findPair(fairnode* a, fairnode* b, vector<pair<fairnode*, fairnode*>> &wspd) {
	// 2r <= dball -> 4r^2 <= dball^2
	if (well_separated(a,b))
		wspd.push_back(mp(a,b));
	else {
		if (a->R.computeLmax() <= b->R.computeLmax()) {
			findPair(a, b->lt, wspd);
			findPair(a, b->rt, wspd);
		} else {
			findPair(a->lt, b, wspd);
			findPair(a->rt, b, wspd);
		}
	}
}

void dfsFindWSPD(fairnode* cur, vector<pair<fairnode*, fairnode*>> &wspd) {
	if (cur->lt) {
		findPair(cur->lt, cur->rt, wspd);
		dfsFindWSPD(cur->lt, wspd);
		dfsFindWSPD(cur->rt, wspd);
	}
}

#endif
