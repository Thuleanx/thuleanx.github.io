
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple

using ll = long long;
using pii = pair<ll,ll>;
using vi = vector<int>;

const int mod = 1e9+7;
const ll oo = 1e18;
ll modpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b&1) res = res*a%mod;
		a = a*a%mod;
		b /=2;
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n; cin>>n;
	pii a[n];
	f(i,0,n) {
		int x,y; cin>>x>>y;
		a[i] = mp(x,y);
	}


	pii cur = mp(1,1);

	int p[n],q[n];
	f(i,0,n) p[i] = i;
	f(j,0,n) q[j] = j;
	sort(p,p+n,[&](int i, int j) { return a[i].first < a[j].first; });
	sort(q,q+n,[&](int i, int j) { return a[i].second < a[j].second; });

	priority_queue<pii, vector<pii>, greater<pii>> pa, pb, pc;
	f(i,0,n) pa.push(mp(a[i].first + a[i].second, i));

	bool take[n];
	f(i,0,n) take[i] = 0;

	vi sol;
	int lt = 0, rt = 0;
	while (sol.size() < n) {
		while (lt < n && a[p[lt]].first <= cur.first) {
			pb.push(mp(a[p[lt]].second, p[lt]));
			lt++;
		}
		while (rt < n && a[q[rt]].second <= cur.second ) {
			pc.push(mp(a[q[rt]].first, q[rt]));
			rt++;
		}

		while (pa.size() && take[pa.top().second]) pa.pop();
		while (pb.size() && take[pb.top().second]) pb.pop();
		while (pc.size() && take[pc.top().second]) pc.pop();

		pii w(oo,oo);

		if (pa.size()) w = min(w, pii(pa.top().first - cur.first - cur.second, pa.top().second));
		if (pb.size()) w = min(w, pii(pb.top().first - cur.second, pb.top().second));
		if (pc.size()) w = min(w, pii(pc.top().first - cur.first, pc.top().second));

		sol.push_back(w.second);
		take[w.second]=1;
	}

	for (int x : sol) cout << x+1 << " ";
	cout << endl;

	return 0;
}
