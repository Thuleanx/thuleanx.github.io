#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)

int n;
vector<int> p, fi;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n;
	p = vector<int>(n); fi = vector<int>(n);
	f(i,0,n) cin>>p[i];
	f(i,0,n) cin>>fi[i];
	
	vector<pair<int,int>> v;
	f(i,0,n) v.emplace_back(p[i],i);
	sort(begin(v),end(v));
	sort(begin(fi), end(fi));

	int best = -1, bests = -1;
	f(s,0,n) {
		int cnt = 0;
		f(i,0,n) cnt += v[i].first < fi[(i+s)%n];
		if (cnt >= best) best = cnt, bests = s;
	}

	vector<int> ans(n);
	f(i,0,n)
		ans[v[i].second] = fi[(i+bests)%n];
	
	f(i,0,n)
		cout << ans[i] << " ";
	cout << endl;

	return 0;
}
