
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

const int N = 5e5;

int n;
int p[N][2], h[N][2];
vector<tuple<int,int,int>> mem[2];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n;		
	f(z,0,2) {
		f(i,0,n) cin>>p[i][z];
		f(i,0,n) cin>>h[i][z];
		f(i,0,n)
			mem[z].push_back(mt(p[i][z], h[i][z], i));
		sort(begin(mem[z]), end(mem[z]), greater<tuple<int,int,int>>());
	}

	set<pair<int,int>> a[2];
	int ans[n][2];
	f(z,0,n) {
		f(y,0,2) {
			if (a[y].size()) {
				int x = get<0>(mem[y].back());
				while (mem[y].size() && get<0>(mem[y].back()) == x) {
					a[y].push_back(mem[y].b);

				}
			}
		}
		if (!a[0].size()) {
			int x = get<0>(mem[0].back());
			while (mem[0].size() && get<0>(mem[0].back()) == x) {
				a[0].
				mem[0].pop_back();
			}
		}
	}
	

	return 0;
}
