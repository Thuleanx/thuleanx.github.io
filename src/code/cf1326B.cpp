#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i>=a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n; cin>>n;
	long long b[n];
	f(i,0,n) cin>>b[i];

	long long x = 0;
	stringstream ss;
	f(i,0,n) {
		long long a = b[i]+x;
		x = max(x, a);
		ss << a << " ";
	}
	cout << ss.str() << endl;


	return 0;
}
