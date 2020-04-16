
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

const int N = 1<<22;
int g,h;
int n,m;
int pos[N], a[N];

bool pa(int i) {
	int j = i;
	while (a[j<<1] || a[j<<1|1]) {
		if (a[j<<1] > a[j<<1|1]) j = j<<1;
		else j = j<<1|1;
	}
	return j >= m;
}

void exec(int i) {
	int j = i;
	while (a[j]) {
		if (!a[j<<1] && !a[j<<1|1])
			a[j] = 0;
		else if (a[j<<1]>a[j<<1|1]) {
			a[j] = a[j<<1];
			pos[a[j<<1]] = j;
			j = j<<1;
		} else {
			a[j] = a[j<<1|1];
			pos[a[j<<1|1]] = j;
			j = j<<1|1;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	stringstream ss;
	while (t--) {
		cin>>g>>h; n = 1<<g; m = 1<<h;
		f(i,1,n) cin>>a[i];
		ll sum = 0;
		f(i,1,n) {
			sum += a[i];
			pos[a[i]] = i;
		}

		priority_queue<int> pq;
		f(i,1,n) pq.push(a[i]);

		int cnt = 0;
		vi ans(n-m);
		while (pq.size() && cnt < n-m) {
			int v = pq.top(); pq.pop();
			
			// 20 steps
			if (pa(pos[v])) {
				ans[cnt++] = pos[v];
				sum -= v; 
				exec(pos[v]);
			}
		}

		ss << sum << endl;
		for (int x : ans) ss << x << " ";
		ss << endl;

		f(i,1,n) a[i] = 0;
	}
	cout << ss.str();

	return 0;
}
