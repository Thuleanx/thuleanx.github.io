/*
 * Problem: Lunch Time Name Recall
 * Platform: Kattis
 * Contest: North American Championship 2020
 * Date: 27022020
 * Score: +3
 * Description: We simply brute force. Each day we have a partition for the people there. 
 *	If we sort the partition, the number of partitions of 30 seems very small (5k ish). We also 
 *	omit 1 for simplicity. Each state of our dp is (day, stuff yet partition, stuff partitioned, 
 *	number of burgers left to use on this day). Overall, there could be roughly 10^6 states. And
 *	for each we do O(N) work, so we get a nice complexity
 * Tags: bruteforce,highschool
 */
#include <bits/stdc++.h>
using namespace std;

const int N = 30, D = 10;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = b-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair

using vi = vector<int>;

map<pair<vi,vi>, int> hmap[D][N];

int n, d;
int nb[D];

void ins(vector<int> &a, int x) {
	int i = a.size();
	a.push_back(x);
	while (i > 0 && a[i] < a[i-1]) {
		swap(a[i], a[i-1]);
		i--;
	}
}

// don't we need hashing?
int dp(int i, vector<int> a, vector<int> b, int h, int n1, int lt) {
	h = min(h, lt-h);
	if (h < 0) return 0;

	auto pp = mp(a,b);

	if (!a.size()) {
		if (h>n1) return 0;
		if (i == d-1) return n1;
		return hmap[i][h][pp] = dp(i+1, b, vector<int>(), nb[i+1], n1, n);
	}
	
	auto iter = hmap[i][h].find(pp);
	if (iter != hmap[i][h].end())
		return iter->second;


	// from back
	int x = a.back(); a.pop_back();

	int ans = 0;
	// want lt >= h -> so element need to be so that k >= h+x-lt
	f(k,max(0,h+x-lt),min(x+1, h+1)) {
		vector<int> aa(a), bb(b);
		if (k>1) ins(bb,k);
		if (x-k>1) ins(bb, x-k); 
		ans = max(ans, dp(i, aa, bb, h-k, n1 + (k==1) + (x-k == 1), lt - x));
	}

	return hmap[i][h][pp] = ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>d;
	f(i,0,d) cin>>nb[i];

	vector<int> a;
	a.push_back(n);

	cout << dp(0, a, vector<int>(), nb[0], 0, n) << endl;

	return 0;
}
