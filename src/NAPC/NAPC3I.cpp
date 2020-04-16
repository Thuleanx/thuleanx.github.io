
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
using ld = long double;
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

const int N = 1000;
int n, q;
long double r[N][N];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n;
	f(i,0,n) {
		int x,y; cin>>x>>y;
		cin>>r[x][y];
	}

	stringstream ss;
	cin>>q;
	while (q--) {
		int x1, x2, y1, y2;
		cin>>x1>>y1>>x2>>y2;

		ld len = sqrt(ld(x2-x1)*(x2-x1)+ld(y2-y1)*(y2-y1));

		auto dist = [&](int x, int y) {
			ld dx = x-x1, dy = y-y1, dx2 = x2-x1, dy2 = y2-y1;
			return abs(dx * dy2 - dy * dx2) / len;
		};

		if (abs(y2 - y1) > abs(x2 - x1)) {
			if (y1 > y2) {
				swap(y1, y2);
				swap(x1, x2);
			}
			int cnt = 0;

			f(y,y1,y2+1) {
				ld x = (ld(y-y1)/(y2-y1))*(x2-x1)+x1;

				int xu = ceil(x);
				f(d,-4,5) if (xu+d >= 0 && dist(xu+d,y) < r[xu+d][y]) cnt++;
			}

			ss << cnt << endl;
		} else {
			if (x1 > x2) {
				swap(x1, x2);
				swap(y1, y2);
			}
			int cnt = 0;

			f(x,x1,x2+1) {
				ld y = (ld(x-x1) / (x2-x1)) * (y2-y1) + y1;
				int yu = ceil(y);
				f(d,-4,5) {
					if (yu + d >= 0 && dist(x,yu+d) < r[x][yu+d]) cnt++;
				}
			}
			ss << cnt << endl;
		}
	}
	cout << ss.str();

	return 0;
}
