#include <bits/stdc++.h>
using namespace std;

const int N = 2e5;

struct BIT {
	long long tree[N];
	BIT() { for (int i = 0; i < N; i++) tree[i] = 0; }
	void add(int v, long long value) {
		for (; v >= 0; v = (v&(v+1))-1)
			tree[v] += value;
	}
	long long sum(int v) {
		long long res = 0;
		for (; v < N; v |= v+1)
			res += tree[v];
		return res;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n; cin>>n;
	int x[n], v[n];
	
	for (int i = 0; i < n; i++) cin>>x[i];

	map<int,int> dpv;
	for (int i = 0; i < n; dpv[v[i++]] = 0) cin>>v[i]; 
	int p = 0;
	for (auto pp : dpv) dpv[pp.first] = p++;

	for (int i = 0; i < n; i++) v[i] = dpv[v[i]];

	vector<pair<int,int>> vpp;
	for (int i = 0; i < n; i++) vpp.push_back({x[i], v[i]});

	sort(begin(vpp),end(vpp));
	for (int i = 0; i < n; i++) x[i] = vpp[i].first, v[i] = vpp[i].second;

	BIT coun, fsum;

	long long ans = 0;
	
	for (int i = n-1; i >= 0; i--) {
		ans += fsum.sum(v[i]) - x[i] * coun.sum(v[i]);	
		fsum.add(v[i], x[i]);
		coun.add(v[i], 1);
	}

	cout << ans << endl;


	return 0;
}
