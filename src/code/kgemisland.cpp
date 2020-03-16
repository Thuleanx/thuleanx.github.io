#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define f(i,a,b) for (int i = a; i < b; i++)

const int N = 501; 
int n, d, r;
long double p[2][N][N], ff[2][N][N];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>d>>r;

	int cur = 0;

	f(i,0,2)f(j,0,N)f(k,0,N) p[i][j][k] = ff[i][j][k] = 0;
	p[0][0][0] = 1;
		
	f(i,0,n) {
		int nxt = cur^1;
		f(s,0,d+1) f(l,0,d+1) {
			if (s >= l) p[nxt][s][l] = p[cur][s - l][l];
			if (s >= l) ff[nxt][s][l] = ff[cur][s - l][l];
			if (n-i <= r)
				ff[nxt][s][l] += l*p[nxt][s][l];
			if (l) {
				p[nxt][s][l] += p[nxt][s][l-1];
				ff[nxt][s][l] += ff[nxt][s][l-1];
			}
			cout << i+1 << " " << s << " " << l << " " << p[nxt][s][l] << " " << ff[nxt][s][l] << endl;
		}
		f(j,0,N) f(k,0,N) p[cur][i][j] = ff[cur][i][j] = 0;
		cur = nxt;
	}

	long double ans = 0;
	f(k,0,d+1) ans += ff[cur][d][k];


	
	cout << setprecision(40) << ans + r << endl;

	return 0;
}
