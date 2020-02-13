#include <bits/stdc++.h>
using namespace std;

const int N = 2e5, sqrtN = 700, mod = 1e9+7;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m; cin>>n>>m;
	long long mx[sqrtN], cnt[sqrtN];
	int a[n];
	for (int i = 0; i < n; i++) a[i] = 0;
	for (int i = 0; i < sqrtN; i++)
		mx[i] = cnt[i] = 0;
	cnt[0] = 1;
	for (int i = 0; i < m; i++) {
		int x,y; cin>>x>>y;
		a[--x]++;
		a[--y]++;
	}
	for (int i = 0; i < n; i++) {
		for (int j = sqrtN-2; j >= 0; j--) if (cnt[j]) {
			if (mx[j+1] < mx[j]+a[i]) mx[j+1] = mx[j] + a[i], cnt[j+1] = 0;
			if (mx[j+1] == mx[j] + a[i]) cnt[j+1] = (cnt[j]+cnt[j+1])%mod;
		}
	}
	long long ans = 0;
	for (int j = 0; j < sqrtN; j++) {
		if (mx[j] == 1LL*j*(j-1)/2 + m)
			ans = (ans+cnt[j])%mod;
	}
	cout << ans << endl;


	return 0;
}
