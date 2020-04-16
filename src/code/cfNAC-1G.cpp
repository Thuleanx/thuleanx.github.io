
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i>=a; i--)
#define IN(i,a,b) (a<=(i) && (i)<=b)
#define mp make_pair
#define mt make_tuple

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string ss, rr; cin>>ss>>rr;
	int n = ss.length();
	int s[n], r[n];
	{
		f(i,0,n) s[i] = ss[i]-'0';
		f(i,0,n) r[i] = rr[i]-'0';
	}
	{
		int cnt = 0;
		f(i,0,n) cnt += s[i] != r[i];
		if (!cnt) {
			cout << 0 << endl;
			return 0;
		}
	}

	vector<int> a, b;

	int x = 0;
	while (1) {
		int cnt = 0;
		f(i,0,n) cnt += s[i] != s[n-1];
		if (n % 2 == 0 && cnt == n-1) break;
		if (!cnt) break;

		f(i,0,n) if (s[i] == s[(i+1)%n] && s[i] == x) {
			a.push_back(i);
			s[i] ^= 1; s[(i+1)%n] ^= 1; 
		}
		x ^= 1;
	}
	while (1) {
		int cnt = 0;
		f(i,0,n) cnt += r[i] != r[n-1];
		if (n % 2 == 0 && cnt == n-1) break;
		if (!cnt) break;

		f(i,0,n) if (r[i] == r[(i+1)%n] && r[i] == x) {
			b.push_back(i);
			r[i]^=1; r[(i+1)%n] ^= 1;
		}
		x ^= 1;
	}
	
	f(i,0,n) if (s[i] != r[i]) {
		f(j,0,n) a.push_back(j++);
		break;
	}

	stringstream ssr;

	ssr << a.size() + b.size() << endl; 
	for (int y : a) ssr << y << endl;

	reverse(begin(b),end(b));
	for (int y : b) ssr << y << endl;

	cout << ssr.str();

	return 0;
}
