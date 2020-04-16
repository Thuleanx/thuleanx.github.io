
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
	while (t--) {
		long long n, k;
		cin>>n>>k;

		long long x = 1LL*k*k;


		cout << ((n%2==k%2 && x <= n) ? "YES" : "NO") << endl;
	}
		

	return 0;
}
