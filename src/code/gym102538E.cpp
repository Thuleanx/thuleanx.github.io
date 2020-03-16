#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define popcount __builtin_popcountll

const int N = 5e5+7, K = 20;
int n;
int a[N], ff[N], res[N];

int sum(int i, int j) {
	i = max(i,1); j = min(j,N-1);
	if (i <= j) return a[j]-a[i-1];
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n;
	f(i,0,n) {
		int x; cin>>x;
		a[x] ^= 1;
	}
	f(i,1,N) a[i] += a[i-1];

	stringstream ss;
	for (int j = 1; j <= n; j <<= 1) {
		fr(i,0,n+1) ff[i] = (i+2*j <= n ? ff[i+2*j] : 0) + sum(i+j, i+2*j-1);
		f(y,j,n+2) {
			int bloc = (y+2*j-1)/(2*j)*(2*j), 
				take = min(bloc-y, j);
			int cnt = 0;
			for (int lt = 0; lt <= n; lt += y) {
				cnt += ff[lt];	
				if (lt + bloc < N) cnt -= ff[lt+bloc];
				cnt -= sum(lt+bloc-take, lt+bloc-1);
			}
			if (cnt%2) res[y] = 1;
		}
	}
	f(y,2,n+2) ss << (res[y]?"Alice":"Bob") << " \n"[y==n+1];
	cout << ss.str();

	return 0;
}
