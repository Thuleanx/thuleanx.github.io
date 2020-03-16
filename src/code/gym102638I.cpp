#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i =a; i < b; i++)
#define count __builtin_popcountll

const int mod = 998244353;
const int N = 100;
int n, k;
long long a[N];

long long modpow(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b&1) res = res*a%mod;
		a = a*a%mod;
		b /= 2;
	}
	return res;
}

void add(long long &a, long long b) {
	a += b;
	if (a >= mod) a-= mod;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>k;
	f(i,0,n) cin>>a[i];
	
	long long last = 0;

	long long ans = 0;
	f(i,0,n) {
		long long cur = last | a[i];
		int cnt = k-count(last);
		int cnt2 = k-count(cur);
		add(ans, (i+1)*(( mod + modpow(2,cnt) - modpow(2,cnt2) ) % mod) % mod);
		last = cur;
	}
	cout << ans << endl;

	return 0;
}
