#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n; cin>>n;
	stringstream ss;
	while (n--) {
		string s; cin>>s;
		ss << s << ": " << "F" << endl;
	}
	cout << ss.str();

	return 0;
}
