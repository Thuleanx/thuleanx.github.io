#include <bits/stdc++.h>
using namespace std;

const int N = 40;
int n, m;
int v[N];

void add(int &a, int b) {
	a += b;
	if (a >=m) a%=m;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>m;
	for (int i = 0; i < n; i++)
		cin>>v[i];
	int a = n/2, b = n-a;

	vector<int> sums;
	for (int mask = 0; mask < (2<<a); mask++) {
		int value = 0;
		for (int i = 0; i < a; i++)
			if (mask>>i&1)
				add(value, v[i]);
		sums.push_back(value);
	}
	sort( begin(sums), end(sums) );

	int best = 0;

	for (int mask = 0; mask < (2<<b); mask++) {
		int value = 0;
		for (int i = 0; i < b; i++)
			if (mask>>i&1)
				add(value, v[i+a]);
		
		int lo = 0, hi = sums.size()-1;
		while (lo <= hi) {
			int mid = lo+hi>>1;
			
			if (sums[mid] + value < m)
				lo = mid+1;
			else hi = mid-1;
		}

		best = max(best, sums[hi] + value);
		best = max(best, (sums.back() + value)%m); 
	}
	cout << best << endl;

	return 0;
}
