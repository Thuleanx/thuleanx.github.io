#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)

const int N = 300000;
const long long mod = 998244353;
int n, m;
unordered_map<int,int> gaussian[N];
int a[N], b[N];
bool elim[N];

int inv[5] = {0, 1, 3, 2, 4};
int mul[5][5];

long long modpow(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b&1) res = res*a % mod;
		a = a*a%mod;
		b /= 2;
	}
	return res;
}

void add(int &a, int b) {
	a += b;
	if (a >= 5) a-=5;
}

void gauss_elim(int i, int j, int m) {
	if (m == 5 || !m) return;
	// assume m != 0 and pp.second != 0
	for (auto pp : gaussian[i]) {
		int e = pp.first, amt = mul[pp.second][m];
		add(gaussian[j][e], amt);	
		if (!gaussian[j][e]) gaussian[j].erase(e);
		else if (gaussian[j][e] == amt) {
			if (a[e] == i) a[e] = j;
			if (b[e] == i) b[e] = j;
		}
	}
}

void display_gauss(stringstream &ss) {
	f(i,0,n) {
		f(j,0,m) {
			if (gaussian[i].count(j))
				ss << gaussian[i][j] << " ";
			else ss << 0 << " ";
		}
		ss << endl;
	}
	ss << endl;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	f(i,0,5) f(j,0,5) mul[i][j] = i*j%5;

	int t; cin>>t;
	stringstream ss;
	while (t--) {
		cin>>n>>m;
		// __init__
		f(i,0,n) {
			gaussian[i].clear();
			elim[i] = 0;
		}
		f(i,0,m) {
			cin>>a[i]>>b[i];		
			gaussian[--a[i]][i]++;
			gaussian[--b[i]][i]++;
		}
		int basis = 0;
		// no more than n basis 
		f(k,0,m) {
			int c = -1;
			for (int x : { a[k], b[k] }) if (!elim[x] && gaussian[x].count(k)) {
				if (c == -1 || gaussian[x].size() < gaussian[c].size())
					swap(x,c);
			}
			if (c == -1) continue;
			elim[c] = 1;
			basis++;

			int o = a[k] ^ b[k] ^ c;
			if (!elim[o] && gaussian[o].count(k)) 
				gauss_elim(c, o, 5-mul[inv[gaussian[c][k]]][gaussian[o][k]]);		
		}
		
		ss << modpow(5, m-basis) << endl;
	}
	cout << ss.str();

	return 0;
}
