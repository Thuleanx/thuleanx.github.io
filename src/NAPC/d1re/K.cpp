
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple
#define sz(a) a.size()

using ld = long double;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi  = vector<int>;

const int oo = 1e9+7;
const ll ool = 1e18;

ll modpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b&1) res = res*a%oo;
		a = a*a%oo;
		b /=2;
	}
	return res;
}

const int N = 2000;
int n, m, t;
vi adj[N];
int a[N], b[N];

bool vis[N], bloc[N];
int tin[N], fup[N];
vi bridges;

void dfs(int v, int p = -1) {
	vis[v] = 1;
	tin[v] = fup[v] = t++;

	for (int e : adj[v]) if (!bloc[e]) {
		int w = a[e]^b[e]^v;
		if (!vis[w]) {
			dfs(w, v);
			fup[v] = min(fup[v], fup[w]);
			if (fup[w] > tin[v]) bridges.push_back(e);
		} else if (w != p) fup[v] = min(fup[v], tin[w]);
	}
}

int gcd(int a, int b) { return a?gcd(b%a, a):b; }

void run() {
	bridges.clear();
	f(i,0,N) vis[i] = 0, tin[i] = -1, fup[i] = -1;
	f(i,0,n) if (!vis[i]) dfs(i);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>m;
	f(i,0,m) {
		cin>>a[i]>>b[i];
		adj[--a[i]].push_back(i);
		adj[--b[i]].push_back(i);
	}

	run();
	for (int e : bridges) {
		adj[a[e]].erase(find(begin(adj[a[e]]), end(adj[a[e]]), e));
		adj[b[e]].erase(find(begin(adj[b[e]]), end(adj[b[e]]), e));
		bloc[e] = 1;
	}
	
	int g = 0;
	f(e,0,m) if (!bloc[e]) {
		bloc[e] = 1;
		run();
		g = gcd(g, bridges.size()+1);
		bloc[e] = 0;
	}
	f(i,1,m+1) if (g%i == 0)
		cout << i << " ";
	cout << endl;

	return 0;
}
