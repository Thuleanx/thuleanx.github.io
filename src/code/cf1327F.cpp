
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i>=a; i--)
#define IN(i,a,b) (a<=(i) && (i)<=b)
#define mp make_pair
#define mt make_tuple

const int N = 5e5+7, mod = 998244353;
int n,m,k;
int l[N], r[N];
long long x[N];
int up[N], down[N], cnt[N];

void add(long long &a, long long b) {
	a += b;
	if (a >= mod) a-=mod;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	long long res = 1;
	cin>>n>>k>>m;
	f(i,0,m) {
		cin>>l[i]>>r[i]>>x[i]; 
		l[i]--;
	}

	f(z,0,k) {
		f(i,0,n) cnt[i] = up[i] = down[i] = 0;
		f(i,0,m) if (x[i]>>z&1) {
			cnt[l[i]]++; cnt[r[i]]--;	
		} else {
			up[l[i]]++; down[r[i]]++;
		}

		long long dp[n+1][2];
		f(i,0,n+1) f(j,0,2) dp[i][j] = 0;

		dp[0][up[0]] = 1;

		int running = 0;
		f(i,0,n) {
			running += cnt[i];
			f(j,0,2) if (dp[i][j]) {
				// zero move - do whenever not forced
				if (!running) add(dp[i+1][up[i+1]], dp[i][j]);
				// one move - can only do if, not 
				// end next and j still positive
				
			}
		}

		long long sum = (dp[n][0]+dp[n][1])%mod;
		res = res*sum%mod;
	}

	return 0;
}
