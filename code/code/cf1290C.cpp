#include <bits/stdc++.h>
using namespace std;

const int N = 6e5;
int n, k, ans;
int a[N];
vector<int> lamp[N];
vector<int> sw[N];
int dsu[N], sz[N], fc[N], num[N];

void init() {
	for (int i =0 ;i  < N; i++)
		dsu[i] = i, sz[i] = i, num[i] = !(i&1), fc[i] = 0;
}

int root(int v) { return dsu[v] = dsu[v] == v ? v : root(dsu[v]); }
void merge(int v, int w) {

	v = root(v); w = root(w);
	int vv = root(v^1), ww = root(w^1);
	if (v == w) return;
	
	if (fc[w]) ans -= num[w];
	else if (fc[ww]) ans -= num[ww];
	else ans -= min(num[w], num[ww]);

	if (fc[v]) ans -= num[v];
	else if (fc[vv]) ans -= num[vv];
	else ans -= min(num[v],num[vv]);


	// if one is forced, we only change that
	if (fc[vv] || fc[ww]) 
		ans += num[vv] + num[ww];
	else if (fc[v] || fc[w])
		ans += num[v] + num[w];
	else ans += min(num[vv]+num[ww], num[v]+num[w]);

	// now we merge
	if (sz[v] < sz[w]) swap(v,w);
	dsu[w] = v; sz[v] += sz[w]; num[v] += num[w]; fc[v] |= fc[w];
	if (sz[vv] < sz[ww]) swap(vv,ww);
	dsu[ww] = vv; sz[vv] += sz[ww]; num[vv] += num[ww]; fc[vv] |= fc[ww];
}

void force(int v) {
	v = root(v);
	if (fc[v]) return;
	int w = root(v^1); // other side, not sure why
	ans += num[v] - min(num[v], num[w]);
	fc[v] = 1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>k;
	string s; cin>>s;
	for (int i = 0; i < n; i++)
		a[i] = s[i]-'0';

	for (int i = 0; i < k; i++) {
		int sz; cin>>sz;
		while (sz--) {
			int x; cin>>x; x--;
			sw[i].push_back(x);
			lamp[x].push_back(i);
		}
	}
	init();

	ans = 0;

	stringstream ss;

	for (int i = 0; i < n; i++) {
		if (lamp[i].size() == 2) {
			if (a[i]) merge(lamp[i][0]<<1, lamp[i][1]<<1);
			else merge(lamp[i][0]<<1, lamp[i][1]<<1|1);
		} else if (lamp[i].size() == 1) {
			if (a[i]) force(lamp[i][0]<<1|1);
			else force(lamp[i][0]<<1);
		}
		ss << ans << endl;
	}
	cout << ss.str();

	return 0;
}
