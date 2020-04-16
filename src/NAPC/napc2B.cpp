
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

const ll ool = 1e18;
const int oo = 1e9+7;
ll modpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b&1) res = res*a%oo;
		a = a*a%oo;
		b /=2;
	}
	return res;
}

const int N = 75;
int n, ans;
bitset<N> a[N];
vi res;

void dfs(int i, int d, bitset<N> cur, vi &sto) {
	if (cur.count() == n) {
		ans = d;
		res = sto;
	} 
	if (d >= ans-1 || i == n) return;
	dfs(i+1, d, cur, sto);	
	sto.push_back(i);
	dfs(i+1, d+1, cur|a[i], sto);
	sto.pop_back();
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int T = 0;
	stringstream ss;
	while (cin>>n) {
		ans = 6; res.clear();
		f(i,0,n) {
			string s; cin>>s;
			s[i] = '1'; reverse(begin(s),end(s));
			a[i] = bitset<N>(s);
		}
		vi sto;
		dfs(0,0,bitset<N>(0), sto);	
		if (ans == 6) {
			bitset<N> cur(0);
			f(z,0,6) {
				int be = -1, best = -1;
				f(i,0,n) {
					int tot = (a[i]&(cur.flip())).count();
					if (tot < best) { 
						best = tot;
						be = i;
					}
				}
				res.push_back(be);
				cur |= a[be];
			}
		}
		ss << "Case " << ++T << ": ";
		ss << ans << " ";
		for (int x : res) ss << x+1 << " ";
		ss << endl;
	}
	cout << ss.str();

	return 0;
}
