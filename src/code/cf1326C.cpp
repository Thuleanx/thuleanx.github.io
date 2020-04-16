#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i>=a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple

const int N = 2e5+7, mod = 998244353;
int n,k;
int p[N];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>k;
	f(i,0,n) cin>>p[i];

	long long ans = 0;
	f(i,n-k+1,n+1) ans += i;

	long long cnt = 1;
	f(i,0,n) if (p[i] > n-k) {
		int j = i+1;
		while (j < n && p[j] <= n-k) j++;
		if (j != n) cnt = cnt*(j-i)%mod;
	}
	cout << ans << " " << cnt << endl;


	return 0;
}
