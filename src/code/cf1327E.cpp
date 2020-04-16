
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i>=a; i--)
#define IN(i,a,b) (a<=(i) && (i)<=b)
#define mp make_pair
#define mt make_tuple

const int mod = 998244353;

long long modpow(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b&1) res = res*a%mod;
		a = a*a%mod;
		b/=2;
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n; cin>>n;
	vector<long long> ans; ans.push_back(10);

	long long len = 10, num = 10;

	f(i,1,n) {
		len = (len + num)%mod;
		ans.push_back(((i+1)*modpow(10,i+1)%mod-len+mod)%mod);
		len = (len+ans.back())%mod;
		num = (num+ans.back())%mod;
	}

	reverse(begin(ans),end(ans));


	stringstream ss;
	f(i,0,n) ss << ans[i] << " \n"[i==n-1];
	cout << ss.str();


	return 0;
}
