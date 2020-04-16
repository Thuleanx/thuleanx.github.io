
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
		long long k; cin>>k;
		long long a[n];
		f(i,0,n) cin>>a[i];
		
		bool yes = 1;
		while (1) {
			int cnt = 0;
			f(i,0,n) cnt += a[i]%k;

			if (cnt > 1) yes = 0;	
			
			bool gd = 0;
			f(i,0,n) {
				a[i] /= k;
				gd |= a[i];
			}
			if (!gd) break;
		}

		ss << (yes?"YES":"NO") << endl;	
	}
	cout << ss.str();

	return 0;
}
