#include <bits/stdc++.h>
using namespace std;

const int N = 2e5;
int n;
int a[N];

#define f(i,a,b) for (int i = a; i < b; i++)

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n;
	f(i,0,n) cin>>a[i];
	unordered_map<int,long long> dp;

	long long ans = 0;
	f(i,0,n) {
		dp[a[i]-i] += a[i];
		ans = max(ans, dp[a[i]-i]);	
	}
	cout << ans << endl;
	
	return 0;
}
