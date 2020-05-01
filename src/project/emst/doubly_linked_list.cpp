#include <bits/stdc++.h>
#include "poly.cpp"
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)

struct node {
	node *pa, *nxt;
	int i;
	node(int i, node* pa, node* nxt) : i(i), pa(pa), nxt(nxt) {}
};

struct doublylinked {
	node *fi, *la;

	doublylinked() {
		fi = la = NULL;
	}

	// you really only need addlast and delete
	node* addLast(node* cur, node* ls, int i) {
		if (cur == NULL)
			return la = new node(i, ls, NULL);
		else cur->nxt = addLast(cur->nxt, cur, i);
		return cur;
	}
	node* addLast(int i) {
		fi = addLast(fi, NULL, i);
		return la;
	}

	void erase(node* cur) {
		if (cur == fi) fi = cur->nxt;
		if (cur == la) la = cur->pa; 

		if (cur->pa)
			cur->pa->nxt = cur->nxt;
		if (cur->nxt)
			cur->nxt->pa = cur->pa;
		/* cur->pa = cur->nxt = NULL; */
	}
};

/* int main() { */
/* 	int n; cin>>n; */
/* 	doublylinked ls; */

/* 	node* re[n]; */
/* 	f(i,0,n) re[i] = ls.addLast(i); */

/* 	ls.erase(re[5]); */
/* 	ls.erase(re[3]); */

/* 	{ */
/* 		node* cur = ls.fi; */
/* 		while (cur) { */
/* 			cout << (cur->i) << " "; */
/* 			cur = cur->nxt; */
/* 		} */
/* 		cout << endl; */
/* 	} */

/* 	{ */
/* 		node* cur = ls.la; */
/* 		while (cur) { */
/* 			cout << (cur->i) << " "; */
/* 			cur = cur->pa; */
/* 		} */
/* 		cout << endl; */
/* 	} */

/* 	return 0; */
/* } */
