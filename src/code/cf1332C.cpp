
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	stringstream ss;
	while (t--) {
		int n, k; cin>>n>>k;
		map<int,int> cnt[k];
		vector<int> tot(n);
		string s; cin>>s;
		f(i,0,n) {
			int z = i%k; z = min(z, k-1-z);
			cnt[z][s[i]]++;
			tot[z]++;
		}
		int ans = 0;
		f(i,0,k) if (i == min(i,k-i)) {
			int mx = 0;
			for (auto pp : cnt[i]) mx = max(mx, pp.second);
			ans += tot[i]-mx;
		}
		ss << ans << endl;
	}
	cout << ss.str();

	return 0;
}
