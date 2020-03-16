
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)

const int N = 2e5+7, oo = 1e9;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n; cin>>n;

	long long a[n];
	f(i,0,n) cin>>a[i];
	sort(a,a+n,greater<long long>());

	int ans = 0;
	f(i,0,n) ans += a[i]&1; // tentative answer

	if (a[0] == 1) {
		cout << ans << endl;
		return 0;
	}

	bool sieve[2*ans+1];
	f(i,0,2*ans+1) sieve[i] = 1;
	f(p,3,2*ans+1) if (sieve[p]) {
		int res = 0;
		f(i,0,n) {
			int x = a[i]%p;
			if (a[i] > p) res += min(x,p-x);
			else res += p-x;
			if (res > ans) break;
		}
		ans = min(ans, res);
		for (int j = 2*p; j <= 2*ans; j += p)
			sieve[j] = 0;
	}
	cout << ans << endl;

	return 0;
}
