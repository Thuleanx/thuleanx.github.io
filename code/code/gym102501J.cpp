#include <bits/stdc++.h>
using namespace std;

const int N = 2e6+7, mod = 1e9+7;
int n;
long long f[N], g[N];
int a[N], fr[N];

long long modpow(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b&1) res = res*a%mod;
		a = a*a%mod;
		b /= 2;
	}
	return res;
}

void init() {
	for (int i = 0; i < N; i++)
		f[i] = i?f[i-1]*i%mod:1;
	g[N-1] = modpow(f[N-1], mod-2);
	for (int i = N-2; i >= 0; i--)
		g[i] = g[i+1]*(i+1)%mod;
}

long long cat(int n) {
	return f[2*n]*g[n]%mod*g[n]%mod*modpow(n+1,mod-2)%mod;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n;
	for (int i = 0; i < n; i++)
		cin>>a[i];
	init();
	vector<int> st;

	long long ans = 1;
	for (int i = 0; i < n; i++) {
		while (st.size() && st.back() > a[i]) {
			int v = st.back(); st.pop_back();
			ans = ans*cat(fr[v])%mod;
			fr[v] = 0;
		}
		if (!st.size() || st.back() != a[i])
			st.push_back(a[i]);
		fr[a[i]]++;
	}
	while (st.size()) {
		int v = st.back(); st.pop_back();
		ans = ans*cat(fr[v])%mod;
		fr[v] = 0;
	}
	cout << ans << endl;

	return 0;
}
