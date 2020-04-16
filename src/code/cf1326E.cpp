
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i>=a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple

const int N = 3e5;
int n;
int p[N], q[N], r[N];

/*
 * add 
 *
 */
struct SegTree {
	int tree[N<<4];
	SegTree() { f(i,0,N<<4) tree[i] = 0; }
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n;
	f(i,0,n) cin>>p[i];
	f(i,0,n) {
		int x; cin>>x;
		p[i]--; q[--x] = i;
	}

	queue<tuple<int,int,int,int>> pq;
	pq.push(mt(0,n-1,0,n-1));

	while (pq.size()) {
		auto pp = pq.front(); pq.pop(); 
		
		int lo = get<0>(pp), hi = get<1>(pp), lox = get<2>(pp), hix = get<3>(pp);

		int mid = lo+hi>>1;

		while (lox <= hix) {
			int x = lox+hix>>1;

			bool gd = 1;

			int a = 0, b = 0;
			fr(i,0,n) {
				a += p[i] > x;
				b += q[i] < mid; // bomb
				gd &= a <= b;
			}

			if (gd) hix = x-1;
			else lox = x+1;
		}
		
		r[mid] = lox;
		lox = get<2>(pp); hix = get<3>(pp);

		if (lo < mid) pq.push(mt(lo, mid-1, r[mid], hix));
		if (mid < hi) pq.push(mt(mid+1, hi, lox, r[mid]));
	}

	stringstream ss;
	f(i,0,n) ss << r[i]+1 << " ";
	cout << ss.str() << endl;

	return 0;
}
