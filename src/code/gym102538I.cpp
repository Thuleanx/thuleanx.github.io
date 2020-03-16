
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define popcount __builtin_popcountll

const int N = 100, M = 60, mod = 998244353;
int n,k;
long long a[N];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>k;
	f(i,0,n) cin>>a[i];
	long long mask = 0, ans = 0;
	f(i,0,n) {
		long long nmask = mask | a[i];
		ans += (i+1) * (((1LL << k - popcount( mask )) - 
				(1LL << k - popcount(nmask))) % mod) % mod;
		ans %= mod;
		mask = nmask;
	}
	cout << ans << endl;

	return 0;
}
