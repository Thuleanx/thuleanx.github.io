
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i>=a; i--)
#define IN(i,a,b) (a<=(i) && (i)<=b)
#define mp make_pair
#define mt make_tuple

const int N = 4000, oo = 1e9;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n; cin>>n;
	int a[n];
	f(i,0,n) cin>>a[i];
	vector<int> res[n][N]; 
	f(i,0,n) res[i][--a[i]].push_back(i+1);

	fr(i,0,n) f(j,0,N) {
		for (int k : res[i][j]) {
			if (k < n) for (int z : res[k][j]) res[i][j+1].push_back(z);	
		}
	}

	int dp[n+1];
	f(i,0,n+1) dp[i] = oo;
	dp[0] = 0;
	f(i,0,n) f(j,0,N) for (int k : res[i][j]) dp[k] = min(dp[k], dp[i]+1);

	cout << dp[n] << endl;

	return 0;
}
