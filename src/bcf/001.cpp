// 1329A https://codeforces.com/problemset/problem/1329/A

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

const int N = 1e5;
int n, m;
int l[N];
ll p[N];

int solve() {
	cin>>m>>n;
	f(i,0,n) cin>>l[i];
	fr(i,0,n) p[i] = i == n-1 ? 0 : p[i+1] + l[i+1];
	
	int R = 0, L = 0;
	stringstream ss;
	f(i,0,n) {
		while (max(L+l[i], R) + p[i] < m) L++;
		if ((!i && L) || L+l[i] > m) {
			cout << -1 << endl;
			return 0;
		}
		R = max(R, L+l[i]);
		ss << ++L << " ";
	}
	if (R < m) {
		cout << -1 << endl;
	} cout << ss.str() << endl;
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	solve();	

	return 0;
}
