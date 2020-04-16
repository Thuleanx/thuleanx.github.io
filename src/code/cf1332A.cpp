
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	stringstream ss;
	while (t--) {
		int a, b, c, d, x, y, x1, x2, y1, y2;
		cin>>a>>b>>c>>d>>x>>y>>x1>>y1>>x2>>y2;
		x1-=x; x2-=x; y1-=y; y2-=y;

		bool gd = 1;
		if (a-b) gd &= IN(b-a, x1, x2);
		else gd &= IN(0,x1+(a|b?1:0),x2) || IN(0,x1,x2-(a|b?1:0));

		if (c-d) gd &= IN(d-c, y1, y2);
		else gd &= IN(0,y1+(c|d?1:0), y2) || IN(0,y1,y2-(c|d?1:0));

		ss << (gd?"Yes":"No") << endl;	
	}
	cout << ss.str();

	return 0;
}
