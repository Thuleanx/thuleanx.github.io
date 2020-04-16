#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i>=a; i--)
#define IN(i,a,b) (a<=(i) && (i)<=b)
#define mp make_pair
#define mt make_tuple

const int N = 5e5, mod = 998244353;
int n,m;
long long fi[N], gi[N];

long long modpow(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b&1) res = res*a%mod;
		a = a*a%mod;
		b /= 2;
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>m;
	fi[0] = 1;
	f(i,1,N) fi[i] = fi[i-1]*i%mod;
	gi[N-1] = modpow(fi[N-1], mod-2);
	fr(i,0,N-1) gi[i] = gi[i+1]*(i+1)%mod;

	if (n-1 > m) cout << 0 << endl;
	else {
		// m choose n-1 multiply n-2
		cout << (n-2) * (fi[m] * gi[n-1] % mod * gi[m-(n-1)] % mod) % mod * modpow(2, n-3) % mod << endl;
	}

	return 0;
}
