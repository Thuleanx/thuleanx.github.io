#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i>=a; i--)

const long long oo = 1e18;
const int N = 51;
int n;
long long dp[N][N][N][2][2][2];
int a[N], b[N];

#define re(a,b) a = max(a,b)

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	freopen("bowling.in", "r", stdin);

	cin>>n;
	f(i,0,n) {
		cin>>a[i]>>b[i];
		b[i] += a[i];
	}
	int x, y; cin>>x>>y;
	a[n] = x; b[n] = x+y;

	long long res = 0;

	fr(tt,0,n+1) {
		swap(a[tt], a[n]);
		swap(b[tt], b[n]);

		int A = 0, B = 0;
		long long ans = 0;
		f(i,0,n) {
			ans += b[i];
			if (a[i] == 10) A++;
			else if (b[i] == 10) B++;
		}

		/* f(i,0,n+1) cout << a[i] << " \n"[i==n]; */
		/* f(i,0,n+1) cout << b[i]-a[i] << " \n"[i==n]; */
		/* cout << ans << endl; */

		f(i,0,N) f(j,0,N) f(k,0,N) f(z,0,2) f(zz,0,2) f(zzz,0,2) 
			dp[i][j][k][z][zz][zzz] = -oo;

		dp[0][0][0][!A][!B][!(A+B)] = 0;

		f(i,0,n) f(aa,0,n) f(bb,0,n) 
		f(z,0,2) f(zz,0,2) f(zzz,0,2) if (dp[i][aa][bb][z][zz][zzz] != -oo && aa<=A && bb<=B) {
			if (aa < A) {
				re(dp[i+1][aa+1][bb][z|(a[i]<10)][zz][zzz|(b[i]<10)], 
						dp[i][aa][bb][z][zz][zzz] + b[i]);
			}
			if (bb < B) {
				re(dp[i+1][aa][bb+1][z][zz|(a[i]==10 || b[i]<10)][zzz|(b[i]<10)],
						dp[i][aa][bb][z][zz][zzz] + a[i]);
			}
			re(dp[i+1][aa][bb][z][zz][zzz], dp[i][aa][bb][z][zz][zzz]);
		}

		for (int AA : {A, A-1})
		for (int BB : {B, B-1}) 
		f(z,0,2) f(zz,0,2) f(zzz,0,2) if (A-AA + B-BB < 2 && AA>=0 && BB>=0) {
			if (AA == A && BB == B) {
				if (z & zz & zzz) re(res, ans + dp[n][AA][BB][z][zz][zzz]);	
			} else if (AA == A-1) {
				if (zz) re(res, ans + dp[n][AA][BB][z][zz][zzz] + 2*b[n]);
			} else if (BB == B-1) {
				if (z) re(res, ans + dp[n][AA][BB][z][zz][zzz]);
			}
		}
	}

	cout << res << endl;


	return 0;
}
