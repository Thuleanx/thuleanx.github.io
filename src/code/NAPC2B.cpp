
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple

using ll = long long;
using vi = vector<int>;

const int mod = 1e9+7;  
ll modpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b&1) res = res*a%mod;
		a = a*a%mod;
		b /=2;
	}
	return res;
}

const int N = 75;
int n, ans = 6;
bitset<N> goal;
bitset<N> a[N];
vi sol;

void dfs(int i, int d, bitset<N> cur, vi &part) {
	if (cur == goal && d < ans) {
		sol = part;
		ans = d;
	}
	if (d >= ans-1 || i == n) return;
	
	dfs(i+1,d,cur,part);
	part.push_back(i);
	dfs(i+1,d+1,cur|a[i],part);
	part.pop_back();
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t = 0;
	while (cin>>n) {
		goal = bitset<N>(0); 
		ans = 6; 
		sol.clear();
		f(i,0,n) goal[i] = 1;
		f(i,0,n) {
			string s; cin>>s; s[i] = '1';
			reverse(begin(s),end(s));
			a[i] = bitset<N>(s);
		}
		vi part;
		dfs(0,0,bitset<N>(0),part);
		if (ans == 6) {
			bitset<N> cur(0);
			f(z,0,6) {
				int be = -1, cnt = -1;
				f(i,0,n) {
					int num = (cur^goal^a[i]).count();
					if (num > cnt) {
						cnt = num;
						be = i;
					}
				}
				sol.push_back(be);
				cur |= a[be];
			}
		}
		cout << "Case " << ++t << ": " << sol.size() << " ";
		for (int x : sol) cout << x+1 << " ";
		cout << endl;
	}


	return 0;
}
