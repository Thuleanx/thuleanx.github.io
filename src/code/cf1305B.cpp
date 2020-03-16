#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string s; cin>>s;
	int n = s.length();

	vector<int> res, st;
	f(i,0,n) if (s[i] == ')')
		st.push_back(i);
	f(i,0,n) {
		if (s[i] == '(' && st.size() && st.back() > i)  {
			res.push_back(i);
			res.push_back(st.back()); st.pop_back();
		}
	}
	sort(begin(res),end(res));
	
	if (res.size()) {
		cout << 1 << endl;
		cout << res.size() << endl;
		for (int x : res) cout << x+1 << " ";
		cout << endl;
	} else cout << 0 << endl;

	return 0;
}
