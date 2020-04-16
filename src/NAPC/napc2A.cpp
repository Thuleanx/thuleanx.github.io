#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple
#define sz(a) a.size()

using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi = vector<int>;

#define x first
#define y second

const ll oo = 1e18+7;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n; cin>>n;
	pii p[n];
	f(i,0,n) {
		int a,b;cin>>a>>b;
		p[i] = mp(a,b);
	}

	priority_queue<pii,vector<pii>,greater<pii>> pq[3];	
	f(i,0,n) pq[0].push(mp(p[i].x + p[i].y, i));

	bool taken[n];
	f(i,0,n) taken[i] = 0;

	pii cur(1,1);

	int a[n],b[n];
	f(i,0,n) a[i] = i;
	f(i,0,n) b[i] = i;
	sort(a,a+n,[&](int i, int j) { return p[i].x < p[j].x; });
	sort(b,b+n,[&](int i, int j) { return p[i].y < p[j].y; });

	int j = 0, k = 0;	

	vi ans;

	while (sz(ans) < n) {
		while (j < n && p[a[j]].x <= cur.x) {
			pq[1].push(mp(p[a[j]].y, a[j]));
			j++;
		}
		while (k < n && p[b[k]].y <= cur.y) {
			pq[2].push(mp(p[b[k]].x, b[k]));
			k++;
		}

		while (pq[0].size() && (taken[pq[0].top().y] || p[pq[0].top().y].x <= cur.x || p[pq[0].top().y].y <= cur.y)) pq[0].pop();
		while (pq[1].size() && taken[pq[1].top().y]) pq[1].pop();
		while (pq[2].size() && taken[pq[2].top().y]) pq[2].pop();

		pll best(oo,oo);
		if (pq[0].size())
			best = min(best, pll(pq[0].top().x - cur.x - cur.y, pq[0].top().y));
		if (pq[1].size())
			best = min(best, pll(pq[1].top().x - cur.y, pq[1].top().y));
		if (pq[2].size())
			best = min(best, pll(pq[2].top().x - cur.x, pq[2].top().y));

		if (best.y == oo) break;

		taken[best.y] = 1;
		ans.push_back(best.y);
		cur = mp(max(cur.x, p[best.y].x), max(cur.y, p[best.y].y));
	}
	for (int x : ans) cout << 1+x << " ";
	cout << endl;


	return 0;
}
