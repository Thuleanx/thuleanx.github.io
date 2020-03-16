#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)

const int N = 3e5+7;

int n,a,b;
long long h[N], ff[N], g[N];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin>>n>>a>>b;
	f(i,0,n) {
		cin>>h[i]; h[i]--;
		ff[i] = h[i] % b / a + 1 + 1;
		g[i] = (i?g[i-1]:0) + h[i] / b + 1;
	}
	priority_queue<long long> pq;
	long long s = 0;
	f(i,0,n) {
		pq.push(ff[i]); s += ff[i];
		if (s > g[i] + 1) {
			s -= pq.top();
			pq.pop();
		}
	}
	cout << pq.size() << endl;


	return 0;
}
