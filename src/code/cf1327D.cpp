
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i>=a; i--)
#define IN(i,a,b) (a<=(i) && (i)<=b)
#define mp make_pair
#define mt make_tuple

const int oo = 1e9;

int gcd(int a, int b) {
	return a?gcd(b%a, a):b;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	stringstream ss;
	while (t--) {
		int n; cin>>n;
		int p[n], c[n];
		f(i,0,n) {
			cin>>p[i];
			p[i]--;
		}
		f(i,0,n) cin>>c[i];

		bool vis[n];
		f(i,0,n) vis[i] = 0;

		int k = oo;

		f(s,0,n) if (!vis[s]) {
			// all arithmetic progressions have the same colors

			vector<int> cyc;
			{
				int z = s;
				do {
					vis[z] = 1;
					cyc.push_back(z);
					z = p[z];
				} while (z != s);
			}
			int m = cyc.size();
			f(d,1,m) if (gcd(m,d) == d) {
				// O(n), but happens only a few times
				
				int cq[d];
				f(z,0,d) cq[z] = c[cyc[z]];
				bool gd[d];
				f(z,0,d) gd[z] = 1;
			
				f(z,0,m) gd[z%d] &= cq[z%d] == c[cyc[z]];
			
				f(z,0,d) if (gd[z]) k = min(k,d);
			}
			k = min(k, m);
		}

		ss << k << endl;
	}
	cout << ss.str();

	return 0;
}
