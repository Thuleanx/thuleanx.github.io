
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

	int k; cin>>k;

	int oo = (1<<18)-1;

	int a[3][3];
	a[0][0] = oo;
	a[0][1] = a[1][0] = oo;
	a[1][1] = (1<<17);
	a[0][2] = a[2][0] = k; // score you want
	a[2][1] = a[1][2] = oo;
	a[2][2] = oo - (1<<17); 

	cout << 3 << " " << 3 << endl;
	f(i,0,3) f(j,0,3) cout << a[i][j] << " \n"[j==2];

	return 0;
}
