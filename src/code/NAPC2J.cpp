
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple

using ll = long long;

const int mod = 1e9+7;  
ll modpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b&1) res = res*a%mod;
		a = a*a%mod;
		b /=2;
	}
	return res;
}

int interact(int x) {
	if (x) cout << '+' << endl;
	else cout << '-' << endl;
	fflush(stdout);
	int gd; cin>>gd;
	return gd;
}

void declare(string s) {
	cout << "! " << s << endl;
	fflush(stdout);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	while (1) {
		if (interact(1)) {
			declare("ugly");
		}
		interact
	}
	declare("ugly");

	return 0;
}
