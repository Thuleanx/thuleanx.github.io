
#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple
#define sz(a) a.size()

using ld = long double;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi  = vector<int>;

const int oo = 1e9+7;
const ll loo = 1e18;

ll modpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b&1) res = res*a%oo;
		a = a*a%oo;
		b /=2;
	}
	return res;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// use uniform_int_distribution<int>(0, i)(rng)

const int N = 101;
int n;
vector<ll> cx, cy;
vector<int> r;
int a[N], b[N];

void read(int i) {
	cout << "+ " << i +1 << endl;
	r.push_back(i);
	fflush(stdout);
	ll x,y;cin>>x>>y;
	cx.push_back(x); cx.push_back(y);
}

int solve() {
	cin>>n;

	int x,y; cin>>x>>y;
	cx.push_back(x); cy.push_back(y);
	
	f(i,0,n) a[i] = 0, b[i] = -1;

	f(i,0,n) read(i);

	vector<ll> cnt(n);
	if (cx.back() == 0) {
		fr(i,0,n-1) if (b[i+1] == -1) {
			if (cy[i+1]-cy[i] == 0)
				b[i+1] = 0;
			else if (cy[i+1]-cy[i] == 1)
				b[i+1] = 1, b[i+2] = 0;
			else if (cy[i+1]-cy[i] == 2) 
				b[i+1] = 1, b[i+2] = 1;
		}
	}
	f(i,0,n) cout << cnt[i] << " ";

	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	solve();

	return 0;
}
