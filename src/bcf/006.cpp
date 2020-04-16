// 102501G https://codeforces.com/problemset/gymProblem/102501/G
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

const int N = 200, M = 1e5;
int n, m;
vi se, oc[N];
bitset<N> adj[N];
map<string, int> id;
string name[N];

int solve() {
	int z; cin>>n>>z>>m;
	f(i,0,n) cin>>name[i];
	sort(name,name+n);

	f(i,0,n) id[name[i]] = i;


	while (z--) {
		string s, r; cin>>s>>r;
		int i = id[s], j = id[r];
		adj[i][j] = adj[j][i] = 1;
	}

	f(i,0,m) {
		string s; cin>>s;
		se.push_back(id[s]);
		oc[id[s]].push_back(i);
	}
	f(i,0,n) reverse(begin(oc[i]), end(oc[i]));


	stringstream ss;

	set<pii> contain;
	f(i,0,n) if (oc[i].size()) contain.insert(pii(oc[i].back(), i));
	
	f(i,0,m) {
		bitset<N> en = bitset<N>(0);
		int best = n;
		for (auto pp : contain) {
			int d = pp.second;
			if (d < best && (en & adj[d]).count() == en.count())
				best = d;
			en[d] = 1;	
		}
		contain.erase(pii(oc[best].back(), best));
		oc[best].pop_back();
		ss << name[best] << " ";
		if (oc[best].size()) contain.insert(pii(oc[best].back(), best));
	}

	cout << ss.str() << endl;
	

	return 0;	
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	solve();

	return 0;
}
