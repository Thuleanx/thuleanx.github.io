#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i>=a; i--)
#define IN(i,a,b) (a<=(i) && (i)<=b)
#define mp make_pair
#define mt make_tuple

const int N = 3e5+7, mod = 998244353;
int n;
int a[N], cnt[N], nxt[N];
long long toadd[N], dp[N];

struct TwoHeap {
	priority_queue<int> a,b;
	int sz = 0;
	void add(int x) {
		resolve();
		a.push(x);
		sz++;
	}
	void rem(int x) {
		b.push(x);
		resolve();
		sz--;
	}
	void resolve() {
		while (a.size() && b.size() && a.top() == b.top()) {
			a.pop();
			b.pop();
		}
	}
	int get() {
		resolve();
		return a.top();
	}
};

void add(long long &a, long long b) {
	a += b;
	if (a >= mod) a-=mod;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	stringstream ss;
	while (t--) {
		cin>>n;
		f(i,0,n) cin>>a[i];
		f(i,0,n) cnt[a[i]]++;
		f(i,0,n+1) toadd[i] = 0, dp[i] = 0;

		int x = 0;
		while (cnt[x]) x++;

		unordered_map<int,int> nxte;
		TwoHeap ds;
		fr(i,0,n) {
			if (a[i] < x) {
				if (nxte.count(a[i])) 
					ds.rem(nxte[a[i]]);
				nxte[a[i]] = i;
				ds.add(i);
			}
			if (nxte.size() == x)
				nxt[i] = x ? ds.get() : i;	
			else nxt[i] = -1;
		}

		dp[0] = 1;
		long long sum = 0;
		f(i,0,n+1) {
			add(sum, toadd[i]);
			add(dp[i], sum);
			if (nxt[i] != -1)
				add(toadd[nxt[i]+1], dp[i]);
		}
		ss << dp[n] << endl;

		f(i,0,n) cnt[a[i]]--;
	}
	cout << ss.str();

	return 0;
}
