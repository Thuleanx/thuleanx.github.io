#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)

const int N = 4e8;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m; cin>>n>>m;
	vector<long long> ans;
	long long d = 1;
	f(i,0,n) {
		if (m == 0 && (!ans.size() || ans.back() < N))
			ans.push_back(N);
		else if (m==0)
			ans.push_back(ans.back() + (d+1));
		else if (m < i/2) {
			ans.push_back((ans.size()?ans.back():0) + ans[i-2*m]);
			d = ans.back();
			m = 0;
		} else {
			ans.push_back((ans.size()?ans.back():0) + 1);
			m -= i/2;
			d = ans.back();
		}
	}
	if (m) cout << -1 << endl;
	else {
		for (long long x : ans)
			cout << x << " ";
		cout << endl;
	}

	return 0;
}
