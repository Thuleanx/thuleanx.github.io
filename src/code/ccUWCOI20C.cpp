#include <bits/stdc++.h>
using namespace std;

const int N = 1e6, NN = 1e3;

int dsu[N], sz[N];
bool active[NN][NN];

int a[NN][NN];
int di[] = {1,-1,0,0};
int dj[] = {0,0,1,-1};

#define f(i,a,b) for (int i = a; i <b ; i++)
#define IN(i,a,b) (a<=i&&i<=b)

int n, m, q;

void init() {
	f(i,0,N) dsu[i] = i, sz[i] = 1;
	f(i,0,n) f(j,0,m) active[i][j] = 0;
}
int root(int v) {
	return dsu[v] = dsu[v] == v ? v : root(dsu[v]);
}
void merge(int a, int b) {
	a = root(a); b = root(b);
	if (a == b) return;
	if (sz[a] < sz[b]) swap(a,b);
	dsu[b] = a; sz[a] += sz[b];
}
void ac(int v) {
	int i = v/m, j = v%m;
	active[i][j] = 1;
	f(k,0,4) {
		int ni = i+di[k], nj = j+dj[k];
		if (IN(ni,0,n-1) && IN(nj,0,m-1) && active[ni][nj])
			merge(v, ni*m + nj);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);


	stringstream ss;
	int t; cin>>t;
	while (t--) {
		cin>>n>>m>>q;
		init();
		f(i,0,n) f(j,0,m) cin>>a[i][j];
		vector<tuple<int,int,int>> cells;
		f(i,0,n) f(j,0,m) cells.push_back(make_tuple(a[i][j], i, j));
		sort(begin(cells),end(cells));
		vector<tuple<int,int,int,int>> que;
		f(z,0,q) {
			int i,j,p; cin>>i>>j>>p; i--; j--;
			que.push_back(make_tuple(p,i,j,z));		
		}
		sort(begin(que),end(que));
		int zz = 0;
		vector<int> ans(q);
		f(z,0,q) {
			int i,j,p; i = get<1>(que[z]); j = get<2>(que[z]); p = get<0>(que[z]);
			while (zz < cells.size() && get<0>(cells[zz]) < p) {
				ac(get<1>(cells[zz])*m + get<2>(cells[zz]));
				zz++;
			}
			if (p > a[i][j]) 
				ans[get<3>(que[z])] = sz[root(i*m+j)];
			else ans[get<3>(que[z])] = 0;
		}
		f(z,0,q) ss << ans[z] << endl;
	}
	cout << ss.str();

	return 0;
}
