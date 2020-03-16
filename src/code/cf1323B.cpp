#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)

const int K = 25, N = 4e5, M = 2e7+8;
int n;
int a[N];

struct BIT {
	int times = 0;
	bitset<M> cnt;	
	void add(int i) {
		times^=1;
		for (; i < M; i |= i+1)
			cnt.flip(i);
	}
	int sum(int i) {
		int res = 0;
		for (; i >= 0; i = (i&(i+1))-1)
			res ^= cnt[i];
		return res;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);


	cin>>n;
	f(i,0,n) cin>>a[i];
	long long ans = 0;
	long long cnt[2] = {0,0};
	f(i,0,n) cnt[a[i]&1]++;
	if ((1LL*cnt[0]*cnt[1])&1) ans++;

	f(k,1,K) {
		BIT ds[2];
		fr(i,0,n) {
			int begi = a[i]&((1<<k)-1); 
			f(j,0,2) {
				if ((a[i]>>k&1) != j) {
					if (ds[j].sum((1<<k) - begi - 1)) 
						ans ^= 1<<k;
				} else {
					if (ds[j].sum((1<<k)- begi - 1) ^ ds[j].times)
						ans ^= 1<<k;
				}
			}

			ds[a[i]>>k&1].add(begi);
		}
	}
	cout << ans << endl;

	return 0;
}
