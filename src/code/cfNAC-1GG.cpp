
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i>=a; i--)
#define IN(i,a,b) (a<=(i) && (i)<=b)
#define mp make_pair
#define mt make_tuple

vector<int> transform(string &s) {
	int n = s.length();
	vector<int> res;

	f(i,1,n) {
		if (s[i] == '1') {
			int j = i;
			while (j >= 2 && s[j-1] == s[j-2] && s[j-2] == '0') {
				res.push_back(j-2);
				s[j-2] = '1'; s[j] = '0';
				j -= 2;
			}
			if (j && s[j] == s[j-1] && s[j-1] == '1') {
				s[j] = s[j-1] = '0';
				res.push_back(j);
			}
		}
	}

	if (n%2 == 1 && s[0] == '1')
		f(i,1,n) res.push_back(i++);
	if (n%2 == 0) {
		int cnt = 0;
		f(i,0,n) cnt += s[0] == s[i];
		if (cnt == n && s[0] != '1') {
			f(i,0,n) res.push_back(i++);
		}
	}

	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string s, r; cin>>s>>r;
	if (s == r) {
		cout << 0 << endl;
	} else {
		vector<int> a = transform(s), b = transform(r);
		reverse(begin(b),end(b));
		stringstream ss;
		ss << a.size() + b.size() << endl;
		for (int x : a) ss << x << endl;
		for (int x : b) ss << x << endl;
		cout << ss.str();
	}

	return 0;
}
