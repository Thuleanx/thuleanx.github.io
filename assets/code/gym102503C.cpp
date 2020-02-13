#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;

	char A[] = {'T', 's', 'l'};
	stringstream ss;
	while (t--) {
		int n; cin>>n;

		string s; cin>>s;

		int cnt[] = {0,0,0};
		for (char c : s)
			for (int i = 0; i < 3; i++)
				if (c == A[i])
					cnt[i]++;
		ss << cnt[0] << " " << cnt[1] << " " << cnt[2] << endl;
	}
	cout << ss.str();

	return 0;
}
