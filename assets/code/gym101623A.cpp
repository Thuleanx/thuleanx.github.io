#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n; cin>>n;
	int a[n], b[n];
	for (int i = 0; i < n; i++) {
		cin>>a[i];
		b[i] = a[i];
	}
	map<pair<int,int>, int> cnt;
	sort(b,b+n);
	for (int i = 0; i < n-1; i++)
		cnt[make_pair(b[i],b[i+1])]++;
	if (cnt[make_pair(a[n-1],a[0])])
		cnt[make_pair(a[n-1],a[0])]--;
	int ans = 0;
	for (int i = 0; i < n-1; i++) {
		pair<int,int> pp = make_pair(a[i],a[i+1]);
		if (!cnt.count(pp) || !cnt[pp]) {
			ans++;
		} else cnt[pp]--;
	}
	cout << ans << endl;

	return 0;
}
