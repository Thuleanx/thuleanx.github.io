#include <bits/stdc++.h>
using namespace std;

const int oo = 1e9;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	while (t--) {
		int n,m,k; cin>>n>>m>>k;
		int a[n];
		for (int i =0 ; i < n; i++)
			cin>>a[i];
		m = n - m + 1;
		// n - m + 1 - k;
		

		int res = 0;
		
		int r = max(1, n-m+1-k);
		for (int i = 0; i+m-1 < n; i++) if (i+m-1+r <= n) {
			int tmp = oo;
			for (int j = 0; j < r; j++)
				tmp = min(tmp, max(a[i+j], a[i+j+m-1]));	
			res = max(res, tmp);
		}

		cout << res << endl;
	}

	return 0;
}
