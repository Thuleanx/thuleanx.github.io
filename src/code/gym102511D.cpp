#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++) 
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)

const int N = 1e6;
int n;
int sum[N], a[N];
bool be[N];
vector<int> g[N];

void add(int i, int j) {
	sum[i]++; 
	if (j+1<N) sum[j+1]--;	
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n;
	f(i,0,n) {
		string s; cin>>s;
		be[i] = s[0] == 's';
		a[i] = stoi(s.substr(1,s.length()-1)) - 1;
		g[a[i]].push_back(i);
	}
	f(i,0,N) if (g[i].size()) {
		int sum = 0, lo = 0;
		for (int x : g[i]) {
			sum += be[x]?1:-1;
			lo = min(lo, sum);
		}
		if (sum) continue;
		f(j,0,g[i].size()) {
			sum += be[g[i][j]]?1:-1;
			if (sum == lo) {
				int jj = (j+1)%g[i].size();
				if (jj == 0) {
					add(g[i][j],n-1);
					add(0,g[i][jj]-1);
				} else add(g[i][j], g[i][jj]-1);
			}
		}
	}
	int m = 0, p = 0;
	f(i,0,n) {
		if (i) sum[i] += sum[i-1];
		if (sum[i] > m) {
			m = sum[i];
			p = i;
		}
	}
	if (sum[n-1] == m)
		p = n-1;
	cout << 1+(p+1)%n << " " << m << endl;

	return 0;
}
