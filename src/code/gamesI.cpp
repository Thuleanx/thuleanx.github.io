
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
const ll loo = 1e18;

ll modpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b&1) res = res*a%oo;
		a = a*a%oo;
		b /=2;
	}
	return res;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// use uniform_int_distribution<int>(0, i)(rng)

const int N = 1e5;
int n;
int a[N], val[N];
vector<int> adj[N];
map<int,string> id;
bool vis[N];

void build(int i, int l, int r) {
	id[i] = "";
	if (i == 1) { // split 2
		int mid = (l+r)>>1;
		build(i<<1, l, mid);
		build(i<<1|1, mid, r);
		adj[i].push_back(i<<1);
		adj[i].push_back(i<<1|1);
	} else if (r-l == 1)
		val[i] = a[l];
	else {
		int m1 = l + (r-l)/3, m2 = l + 2*(r-l)/3;
		build(i*3 , l, m1);
		build(i*3+1, m1, m2);
		build(i*3+2, m2, r);
		adj[i].push_back(3*i);
		adj[i].push_back(3*i+1);
		adj[i].push_back(3*i+2);
	}
}

int alphabeta(int i, int a, int b, int m) {
	vis[i] = 1;
	if (val[i] != -1) {
		cout << id[i] << " " << (a==-oo?"-oo":to_string(a)) << " " << (b==oo?"oo":to_string(b)) << endl;
		return val[i];
	}
	if (m) {
		int value = -oo;
		for (int j : adj[i]) {
			value = max(value, alphabeta(j, a, b, 0));
			a = max(a, value);
			if (a >= b) break; // cut
		}
		cout << id[i] << " " << (a==-oo?"-oo":to_string(a)) << " " << (b==oo?"oo":to_string(b)) << endl;
		return value;
	} else {
		int value = oo;
		for (int j : adj[i]) {
			value = min(value, alphabeta(j, a, b, 1));
			b = min(b, value);
			if (a >= b) break;
		}
		cout << id[i] << " " << (a==-oo?"-oo":to_string(a)) << " " << (b==oo?"oo":to_string(b)) << endl;
		return value;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n;
	f(i,0,n) cin>>a[i];
	f(i,0,N) val[i] = -1;
	build(1, 0, n);
	for (auto pp : id) 
		cin >> id[pp.first];
	cout << alphabeta(1, -oo, oo, 1) << endl;

	return 0;
}
