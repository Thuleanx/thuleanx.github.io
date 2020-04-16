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

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n,m; cin>>m>>n;

	int a[n];
	f(i,0,n) cin>>a[i];
	ll rev[n];
	fr(i,0,n) rev[i] = (i<n-1?rev[i+1]+a[i+1]:0);

	int R = 0;
	stringstream ss;
	
	int cur = 0;
	f(i,0,n) {
		while (m - max(R, cur+a[i]) > rev[i] && cur <= R) cur++;
		if (cur+a[i] > m) {
			cout << -1 << endl;
			return 0;
		}
		ss << cur+1 << " ";
		R = max(R, cur+a[i]);
		cur++;
	}

	if (R < m) cout << -1 << endl;
	else cout << ss.str();

	return 0;
}
