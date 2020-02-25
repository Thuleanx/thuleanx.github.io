
/*
 * Problem: ICPC Camp
 * Platform: Kattis
 * Contest: North American Championship 2020
 * Date: 24022020
 * Score: +5
 * Description: First, we guess a value for the answer, say $D$. You realize that $x[i]$ can be paired with anything in the range
 *		$\max(0, x[i]-d)$ to $\min(s-x[i], x[i]+d)$. You can greedy pair by going from lowest to highest $y[i]$ and pair it with the 
 *		most constrained x[i]
 * Tags: binarysearch,greedy
 */
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5+7, oo = 1e9+7;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = b-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)

int k,n,m,s;
int x[N], y[N];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>k>>n>>m>>s;
	f(i,0,n) cin>>x[i];	
	f(i,0,m) cin>>y[i];
	sort(x,x+n); sort(y,y+m);

	int lo = 0, hi = oo;

	while (lo <= hi) {
		int d = lo+hi>>1;

		int cnt = 0;
		priority_queue<int,vector<int>,greater<int>> pq;

		int j = 0;
		f(i,0,m) {
			while (j < n && max(0, x[j]-d) <= y[i]) {
				pq.push(min(s-x[j], x[j]+d));
				j++;
			}
			while (pq.size() && pq.top() < y[i]) pq.pop();
			if (pq.size()) {
				cnt++;
				pq.pop();
			}
		}
		if (cnt >= k)	hi = d-1;
		else			lo = d+1;
	}
	
	cout << (lo==oo+1?-1:lo) << endl;
	
	

	return 0;
}
