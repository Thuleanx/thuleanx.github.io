#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i =a; i < b;i++)

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	while (t--) {
		int n; cin>>n;
		int a[n];
		int x = 0;
		if (n == 2) {
			cout << 1 << endl;
			continue;
		}
		f(i,0,n) {
			cin>>a[i];
			if (a[i] > 1) x++;
		}	
		cout << min(n/2, x) << endl;	
	}

	return 0;
}
