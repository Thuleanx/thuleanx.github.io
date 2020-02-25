#include <bits/stdc++.h>
using namespace std;

const int X = 26;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string s; cin>>s;
	int n = s.length();
	int freq[n][X];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < X; j++)
			freq[i][j] = i?freq[i-1][j]:0;
		freq[i][s[i]-'a']++;
	}

	int q; cin>>q;
	stringstream ss;
	while (q--) {
		int i, j; cin>>i>>j;
		i--;j--;
		int cnt = 0;
		for (int k = 0; k < X; k++) {
			cnt += freq[j][k] - (i?freq[i-1][k]:0) > 0;
		}

		// if not equal, YES
		if (i == j) cout << "Yes" << endl;
		else if (s[i] != s[j]) cout << "Yes" << endl;
		else cout << (cnt>2 ? "Yes":"No") << endl;	
	}
	cout << ss.str();

	return 0;
}
