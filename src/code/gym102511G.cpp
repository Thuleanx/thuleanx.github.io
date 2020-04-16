#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i>=a; i--)
#define mt make_tuple 
#define mp make_pair

const int N = 2e6, K = 22;
int n, k;
int p[N][K], q[N][K], x[N];
char c[N];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>k;
	f(i,0,n) {
		cin>>c[i];
		cin>>p[i][0]; p[i][0]--;
	}
	f(i,0,n) q[i][0] = c[i];
	
	f(k,1,K) {
		vector<tuple<int,int,int>> tp;
		f(i,0,n) {
			if (p[i][k-1] != -1) tp.push_back(mt(q[i][k-1], q[p[i][k-1]][k-1], i));	
			else tp.push_back(mt(q[i][k-1], -1, i));
		}
		sort(begin(tp), end(tp));
		int r = -1;
		f(i,0,n) {
			if (i && get<1>(tp[i]) == get<1>(tp[i-1]) && get<0>(tp[i]) == get<0>(tp[i-1]))
				q[get<2>(tp[i])][k] = r;
			else q[get<2>(tp[i])][k] = ++r;

			if (p[i][k-1] != -1) 
				p[i][k] = p[p[i][k-1]][k-1];
			else p[i][k] = -1;
		}
	}
	f(i,0,n) x[q[i][K-1]] = i;

	auto le = [&](int i, string s, int eq) {
		int j = 0;
		while (i != -1 && j < s.length()) {
			if (c[i] < s[j]) return 1;
			if (c[i] > s[j]) return 0;
			i = p[i][0]; j++;
		}
		if (j < s.length()) return 1;
		return eq;
	};

	stringstream ss;
	f(_,0,k) {
		string s; cin>>s;
		int pos[2];
		f(z,0,2) {
			int lo = 0, hi = n-1;
			while (lo <= hi) {
				int i = lo+hi>>1;
				if (le(x[i], s, z)) lo = i+1;
				else hi = i-1;
			}
			pos[z] = hi;
		}
		ss << pos[1]-pos[0] << endl;
	}
	cout << ss.str();

	return 0;
}
