
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

	int n, m; cin>>n>>m;

	string s; cin>>s;
	int p[n];
	f(i,0,n) p[i] = ((i?p[i-1]*10%m:0) + (s[i]-'0'))%m;

	int cnt = 0;
	f(i,0,n) if (!p[i]) cnt++;
	if (p[n-1]) cout << 0 << endl;
	else cout << modpow(2, cnt-1) << endl;

	return 0;
}
