
#include <bits/stdc++.h>
using namespace std;

const int N = 2500;

#define f(i,a,b) for (int i = a; i <b ; i++)
#define IN(i,a,b) (a<=i&&i<=b)

int n;
int a[N][N];
int r[N];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	stringstream ss;
	while (t--) {
		cin>>n;
		f(i,0,n) {
			string s; cin>>s;
			f(j,0,n) {
				a[i][j] = s[j]=='1';
				if (a[i][j])
					r[i] = j;
			}
		}
		int ans = 0;
		f(i,0,n) {
			int mi = n, ma = -1;
			f(j,i,n) {
				mi = min(mi, r[j]);
				ma = max(ma, r[j]);
				if (ma-mi == j-i) ans++;
			}
		}
		ss << ans << endl;
	}
	cout << ss.str();

	return 0;
}
