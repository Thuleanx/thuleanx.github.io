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

	int t; cin>>t;
	stringstream ss;
	while (t--) {

		int n; cin>>n;
		if (n == 1) {
			ss << -1 << endl;
		} else {
			string s;
			int cnt = 0;
			for (int i = 0; i < n; i++) {
				s += (i==n-1?'3':'2');
				cnt += s[i]-'0';
			}
			if (cnt % 3 == 0) 
				s[n-2] = '3';
			ss << s << endl;
		}
	}
	cout << ss.str();


	return 0;
}
