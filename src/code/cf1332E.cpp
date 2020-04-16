#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple

const int mod = 998244353;
using ll = long long;

template<class T, int N> struct Matrix {
	typedef Matrix M;
	array<array<T,N>,N> d{};
	M operator*(const M& m) const {
		M a;
		f(i,0,N) f(j,0,N) f(k,0,N)
			a.d[i][k] = (a.d[i][k] + d[i][j]*m.d[j][k]%mod)%mod;
		return a;
	}
	M operator^(ll p) const {
		assert(p >= 0);
		M a, b(*this);
		f(i,0,N) a.d[i][i] = 1;
		while (p) {
			if (p&1) a = a*b;
			b = b*b;
			p >>= 1;
		}
		return a;
	}
	void print() {
		f(i,0,N) f(j,0,N) cout << d[i][j] << " \n"[j==N-1];
		cout << endl;
	}
};

ll modpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b&1) res = res*a%mod;
		a = a*a%mod;
		b /=2;
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, L, R;
	cin>>n>>m>>L>>R;

	if (n*m&1) cout << modpow(R-L+1, 1LL*n*m) << endl;
	else {
		long long a = (R-L+1)/2 + ((R-L+1)&1?L&1:0), b = (R-L+1)/2 + ((R-L+1)&1?!(L&1):0);

		Matrix<ll,2> x, y, z;
		x.d[0][0] = b%mod; x.d[0][1] = a%mod;
		x.d[1][0] = a%mod; x.d[1][1] = b%mod;

		x = x^(1LL*n*m);

		y.d[0][0] = 1;
		z = x*y;

		cout << z.d[0][0] << endl;
	}
}
