
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

using ld = long double;
using point = complex<ld>;
#define x real()
#define y imag()

ld cross(point a, point b ) { return (conj(a)*b).y; }
ld dot(point a, point b) { return (conj(a)*b).x; }
ld len(point a) { return sqrt(ld(dot(a,a))); }
ld orient(point a, point b, point c) { return cross(b-a,c-a); }

bool inDist(point a, point b, point p) {
	return dot(a-p, b-p) <= 0;
}
bool on_segment(point a, point b, point p) {
	return orient(a,b,p) == 0 && inDist(a,b,p);
}
bool proper_inter(point a, point b, point c, point d) {
	ld oa = orient(c,d,a), ob = orient(c,d,b), oc = orient(a,b,c), od = orient(a,b,d);	

	if (oa*ob < 0 && oc*od < 0)
		return 1;
	return on_segment(a,b,c) || on_segment(a,b,d) || on_segment(c,d,a) || on_segment(c,d,b);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	stringstream ss;
	while (t--) {
		int n; cin>>n;
		point p[n], q[n];
		f(i,0,n) {
			int a,b; cin>>a>>b;
			p[i] = point(a,b);
		}
		f(i,0,n) {
			int a,b; cin>>a>>b;
			q[i] = point(a,b);
		}

		int perm[n];
		f(i,0,n) perm[i] = i;
		do {
			bool gd = 1;
			f(i,0,n) f(j,0,n) if (i != j && proper_inter(p[i], q[perm[i]], p[j], q[perm[j]]))
				gd = 0;
			if (gd) break;
		} while (next_permutation(perm, perm+n));

		f(i,0,n) {
			ss << 2 << endl;
			ss << p[i].x << " " << p[i].y << endl;
			ss << q[perm[i]].x << " " << q[perm[i]].y << endl;
		}
	}
	cout << ss.str();

	return 0;
}
