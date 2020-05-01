
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

const int N = 6;
int di[] = {1, -1, 0, 0};
int dj[] = {0, 0, 1, -1};

char board[N][N];
map<int, int> cnt;
bool vis[N][N];

void neg(vector<int> &x) {
	f(i,0,x.size()) x[i] = -x[i];
}

vector<vector<int>> left(vector<vector<int>> coord) {
	swap(coord[0], coord[2]);
	neg(coord[0]);
	return coord;
}

vector<vector<int>> right(vector<vector<int>> coord) {
	swap(coord[0], coord[2]);
	neg(coord[2]);
	return coord;
}

vector<vector<int>> up(vector<vector<int>> coord) {
	swap(coord[1], coord[2]);
	neg(coord[2]);
	return coord;
}

vector<vector<int>> down(vector<vector<int>> coord) {
	swap(coord[1], coord[2]);
	neg(coord[1]);
	return coord;
}

void dfs(int i, int j, vector<vector<int>> coord) {
	vis[i][j] = 1;
	f(z,0,3) if (coord[2][z]) {
		cnt[(z+1)*coord[2][z]]++;		
	}
	f(k,0,4) {
		int ni = i+di[k], nj = j+dj[k];
		if (IN(ni,0,N-1) && IN(nj,0,N-1) && !vis[ni][nj] && board[ni][nj] == '#') {
			vector<vector<int>> nex;
			if (k == 0) nex = down(coord);
			if (k == 1) nex = up(coord);
			if (k == 2) nex = left(coord);
			if (k == 3) nex = right(coord);
			dfs(ni,nj,nex);
		}
	}
}

int solve() {
	f(i,0,N) f(j,0,N) cin>>board[i][j];
	vector<vector<int>> coord = {{1,0,0}, {0,1,0}, {0,0,1}};	
	f(i,0,N) {f(j,0,N) if (board[i][j] == '#') {
		dfs(i,j,coord);
		goto end;
	}
	}
end:{}
	return cnt.size() == 6;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cout << (solve() ? "can fold" : "cannot fold") << endl;

	return 0;
}
