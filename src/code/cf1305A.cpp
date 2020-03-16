#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	stringstream ss;
	while (t--) {
		int n; cin>>n;
		int a[n], b[n];
		f(i,0,n) cin>>a[i];
		f(i,0,n) cin>>b[i];
		sort(a,a+n);
		sort(b,b+n);
		f(i,0,n) ss << a[i] << " \n"[i==n-1];
		f(i,0,n) ss << b[i] << " \n"[i==n-1];
	}
	cout << ss.str();

	return 0;
}
