#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i>=a; i--)
#define IN(i,a,b) (a<=(i) && (i)<=b)
#define mp make_pair
#define mt make_tuple

int di[] = {1,-1,0,0};
int dj[] = {0,0,1,-1};
char dir[] = {'D','U','R','L'};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, k;			
	cin>>n>>m>>k;

	string s;
	f(i,0,n-1) s += 'U';
	f(i,0,m-1) s += 'L';
	// upper left corner now
	
	f(i,0,n) {
		if (i&1) {
			f(j,0,m-1) s += 'L';
		} else f(j,0,m-1) s += 'R';
		if (i != n-1) s += 'D'; 
	}
	cout << s.length() << endl;
	cout << s << endl;

	return 0;
}
