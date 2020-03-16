#include <bits/stdc++.h>
using namespace std;

#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define f(i,a,b) for (int i = a; i < b; i++)
#define IN(i,a,b) (a<=i&&i<=b)

int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};


// d.m.y
bool valid(int i, int j, int k) {
	return IN(j,1,12) && IN(i,1,days[j-1]+(k%4==0&&j==2)) && IN(k,0,9999);
}

string tos(int i, int j, int k, bool toout=0) {
	char buffer[40];
	if (toout) sprintf(buffer, "%02d.%02d.%04d.", i,j,k);
	else sprintf(buffer, "%02d%02d%04d", i,j,k);
	return string(buffer);
}

bool palindromic(int i, int j, int k) {
	f(z,0,4) {
		int digit = 0, cdigit = 0;
		if (z == 0) digit = i/10, cdigit = k%10;
		if (z == 1) digit = i%10, cdigit = k/10%10;
		if (z == 2) digit = j/10, cdigit = k/100%10;
		if (z == 3) digit = j%10, cdigit = k/1000%10;
		if (digit != cdigit) return 0;
	}
	return 1;
}


tuple<int,int,int> parse(string s) {
	return make_tuple(stoi(s.substr(6,4)), stoi(s.substr(3,2)), stoi(s.substr(0,2)));
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	vector<tuple<int,int,int>> ls;
	f(y,0,10000) f(d,1,32) f(m,1,13)
		if (valid(d,m,y) && palindromic(d,m,y))
			ls.push_back(make_tuple(y,m,d));

	int t; cin>>t;
	while (t--) {
		string s; cin>>s;
		tuple<int,int,int> dat = parse(s);
		auto pp = upper_bound(ls.begin(),ls.end(),dat);		
		cout << tos(get<2>(*pp), get<1>(*pp), get<0>(*pp),1) << endl;
	}

	return 0;
}
