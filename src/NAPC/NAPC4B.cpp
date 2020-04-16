
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple
#define sz(a) a.size()

using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi  = vector<int>;

const int oo = 1e9+7;
const ll ool = 1e18;

ll modpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b&1) res = res*a%oo;
		a = a*a%oo;
		b /=2;
	}
	return res;
}

const int N = 2e3+1;
int n;
int a[N], b[N];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;


	while (t--) {
		cin>>n;

		ll ans = 0;
		f(i,0,N) a[i] = 0;

		f(i,0,n) {
			int x; cin>>x;
			a[x]++;
		}
		f(i,1,N) b[i] += b[i-1]+a[i];

		f(i,1,N) if (a[i]) {
			if (i&1) {
				ans += a[i]*a[i];
				for (int j = i+2; j < N; j += i)
					ans += a[j]*a[i];
			} else {
				for (int j = i; j+i < N; j += 2*i) {
					ans += (b[j+i-1] - (i?b[j-1]:0)) * a[i];
					if (b[j+i-1] - (i?b[j-1]:0)) cout << "A " << i << " " << j+i-1 << " " << b[j+i-1] - (i?b[j-1]:0)<< endl;
				}
			}
			if (a[i]) cout << i << " " << ans << endl;
		}
		cout << ans << endl;
	}

	return 0;
}
