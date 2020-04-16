#include <bits/stdc++.h>
using namespace std;

#define M_PI           3.14159265358979323846

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
using C = complex<long double>;
using vd = vector<long double>;

void fft(vector<C> &a) {
	int n = a.size(), L = 31- __builtin_clz(n);
	static vector<complex<long double>> R(2,1);
	static vector<complex<long double>> rt(2,1);
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, (long double) M_PI / k);
		f(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2]*x : R[i/2];
	}
	vector<int> rev(n);
	f(i,0,n) rev[i] = (rev[i/2] | (i&1)<<L)/2;
	f(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k*=2) {
		for (int i = 0; i < n; i += 2*k) f(j,0,k) {
			C z = rt[j+k] * a[i+j+k];
			a[i + j + k] = a[i+j] - z;
			a[i+j] += z;
		}
	}
}
vd conv(const vd& a, const vd& b) {
	if (a.empty() || b.empty()) return {};
	vd res(a.size() + b.size() -1);
	int L = 32 - __builtin_clz(res.size()), n = 1<<L;
	vector<C> in(n), out(n);
	f(i,0,a.size()) in[i] = a[i];
	f(i,0,size(b)) in[i].imag(b[i]);
	fft(in);
	for (C &x : in) x *= x;
	f(i,0,n) out[i] = in[-i&(n-1)] - conj(in[i]);
	fft(out);
	f(i,0,res.size()) res[i] = imag(out[i]) / (4*n);
	return res;
}

const int N = 5e5+7;
int sieve[N];
vd a(N);
long long b[N];

int calc(int v) {
	int num = 1;
	while (v>1) {
		int p = sieve[v];
		int cnt = 0;
		while (sieve[v] == p) {
			cnt++;
			v /= p;
		}
		num *= (cnt+1);
	}
	return num;
}

struct Tree {
	static constexpr long long unit = INT_MIN;
	int cob(int i, int j) { return b[i]>b[j]?i:j; }
	vector<int> s; int n;
	Tree(int n = 0, int def =unit) : s(2*n, def), n(n) {}
	void build() {
		f(i,0,n) s[i+n] = i;
		fr(i,1,n) s[i] = cob(s[i<<1], s[i<<1|1]);
	}
	int query(int b, int e) {
		int res = b;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b%2) res = cob(res, s[b++]);
			if (e%2) res = cob(s[--e], res);
		}
		return res;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	f(i,2,N) if (!sieve[i]) {
		sieve[i] = i;
		for (int j = i+i; j < N; j += i)
			sieve[j] = i;
	}
	f(i,1,N) a[i] = calc(i);

	vd res = conv(a,a);
	f(i,0,N) b[i] = round(res[i]);
	
	Tree ds(N);
	ds.build();

	int q; cin>>q;
	stringstream ss;
	while (q--) {
		int lo, hi; cin>>lo>>hi;
		int x = ds.query(lo, hi+1);
		ss << x << " " << b[x] << endl;
	}
	cout << ss.str();


	return 0;
}
