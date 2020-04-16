
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

	int n; cin>>n;	
	int res[n];
	f(i,0,n) res[i] = 0;
	vector<pair<int,int>> gd;
	f(i,0,n) {
		int x = 1LL*i*i%n;
		if (!res[x]) {
			gd.push_back(mp(i, x));
			res[x] = 1;
		}
	}

	int mx = 0;
	f(i,0,n) {
		for (auto pp : gd) {
			if (res[(i + n - pp.second)%n]) {
				mx = max(mx, pp.first);
				break;
			}
		}
	}
	cout << mx << endl;

	return 0;
}
