#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = b-1; i >= a; i--)

const int oo = 1e9;

int n,m;
string s, r;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>s>>r; n = s.length(); m = r.length();

	int ns[n+2][2], ms[m+2][2];
	f(i,n,n+2) f(j,0,2) ns[i][j] = n;
	f(i,m,m+2) f(j,0,2) ms[i][j] = m;

	fr(i,0,n) {
		f(k,0,2) ns[i][k] = ns[i+1][k];
		ns[i][s[i]-'0'] = i;
	}
	fr(i,0,m) {
		f(k,0,2) ms[i][k] = ms[i+1][k];
		ms[i][r[i]-'0'] = i;
	}

	int dp[n+2][m+2];
	f(i,0,n+2) f(j,0,m+2) dp[i][j] = oo;

	bool gd[n+2][m+2];
	f(i,0,n+2) f(j,0,m+2) gd[i][j] = i==n+1 && j==m+1;

	dp[0][0] = 0;
	f(i,0,n+2) f(j,0,m+2) if (dp[i][j] != oo) {
		f(k,0,2) {
			int ni = ns[i][k] + 1, nj = ms[j][k] + 1;
			if (dp[ni][nj] > dp[i][j] + 1)
				dp[ni][nj] = dp[i][j]+1;
		}
	}
	fr(i,0,n+2) fr(j,0,m+2) if (!gd[i][j] && dp[i][j] != oo) {
		f(k,0,2) {
			int ni = ns[i][k] + 1, nj = ms[j][k] + 1;
			if (dp[ni][nj] == dp[i][j] + 1)
				gd[i][j] |= gd[ni][nj];
		}
	}

	int i = 0, j = 0;
	string ss;
	while (i <= n || j <= m) {
		f(k,0,2) {
			int ni = ns[i][k] + 1, nj = ms[j][k] + 1;
			if (dp[ni][nj] == dp[i][j] + 1 && gd[ni][nj]) {
				ss += to_string(k);
				i = ni; j = nj;
				break;
			}
		}
	}
	assert(ss.length() == dp[n+1][m+1]);
	cout << ss << endl;


	
	return 0;
}
