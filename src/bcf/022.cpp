
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

const int N = 1e5+1;
int n;
int fi[N][2];
bool del[N];
map<int,int> freq[2]; // only store frequency pairs that are > 1 and valid
vector<int> one[2]; // only store ones that are one
vector<int> val[N][2];

void rem(int i) {
	f(j,0,2) {
		if (--freq[j][fi[i][j]] == 1) {
			freq[j].erase(fi[i][j]);
			one[j].push_back(fi[i][j]);
		} 
	}
	del[i] = 1;
}

void getall1(int j, vector<int> &acc) {
	for (int x : one[j])
		for (int y : val[x][j])
			if (!del[y]) acc.push_back(y);
}

void getall2(int j, vector<int> &acc) {
	for (auto pp : freq[j])
		for (int x : val[pp.first][j])
			if (!del[x]) acc.push_back(x);
}

int solve() {
	
	cin>>n;
	f(j,0,2) f(i,0,n) cin>>fi[i][j];
	f(j,0,2) {
		map<int,int> cnt;	
		f(i,0,n) cnt[fi[i][j]]++;

		f(i,0,n) val[fi[i][j]][j].push_back(i);

		for (auto pp : cnt) if (pp.second == 1)
			one[j].push_back(pp.first);
		else freq[j][pp.first] = pp.second;
	}

	int turns; cin>>turns;
	int cur = 0;
	while (turns--) {
		string s; cin>>s;
		vector<int> acc;
		if (s == "YES")
			getall2(cur, acc);
		else
			getall1(cur, acc);
		for (int x : acc)
			rem(x);
		cur ^= 1;
	}

	vector<int> pos;

	f(i,0,N) for (int x : val[i][0]) if (!del[x])
		pos.push_back(x);
	sort(begin(pos),end(pos));

	stringstream ss;
	if (pos.size())
		for (int x : pos)
			ss << x+1 << " ";
	else ss << -1;
	cout << ss.str() << endl;

	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	solve();

	return 0;
}
