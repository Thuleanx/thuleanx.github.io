
/*
 * Problem: Tomb Raider
 * Platform: Kattis
 * Contest: North American Championship 2020
 * Date: 24022020
 * Score: +4
 * Description: We simply treat this as a problem of implications. If gargoyle A faces a certain way, it implies a 
 *		certain orientation for gargoyle B. This relationship is reflective, thus we can find connected component
 *		in the double implication graph and get the one with lowest cost
 * Tags: 2sat,graph
 */
#include <bits/stdc++.h>
using namespace std;

const int N = 501, oo = 1e9+7;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = b-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)

int n, m;
char board[N][N];

int di[] = {1,-1,0,0};
int dj[] = {0,0,1,-1};

int p1[] = {3,2,1,0}; // '/'
int p2[] = {2,3,0,1}; // '\'

tuple<int,int,int> dfs(int i, int j, int k) {
	if (!IN(i,0,n-1) || !IN(j,0,m-1)) return make_tuple(i,j,3);
	if (board[i][j] == '/')		k = p1[k];
	if (board[i][j] == '\\')	k = p2[k];
	if (board[i][j] == 'V' || board[i][j] == 'H')
		return make_tuple(i, j, k>=2);
	if (board[i][j] == '#') return make_tuple(i,j,2);
	return dfs(i+di[k],j+dj[k],k);
}

bool bound[N][N][2];
vector<tuple<int,int,int>> adj[N][N][2];
bool vis[N][N][2];

long long dfs2(int i, int j, int z) {
	long long ans = z^(board[i][j] == 'H');
	if (bound[i][j][z]) ans += oo;
	vis[i][j][z] = 1;
	for (auto pp : adj[i][j][z]) {
		int ii = get<0>(pp), jj = get<1>(pp), zz = get<2>(pp);
		if (!vis[ii][jj][zz])
			ans += dfs2(ii,jj,zz);
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>m;
	f(i,0,n) f(j,0,m) cin>>board[i][j];
	f(i,0,n) f(j,0,m) if (board[i][j] == 'H' || board[i][j] == 'V') {
		f(s,0,2) f(k,s<<1,(s+1)<<1) {
			auto pp = dfs(i+di[k],j+dj[k],k);
			int ii = get<0>(pp), jj = get<1>(pp), z = get<2>(pp);
			if (z == 3) continue;
			if (z == 2) bound[i][j][s] = 1;
			else {
				adj[i][j][s].push_back(make_tuple(ii,jj,z));
				adj[i][j][s^1].push_back(make_tuple(ii,jj,z^1));
			}
		}
	}

	long long ans = 0;
	f(i,0,n) f(j,0,m) if ((board[i][j] == 'V' || board[i][j] == 'H') && !vis[i][j][0]) {
		long long a = dfs2(i,j,0);
		if (vis[i][j][1]) {
			cout << -1 << endl;
			return 0;
		}
		long long b = dfs2(i,j,1);
		ans += min(a, b);
	}
	cout << (ans>=oo?-1:ans) << endl;

	return 0;
}
