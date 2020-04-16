
#include <bits/stdc++.h>
using namespace std;

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

#define x(a) get<0>(a)
#define y(a) get<1>(a)
#define w(a) get<2>(a)
#define h(a) get<3>(a)

using box = tuple<int,int,int,int,int>;
vector<box> wins;

int X, Y;

bool sect(int x11, int x12, int x21, int x22) {
	f(z,0,2) {
		if (IN(x11, x21, x22-1) || IN(x12-1, x21, x22-1)) return 1;
		swap(x11,x21); swap(x12, x22);
	}
	return 0;
}

bool intersect(box a, box b) {
	return	sect(x(a), x(a)+w(a), x(b), x(b)+w(b)) && 
			sect(y(a), y(a)+h(a), y(b), y(b)+h(b));
}

void refXY() {
	for (box &a : wins) {
		swap(x(a), y(a));
		swap(w(a), h(a));
	}
	swap(X, Y);
}

void refX() {
	for (box &a : wins) {
		int l = X-1 - (x(a)+w(a)-1);
		x(a) = l;
	}
}

box get_window(int a, int b) {
	box rem = mt(-1,-1,-1,-1,-1);
	for (box c : wins)
		if (IN(a,x(c),x(c)+w(c)-1) && IN(b,y(c),y(c)+h(c)-1))
			rem = c;
	return rem;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>X>>Y;
	string s;

	int p = 0;
	while (getline(cin,s)) {
		stringstream ss(s); ss >> s;

		if (s == "OPEN") {
			box a; ss>>x(a)>>y(a)>>w(a)>>h(a);
			get<4>(a) = p;
			int cnt = 0;
			for (box b : wins)
				cnt += intersect(a,b);
			if (!cnt) wins.push_back(a);
			else cout << "Command " << p << ": OPEN - window does not fit" << endl; 

		} else if (s == "CLOSE") {
			int a, b; ss>>a>>b;

			box rem = get_window(a,b);
			if (x(rem) == -1) cout << "Command " << p << ": CLOSE - no window at given position" << endl; 
			else wins.erase(find(wins.begin(), wins.end(), rem));


		} else if (s == "RESIZE") {
			
			int a, b, c, d; ss>>a>>b>>c>>d;

			box rem = get_window(a,b);
			if (x(rem) == -1) cout << "Command " << p << ": RESIZE - no window at given position" << endl; 
			else {
				int cnt = 0;
				box nelp = rem;
				w(rem) = c; h(rem) = d;
				for (box b : wins) cnt += intersect(rem, b);
				if (cnt > 1 || x(rem)+w(rem) > X || y(rem)+h(rem)>Y) {
					cout << "Command " << p << ": RESIZE - window does not fit" << endl;
				} else {
					wins.erase(find(wins.begin(), wins.end(), nelp));
					wins.push_back(rem);
				}
			}

		} else if (s == "MOVE") {

			int a, b, c, d; ss>>a>>b>>c>>d;
			// assume w > 0. if not we perform stuff on the board
			
			box rem = get_window(a,b);

			if (x(rem) == -1) cout << "Command " << p << ": MOVE - no window at given position" << endl; 
			else {
				int z = c?c:d; 

				wins.push_back(rem);
				if (d) refXY(); 
				if (z<0) refX();
				rem = wins.back(); wins.pop_back();

				sort(begin(wins),end(wins),[&](box a, box b) {
					return x(a) < x(b);
				});

				int n = wins.size();
				vector<box> nelp(n);
				fr(i,0,n) {
					int l = X;
					f(j,i,n) if (sect( y(nelp[i]), y(nelp[i])+h(nelp[i]), y(nelp[j]), y(nelp[j]) + h(nelp[j])))
						l = min(l, x(nelp[j]));
					nelp[i] = wins[i];
					x(nelp[i]) = l - w(nelp[i]);
				}


				int dd = -1;
				f(i,0,n) {
					int r = 0;
					f(j,0,i) if (sect( y(nelp[i]), y(nelp[i])+h(nelp[i]), y(nelp[j]), y(nelp[j]) + h(nelp[j])))
						r = max(r, x(nelp[j]) + w(nelp[j]));

					if (rem != wins[i]) r = max(r, x(wins[i]));
					else r = max(r, x(wins[i]) + abs(z));

					x(nelp[i]) = min(x(nelp[i]), r);
					assert(x(nelp[i]) + w(nelp[i]) <= X);

					if (wins[i] == rem)
						dd = x(nelp[i]) - x(wins[i]);
				}

				wins = nelp;

				if (dd != abs(z)) cout << "Command " << p << ": MOVE - moved " << dd << " instead of " << abs(z) << endl;

				if (z<0) refX();
				if (d) refXY(); 
			}
		}
		p++;
	}
	cout << wins.size() << " window(s):" << endl; 
	sort(begin(wins),end(wins),[&](box a, box b) {
		return get<4>(a) < get<4>(b);
	});
	for (box a : wins)
		cout << x(a) << " " << y(a) << " " << w(a) << " " << h(a) << endl;


	return 0;
}
