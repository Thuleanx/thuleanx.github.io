
/*
 * Problem: Another Coin Weighing Puzzle
 * Platform: Kattis
 * Contest: North American Championship 2020
 * Date: 24022020
 * Score: +
 * Description: We effectively are constructing a matrix $a_{ij}$ such that when you take a look at:
 *		$$ a_{i1}g, a_{i2}g, \ldots, a_{im}g $$. You can tell uniquely what $i$ is. But for us to know 
 *		this, we need to know what $g$ is, and the way that's possible is if $gcd(a_{i1},\ldots,a_{im})=1$.
 *
 *		Notice that the number of unique rows of this matrix we can construct gives us an upper bound on the answer,
 *		which also happens to be the answer since every element has an inverse that is not itself (except for 
 *		the all zero tuple).
 *
 *		You get a recurrence that involves the mobius function. That's it
 * Tags: numbertheory,mobius,fastexponentiation,dynamicprogramming
 */
#include <bits/stdc++.h>
using namespace std;

const int N = 2e6, oo = 998244353;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = b-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)

long long modpow(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b&1) res = res*a%oo;
		a = a*a%oo; b/=2;
	}
	return res;
}

int m,k;
int sieve[N];

int mu(int p) {
	int cnt = 0;
	while (p>1) {
		int pr = sieve[p];
		if (p % (pr*pr) == 0) return 0;
		p /= pr;	
		cnt++;
	}
	return cnt&1?-1:1;
}

void add(long long &a, long long b) {
	a += b;
	if ( a >= oo ) a -= oo;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>m>>k;
	
	f(i,0,N) sieve[i] = 0;

	f(i,2,N) if (!sieve[i])
		for (int j = i; j < N; j += i)
			sieve[j] = i;
	
	long long ans = modpow(2*k+1,m);
	f(d,2,k+1) {
		int s = mu(d);
		if (s) {
			long long adder = modpow(2*(k/d)+1, m);
			add(adder, oo-1);
			if (s==-1) adder = oo-adder;
			add(ans, adder);
		}
	}
	cout << ans << endl;

	return 0;
}
