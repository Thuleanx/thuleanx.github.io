
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
using vi  = vector<int>;

const int oo = 1e9+7;
const ll ool = 1e18;

ll modpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b&1) res = res*a%oo;
		a = a*a%oo;
		b /=2;
	}
	return res;
}

const int N = 2e5;

int n;
int re[N];
struct BIT {
	int tree[N];
	void add(int v, int x) {
		for (; v < n; v |= v+1)
			tree[v] += x;
	}
	int sum(int v) {
		int res = 0;
		for (; v >= 0; v = (v&(v+1))-1)
			res += tree[v];
		return res;
	}
	void reset() { f(i,0,n) tree[i] = 0; }
};


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;

	BIT ds;
	stringstream ss;
	while (t--) {
		string s; cin>>s;
		n = s.length();
		ds.reset();
		f(i,0,n) re[i] = -1;

		vector<pii> res(4*n);
		int cnt = 0;
		queue<tuple<int,int,int>> pq;

		f(i,0,n) {
			int j = i;
			while (j < n-1 && s[j] != s[j+1]) j++;

			re[i] = re[j] = cnt;
			if (s[i] != s[j]) pq.push(mt(i,j,cnt));
			res[cnt++] = pii(i, j);
			i = j;
		}

		vector<pii> ans;
		while (pq.size()) {
			auto pp = pq.front(); pq.pop();		

			int i = get<0>(pp), j = get<1>(pp), k = get<2>(pp);

			if (i > 0 && j < n-1 && re[i] == re[j] && re[i] == k) {
				int z = ds.sum(i-1), y = ds.sum(j);

				ans.push_back(pii(i-z,j-y));

				ds.add(i, j-i+1-(y-z));

				if (i > 0 && j < n-1) { // merge neighborings
					int ii = res[re[i-1]].first, jj = res[re[j+1]].second;
					re[ii] = re[jj] = cnt;
					
					if (s[ii] != s[jj]) pq.push(mt(ii,jj,cnt));

					res[cnt++] = pii(ii,jj);
				}

				re[i] = re[j] = -1;
			}
		}

		f(i,0,cnt) if (re[res[i].first] == re[res[i].second] && re[res[i].first] == i) {
			int z = ds.sum(res[i].first-1), y = ds.sum(res[i].second);

			ans.push_back(pii(res[i].first-z, res[i].second-y));

			ds.add(res[i].first, res[i].second - res[i].first + 1 - (y-z));
		}
		ss << ans.size() << endl;
		for (auto pp : ans)
			ss << pp.first+1 << " " << pp.second+1 << endl;
	}
	cout << ss.str();

	return 0;
}
