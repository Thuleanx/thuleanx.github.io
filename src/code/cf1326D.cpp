
#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i>=a; i--)
#define IN(i,a,b) (a<=i&&i<=b)
#define mp make_pair
#define mt make_tuple
#define sz(a) (int)(a.size())

using vi = vector<int>;

// p[i][0] -> half length of palindrome centered at i
// p[i][0] -> half length of palindrome centered at i rounded down
array<vi, 2> manacher(const string &s) {
	int n = s.length();
	array<vi, 2> p = {vi(n+1), vi(n)};
	f(z,0,2) for (int i=0,r=0,l=0; i < n; i++) {
		int t = r-i+!z;
		if (i<r) p[z][i] = min(t, p[z][l+t]);
		int L = i-p[z][i], R = i+p[z][i]-!z;
		while (L>=1 && R+1<n && s[L-1] == s[R+1])
			p[z][i]++, L--, R++;
		if (R>r) l=L, r=R;
	}
	return p;
}

string solve(const string &s) {
	int n=s.length(), i = 0;
	while (i+1 <= n-1-(i+1) && s[i] == s[n-1-i])
		i++;
	assert(i <= n-1-i);
	array<vi, 2> p = manacher(s.substr(i, n-2*i));
	int lt = 0, rt = 0;
	f(j,0,sz(p[1])) {
		if (j == p[1][j]) lt = max(lt, p[1][j]<<1|1);
		if (sz(p[1])-1-j == p[1][j]) rt = max(rt, p[1][j]<<1|1);

		if (j == p[0][j]) lt = max(lt, p[0][j]<<1);
		if (sz(p[1])-j == p[0][j]) rt = max(rt, p[0][j]<<1);
	}
	return lt < rt ? s.substr(0,i) + s.substr(n-i-rt, rt+i) : 
		s.substr(0, i+lt) + s.substr(n-i,i);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin>>t;
	stringstream ss;
	while (t--) {
		string s; cin>>s;
		ss << solve(s) << endl;
	}
	cout << ss.str();


	return 0;
}
