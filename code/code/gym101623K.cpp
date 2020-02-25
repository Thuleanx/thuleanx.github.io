#include <bits/stdc++.h>
using namespace std;

const int N = 4096;
int n;
unordered_map<int, long double> dp[2*N];
int a[N];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n;
	for (int i = 0; i < n; i++)
		cin>>a[i];
	sort(a+1,a+n); reverse(a,a+n);

	for (int i = N, j = 0; j < n; i++) {
		if (__builtin_popcount(i - N + n - j) != 1) {
			dp[i][j] = 1.0*a[j]/(a[j]+a[j|1]);
			dp[i][j|1] = 1-dp[i][j];
			j += 2;
		} else
			dp[i][j++] = 1;
	}

	for (int i = N-1; i > 0; i--) {
		int j = i<<1, k = i<<1|1;
		if (!dp[j].size()) dp[i] = dp[k];
		else if (!dp[k].size()) dp[i] = dp[j];
		else {
			for (int z = 0; z < 2; z++, swap(j,k)) {
				if (!dp[k].count(n-1))
				for (auto p1 : dp[j]) {
					int v = p1.first;
					dp[i][v] = 0;
					for (auto p2 : dp[k])
						dp[i][v] += p2.second * a[v] / (a[v] + a[p2.first]);
					dp[i][v] *= p1.second;
				}
			}
		}
	}

	cout << setprecision(40) << dp[1][n-1] << endl;


	return 0;
}
