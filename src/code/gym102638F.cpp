#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)

const int N = 3e5+7;
int n;
int a,b;
int ar[N];
long long c[N], g[N];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>a>>b;
	f(i,0,n) cin>>ar[i];

	f(i,0,n) {
		if (ar[i]%b)	c[i] = (ar[i]%b+a-1)/a + 1;
		else			c[i] = (b+a-1)/a + 1;
		g[i] = (i?g[i-1]:0) + (ar[i]+b-1)/b;
	}

	priority_queue<long long> pq;
	long long sum = 0;
	int ans = 0;
	f(i,0,n) {
		pq.push(c[i]);
		sum += c[i];
		if (sum > g[i] + 1) {
			// oh no
			sum -= pq.top(); pq.pop();
		}
		ans = max(ans, int(pq.size()));
	}
	cout << ans << endl;
	return 0;
}
