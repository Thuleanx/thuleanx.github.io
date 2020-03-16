/*
 * Problem: Editing Explosion
 * Platform: Kattis
 * Contest: North American Championship 2020
 * Date: 27022020
 * Score: +
 * Description: We simply have states as rows in our dp table. Each time we
 *		add a character, we transition into a new state. We only accept
 *		paths with final states where the end is d. Notice that in a row, 
 *		the difference between two adjacent variables is no more than 1.
 *		Therefore, our graph only considers rows such that the first element is
 *		at most n+d (this prunes our search space a lot). Since this graph
 *		is a DAG, counting the number of paths from the starting node to 
 *		a node with a certain property takes O(number of vertices + number of edges)
 *		which happens to be low. Testing on ABCDEFGHIJ 10 takes only 4 secs.
 * Tags: bruteforce,dp,highschool
 */
#include <bits/stdc++.h>
using namespace std;

const int N = 10, oo = 1e9, MOD = 998244353, M = 1e6;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = b-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair

using vi = vector<int>;

int n, d, p = 0;

map<vi, int> vertices;
string s;
vi arr;

int vis[M];
long long dp[M];
vector<int> adj[M];

int add(vi &a) {
	return vertices[a] = p++;
}

// from [0]*n -> something
long long dfs(vector<int> &a, int v) {
	if (vis[v]) return dp[v];
	if (a[0] > n+d) return 0;
	dp[v] = a.back() == d;
	vis[v] = 1;

	f(c, 'A', 'Z' + 1) {
		vi g(n+1, oo);
		f(j,0,n+1) {
			g[j] = a[j] + 1;
			if (j) g[j] = min(g[j], g[j-1] + 1);
			if (j) g[j] = min(g[j], a[j-1] + (c != s[j-1]));
		}
		if (g[n] > n+d) continue;
		
		int w;
		auto pp = vertices.find(g);
		if (pp != vertices.end())
			w = pp->second;
		else w = add(g);

		dp[v] += dfs(g, w);	
		if (dp[v] >= MOD) dp[v] -= MOD;
	}
	return dp[v];
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>s>>d;
	n = s.length();
	arr = vector<int>(n+1);


	vi st(n+1);
	f(i,0,n+1) st[i] = i;

	add(st);

	cout << dfs(st, 0) << endl;


	return 0;
}
