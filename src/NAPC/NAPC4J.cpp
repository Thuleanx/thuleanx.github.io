
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

const int N = 1e6+1;
int n, cnt;
map<vi, int> vmap;
map<int,int> beauty;
vi adj[N];
int x[N],y[N],z[N]; // n points
bool active[N];
int col[N];

int gen(vi id) {
	if (vmap.count(id)) return vmap[id];
	active[cnt] = (id[0]==-1) + (id[1] == -1) + (id[2] == -1) == 2;
	vmap[id] = cnt;
	return cnt++;
}

void con(int i, int j) {
	cout << i << " " << j << endl;
	adj[i].push_back(j);
	adj[j].push_back(i);
}

void dfs(int i, int p) {
	col[i] = p;
	for (int w : adj[i]) if (col[w] == -1 && active[w])
		dfs(w,p);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	stringstream ss;
	while (t--) {
		cin>>n; cnt = 0;

		f(i,0,n) cin>>x[i]>>y[i]>>z[i];
		vmap.clear(); beauty.clear();

		f(i,0,n) {
			vi ssn = {x[i], y[i], z[i]}; 

			f(k,0,3) if (ssn[k] != -1) {

			}
		}

		f(i,0,n) {
			vi ssn = {x[i], y[i], z[i]}; 
			int cur = gen(ssn);
			int neg = 0;
			while (ssn[neg] != -1) neg++;
			f(k,0,3) if (ssn[k] != -1) {
				f(dx,-1,2) if (dx) {
					ssn[k] += dx;
					if (vmap.count(ssn)) 
						con(cur, gen(ssn));
					ssn[k] -= dx;	

					vi id = {-1,-1,-1};
					id[k] = ssn[k] + dx;

					if (vmap.count(id)) {
						int nxt = gen(id);
						if (beauty[nxt] & (7 ^ (1<<neg)))
							con(cur, nxt);
					}
				}

				vi id = {-1,-1,-1};
				id[k] = ssn[k];

				int nxt = gen(id);
				beauty[nxt] |= 1<<neg;
				con(cur, nxt);
			}
			beauty[cur] = neg;
		}

		for (auto pp : vmap) {
			cout << "A: " << pp.second << " -> ";
			f(i,0,3) cout << pp.first[i] << " \n"[i==2];
			int cnt = 0;
			f(i,0,3) if (pp.first[i] == -1) cnt++;
			if (cnt == 2) {
				int id = pp.second;

				bool neg[3] = {0,0,0};
				for (int w : adj[id]) neg[beauty[w]] = 1;			

				if (neg[0] + neg[1] + neg[2] == 2) {
					cout << "ACTIVE" << endl;
					active[id] = 1;
				}
			} else active[pp.second] = 1;
		}

		f(i,0,cnt) adj[i].clear();
		f(i,0,cnt) col[i] = -1;

		int p = 0;	

		f(i,0,cnt) if (col[i] == -1)
			dfs(i, p++);

		int q; cin>>q;
		while (q--) {
			int xx[2],yy[2],zz[2];
			int i[2] = {-1,-1};
			f(zzz,0,2) cin>>xx[zzz]>>yy[zzz]>>zz[zzz];
			f(zzz,0,2) {
				f(k,0,3) {
					vi id = {xx[zzz],yy[zzz],zz[zzz]}; 
					id[k] = -1;
					if (vmap.count(id)) {
						i[zzz] = gen(id);
						break;
					}
				}
			}

			if (i[0] == -1 || i[1] == -1) ss << "NO" << endl;
			else ss << (col[i[0]] == col[i[1]] ? "YES":"NO") << endl;
		}
	}
	cout << ss.str();

	return 0;
}
