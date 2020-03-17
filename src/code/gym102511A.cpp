
/*
 * Problem: Azulejos
 * Platform: Codeforces Gym
 * Contest: ICPC World Finals 2019
 * Date: 28022020
 * Score: +
 * Description: 
 * Tags: 
 */
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = b-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple
#define g(i,a) get<i>(a)

const int N = 5e5, oo = 1e9;

int n;
int p[N][2], h[N][2];
vector<tuple<int,int,int>> mem[2];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n;		
	fr(z,0,2) {
		f(i,0,n) cin>>p[i][z];
		f(i,0,n) cin>>h[i][z];
		f(i,0,n) mem[z].push_back(mt(p[i][z], h[i][z], i));
		sort(begin(mem[z]), end(mem[z]), greater<tuple<int,int,int>>());
	}

	set<pair<int,int>, greater<pair<int,int>> > a;
	set<pair<int,int>> b;
	int ans[n][2];

	int z = 0;
	while (mem[0].size() || mem[1].size()) {
		if (!a.size()) {
			int y = 0, x = g(0,mem[y].back());
			while (mem[y].size() && g(0,mem[y].back()) == x) {
				a.insert(mp(g(1, mem[y].back()), g(2,mem[y].back())));
				mem[y].pop_back();
			}
		}
		if (!b.size()) {
			int y = 1, x = g(0,mem[y].back());
			while (mem[y].size() && g(0,mem[y].back()) == x) {
				b.insert(mp(g(1, mem[y].back()), g(2,mem[y].back())));
				mem[y].pop_back();
			}
		}
		

		if (a.size() < b.size()) {
			while (a.size()) {
				auto pp = a.begin();
				int h = pp->first, i = pp->second;

				auto ppp = b.upper_bound(mp(h,oo));
				int hh = ppp->first, ii = ppp->second;
				if (ppp == b.end()) {
					cout << "impossible" << endl;
					return 0;
				}

				ans[z][0] = i; 
				ans[z++][1] = ii;
			
				b.erase(ppp);
				a.erase(pp);
			}
		} else {
			while (b.size()) {
				auto pp = b.begin();
				int h = pp->first, i = pp->second;

				auto ppp = a.upper_bound(mp(h,-oo));
				if (ppp == a.end()) {
					cout << "impossible" << endl;
					return 0;
				}
				int hh = ppp->first, ii = ppp->second;

				ans[z][0] = ii; 
				ans[z++][1] = i;
			
				b.erase(pp);
				a.erase(ppp);
			}
		}
	}

	stringstream ss;
	fr(z,0,2) f(i,0,n)
		ss << ans[i][z]+1 << " \n"[i == n-1];
	cout << ss.str();
	

	return 0;
}
