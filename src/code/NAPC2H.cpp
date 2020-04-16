
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

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n; cin>>n;
	int a[n][n];
	f(i,0,n) f(j,0,n) cin>>a[i][j];

	int lo = 0, hi = 100;
	while (lo <= hi) {
		int mid = (lo+hi)/2;
		int cnt = 0;
		f(i,0,n) {
			f(j,0,n) if (a[i][j] <= mid) {
				cnt++;
				break;
			}
		}
		if (cnt == n) hi = mid-1;
		else lo = mid+1;
	}
	cout << lo << endl;

	return 0;
}
