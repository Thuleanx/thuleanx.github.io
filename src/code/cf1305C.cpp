
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin>>n>>m;
	int a[n];
	f(i,0,n) cin>>a[i];

	if (n > 2*m) {
		cout << 0 << endl;
	} else {
		long long res = 1;
		f(i,0,n) f(j,0,i) res = res*abs(a[j]-a[i])%m;
		cout << res << endl;
	}


	return 0;
}
