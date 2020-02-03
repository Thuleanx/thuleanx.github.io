#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	stringstream ss;
	while (t--) {
		int k, x; cin>>k>>x;
		string s;
		for (; --x >= 0; x/=k)
			s.push_back('9' - k + 1 + x%k);
		reverse(s.begin(), s.end());
		ss << s << endl;	
	}
	cout << ss.str();

	return 0;
}
