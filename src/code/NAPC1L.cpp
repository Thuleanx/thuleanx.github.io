#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define mp make_pair

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);


	int n; cin>>n;

	long long p[n+1];
	p[0] = 1;
	f(i,1,n+1) p[i] = p[i-1]*i;

	long double x[4];
	f(i,0,4) cin>>x[i];

	long double pa[4][n+1];
	f(i,0,4) {
		pa[i][0] = 1;
		f(j,1,n+1) pa[i][j] = pa[i][j-1]*x[i];
	}

	priority_queue<pair<long double, long long>> pq;

	f(a,0,n+1) f(b,0,n-a+1) f(c,0,n-a-b+1)  {
		int d = n-a-b-c;
		long double pr = pa[0][a] * pa[1][b] * pa[2][c] * pa[3][d];
		pq.push(mp(-pr, p[n] / p[a] / p[b] / p[c] / p[d]));
	}

	long double ans = 0;
	while (pq.size() > 1) {
		auto pp = pq.top(); pq.pop();
		long double pr = pp.first; long long cnt = pp.second;

		if (cnt == 1) {
			auto pp2 = pq.top(); pq.pop();
			long double pr2 = pp2.first; long long cnt2 = pp2.second;
			pq.push(mp(pr+pr2,1));
			ans += (pr + pr2);
			if (cnt2-cnt) pq.push(mp(pr2,cnt2-1));
		} else {
			ans += 2*pr*(cnt/2);
			pq.push(mp(2*pr, cnt/2));
			if (cnt&1) pq.push(mp(pr, 1));
		}
	}

	cout << setprecision(40) << -ans << endl;





	return 0;
}
