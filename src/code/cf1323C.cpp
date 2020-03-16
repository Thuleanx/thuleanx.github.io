#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)

const int N = 5e5, sN = 800, mod = 1e9+7, NN = 1e7+1;
int n,m, p = 0;
long long a[N];
map<int,int> cnt[N];
vector<int> adj[N], rev[N];
int primes[N];

long long gcd(long long a, long long b) {
	return a?gcd(b%a,a):b;
}

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

	bool sieve[NN];
	f(i,0,NN) sieve[i] = 1;
	f(i,2,NN) if (sieve[i]) {
		primes[p++] = i;
		if (p == N) break;
		for (int j = i+i; j < NN; j += i)
			sieve[j] = 0;
	}
	
	int t; cin>>t;
	while (t--) {
		cin>>n>>m;
		f(i,0,n) cin>>a[i];
		long long g = 0;
		f(i,0,n) {
			adj[i].clear();
			rev[i].clear();
		}
		f(i,0,m) {
			int v,w; cin>>v>>w; v--; w--;
			adj[v].push_back(w);	
			rev[w].push_back(v);
		}

		unordered_map<int,int> ash;

		f(i,0,n) {
			long long s = 0;
			for (int w : adj[i])
				s += a[w];
			g = gcd(s, g);
		}

		f(i,0,n) {
			long long val = 0;
			int cnt = 0;
			for (int w : rev[i])
				val = (val + modpow(primes[cnt++], w)) % mod;
			ash[val] += a[i];
		}

		bool con[n];
		f(i,0,n) con[i] = 0;
		f(i,0,n) for (int w : adj[i])
			con[w] = 1;
		long long s = 0;
		f(i,0,n) if (con[i]) s += a[i];
		g = gcd(s, g);

		for (auto pp : ash)
			g = gcd(g, pp.second);

		cout << g << endl;
	}
	
	return 0;
}
