#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n; 
	string s;
	cin>>n>>s;

	int cnt = 0;
	int ls = -1;

	int ans = 0;
	f(i,0,n) {
		if (s[i] == '(') {
			cnt++;
			if (cnt == 0)
				ans += i-ls;
		} else cnt--;
		if (cnt == 0) ls = i;
	}
	cout << (cnt?-1:ans) << endl;

	return 0;
}
