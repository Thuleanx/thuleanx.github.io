#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define IN(i,a,b) (a <= i && i <= b)
#define mp make_pair

const int N = 3000;
int n, m;
char board[N][N];
bool a[N][N],b[N][N];
int dp[N][N];

int di[] = {1,0};
int dj[] = {0,1};

bool valid(int i, int j) {
	return IN(i,0,n-1) && IN(j,0,m-1) && board[i][j] == '.';
}

void init() {
	b[0][0] = valid(0,0);
	f(i,0,n) f(j,0,m) {
		f(k,0,2) {
			int ni = i-di[k], nj = j-dj[k];
			b[i][j] |= valid(ni,nj) && b[ni][nj];
		}
		b[i][j] &= valid(i,j);
	}
	a[n-1][m-1] = valid(n-1,m-1);
	fr(i,0,n) fr(j,0,m) {
		f(k,0,2) {
			int ni = i+di[k], nj = j+dj[k];
			a[i][j] |= valid(ni,nj) && a[ni][nj];
		}
		a[i][j] &= valid(i,j);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>m;

	int cnt = 0;
	f(i,0,n) f(j,0,m) {
		cin>>board[i][j];
		cnt += valid(i,j);
	}
	init();

	if (cnt < 2) {
		cout << 0 << endl;
		return 0;
	}

	int tr[] = {0,1};		
	f(z,1,3) {
		int i = 0, j = 0;
		while (i != n-1 || j != m-1) {
			dp[i][j] |= z;
			bool found = 0;
			for (int k : tr) {
				int ni = i+di[k], nj = j+dj[k];
				if (valid(ni, nj) && a[ni][nj]) {
					found = 1;
					i = ni; j = nj;
					break;
				}
			}

			if (!found) {
				cout << 1LL*cnt*(cnt-1)/2 << endl;
				return 0;
			}
		}
		dp[i][j] |= z;
		swap(tr[0],tr[1]);
	}

	long long ans = 0;

	int one = 0;
	f(i,0,n) f(j,0,m) if (dp[i][j] == 3) {
		one++;
		ans += cnt-one;
	}
	/* cout << ans << endl; */

	f(ii,0,n) f(jj,0,m) if (dp[ii][jj] == 1) {
		int iii = ii, jjj = jj;
		do {
			iii--; jjj++;
		} while (!a[iii][jjj] || !b[iii][jjj]);
		/* cout << ii << " " << jj << " " << iii << " " << jjj << endl;; */

		int i = iii, j = jjj;
		while (i != n-1 || j != m-1) {
			/* cout << "\t" << i << " " << j << " " << dp[i][j] << endl; */
			if (dp[i][j] == 2) ans++;
			for (int k : tr) {
				int ni = i+di[k], nj = j+dj[k];
				if (valid(ni, nj) && a[ni][nj]) {
					i = ni; j = nj;
					break;
				}
			}
		}
		swap(tr[0],tr[1]);
		i = iii, j = jjj;
		while (i || j) {
			/* cout << "\t" << i << " " << j << " " << dp[i][j] << endl; */
			if (dp[i][j] == 2) ans++;
			for (int k : tr) {
				int ni = i-di[k], nj = j-dj[k];
				if (valid(ni, nj) && b[ni][nj]) {
					i = ni; j = nj;
					break;
				}
			}
		}
		swap(tr[0],tr[1]);
		ans -= dp[iii][jjj] == 2;
	}


	cout << ans << endl;

	return 0;
}
