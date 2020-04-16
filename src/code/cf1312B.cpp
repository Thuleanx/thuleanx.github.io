
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i>=a; i--)
#define IN(i,a,b) (a<=(i) && (i)<=b)
#define mp make_pair
#define mt make_tuple

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	stringstream ss;
	while (t--) {
		int n; cin>>n;
		int a[n];
		f(i,0,n) cin>>a[i];
		sort(a,a+n,greater<int>());
		f(i,0,n) ss << a[i] << " \n"[i==n-1];	
	}
	cout << ss.str();

	return 0;
}
