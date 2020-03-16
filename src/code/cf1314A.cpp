#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define mp make_pair

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n; cin>>n;
	int a[n], t[n];
	f(i,0,n) cin>>a[i];
	f(i,0,n) cin>>t[i];
	vector<pair<int,int>> b(n);
	f(i,0,n) b[i] = mp(a[i],t[i]);
	sort(begin(b),end(b),greater<pair<int,int>>());

	priority_queue<int> pq;
	long long cost = 0, ans = 0;
	for (int x = 0; b.size() || pq.size(); x++) {
		if (!pq.size())
			x = b.back().first;
		while (b.size() && b.back().first == x) {
			cost += b.back().second;
			pq.push(b.back().second); 
			b.pop_back();
		}
		cost -= pq.top();
		pq.pop();
		ans += cost;
	}
	cout << ans << endl;

	return 0;
}
