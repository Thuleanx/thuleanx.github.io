
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

const int N = 1e5;
int n; 
vi adj[N];
int cnt[N], res[N];

void dfs(int v, int c) {
	res[v] = c;
	for (int w : adj[v]) if (res[w] == -1) 
		dfs(w, c^1);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	int p = 0;
	stringstream ss;
	while (t--) {
		cin>>n;
		int s[n], e[n];
		f(i,0,N) cnt[i] = 0, adj[i].clear();
		f(i,0,n) {
			cin>>s[i]>>e[i];
			cnt[s[i]]++; cnt[e[i]]--;
			res[i] = -1;
		}
		f(i,1,N) {
			cnt[i] += cnt[i-1];
			if (cnt[i] > 2) {
				ss << "Case #" << ++p << ": " << "IMPOSSIBLE" << endl;
				goto end;
			}
		}

		f(i,0,n) f(j,0,n) if (i != j && (IN(s[i],s[j],e[j]-1) || IN(e[i]-1,s[j],e[j]-1))) {
			adj[i].push_back(j);
			adj[j].push_back(i);
		}
		f(i,0,n) if (res[i] == -1)
			dfs(i,0);

		ss << "Case #" << ++p << ": ";
		f(i,0,n) ss << (res[i]?"C":"J");
		ss << endl;
end: {}
	}
	cout << ss.str();

	return 0;
}
