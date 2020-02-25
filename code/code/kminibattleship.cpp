/*
 * Problem: Mini Battleship
 * Platform: Kattis
 * Contest: North American Championship 2020
 * Date: 24022020
 * Score: +0
 * Description: Simply brute force all ways and check
 * Tags: brute-force,optimization
 */
#include <bits/stdc++.h>
using namespace std;

const int N = 5;
int n, k;
char a[N][N];
int len[N];

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = b-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)

int di[] = {1,0};
int dj[] = {0,1};

int vis[N][N];
vector<tuple<int,int,int>> place;

long long bf(int z, int cnt) {
	if (z == k) {
		return !cnt;
	}
	
	long long ans = 0;
	f(i,0,n) f(j,0,n) {
		f(k,0,2-(len[z] == 1)) {
			if (IN(i+len[z]*di[k],0,n) && IN(j+len[z]*dj[k],0,n)) {
				bool god = 1;
				int add = 0;
				f(d,0,len[z]) { 
					int ni = i+d*di[k], nj = j+d*dj[k];
					god &= !vis[ni][nj] && (a[ni][nj] != 'X');
					add += a[ni][nj] == 'O';
					vis[ni][nj]++;
				}
				if (god) ans += bf(z+1,cnt-add);
				f(d,0,len[z]) { 
					int ni = i+d*di[k], nj = j+d*dj[k];
					vis[ni][nj]--;
				}
			}
		}

	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>k;
	f(i,0,n) f(j,0,n) cin>>a[i][j];
	f(i,0,k) cin>>len[i];
	int cnt = 0;
	f(i,0,n) f(j,0,n) cnt += a[i][j] == 'O';
	cout << bf(0,cnt) << endl;

	return 0;
}
