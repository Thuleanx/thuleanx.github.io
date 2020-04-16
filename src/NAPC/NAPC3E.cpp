
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple
#define sz(a) a.size()

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

const int N = 3e5;
int n, m, q, ans1, ans2;
int dsu[N], sz[N], cnt[N];
vector<int> adj[N];
int a[N],b[N],c[N],d[N],p[N];
pii res[N];

void init() { f(i,0,N) dsu[i] = i, sz[i] = 1, cnt[i] = 0; }
int root(int v) { return dsu[v] = dsu[v] == v ? v : root(dsu[v]); }
void merge(int i, int j) {
	i = root(i); j = root(j);
	if (i == j) return;
	if (sz[i] < sz[j]) swap(i,j);
	dsu[j] = i; sz[i] += sz[j]; cnt[i] += cnt[j]; 
}



int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>m;
	f(i,0,m) {
		cin>>a[i]>>b[i]>>c[i];
		adj[--a[i]].push_back(i);
		adj[--b[i]].push_back(i);
	}
	cin>>q;
	f(i,0,q) cin>>p[i];
	priority_queue< tuple<int,int,int> > pq;
	f(i,0,q) pq.push( mt(p[i], 0, i) );
	f(i,0,m) pq.push( mt(c[i], 1, i) );

	init();

	while (pq.size()) {
		auto pp = pq.top(); pq.pop();
		int i = get<2>(pp), z = get<1>(pp);
		if (!z) res[i] = mp(ans1,ans2);
		else {
			int x = a[i], y = b[i];			

			for (int zz : {x,y}) {
				if (d[zz] == 0) ans1++, ans2++;
				else if (d[zz] == 1) {
					ans1--; ans2 -= d[zz];
					int r = root(zz);
					if (++cnt[r] == sz[r]) ans1++, ans2+=2;
				} else if (d[zz] == 2) {
					ans1++; ans2+=3;
					int r = root(zz);
					if (cnt[r]-- == sz[r]) ans1--, ans2-=2;
				} else ans2++;
				d[zz]++;
			}
			
			if (root(x) != root(y)) {
				int r1 = root(x), r2 = root(y);
				if (cnt[r1] == sz[r1]) ans1--, ans2 -= 2;
				if (cnt[r2] == sz[r2]) ans1--, ans2 -= 2;
				merge(r1, r2);
				r1 = root(r1);
				if (cnt[r1] == sz[r1]) ans1++, ans2 += 2;
			}
		}
	}

	stringstream ss;
	f(i,0,q) ss << res[i].first << " " << res[i].second/2 << endl;
	cout << ss.str();

	return 0;
}
