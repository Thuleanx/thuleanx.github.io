#include <bits/stdc++.h>
using namespace std;

string name[] = {
	"JnS",
	"Load",
	"Store",
	"Add",
	"Subt",
	"Input",
	"Output",
	"Halt",
	"Skipcond",
	"Jump",
	"Clear",
	"AddI",
	"JumpI",
	"LoadI",
	"StoreI",
	"ERROR"
};
bool use[] = {
	1, 
	1, 
	1, 
	1, 
	1, 
	0, 
	0,
	0, 
	1,
	1, 
	0, 
	1, 
	1, 
	1, 
	1,
	1
};

int conv(char c) {
	if (c >= 'a') return c - 'a' + 10;
	return c - '0';
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int p = 0;
	string s;
	bool var = 0;
	while (cin>>s) {
		transform(begin(s),end(s),begin(s),[](unsigned char c){ return std::tolower(c); });
		int i = conv(s[0]);
		printf("%03x: ", p++);
		fflush(stdout);

		if (var) cout << "HEX " << s << endl;
		else {
			cout << name[i];
			if (use[i]) cout << " " << s.substr(1,s.length()-1);
			cout << endl;
		}
		if (i == 7) var = 1;
	}

	return 0;
}
