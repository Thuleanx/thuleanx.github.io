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

int n;
vector<string> program;
vector<string> compiled;
vector<string> expand;

string create(int v) {
	string s = ""; 
	{
		char buffer[10000];
		sprintf(buffer, "%03x: ", p++);
		s = buffer;

	}
	int i = conv(program[v][0]);
	s += name[i];
	if (use[i]) {
		s += " ";
		s += program[v].substr(1);
	}
	return s;
}

void dfs(int v) {
	for (int w = v; w < n; w++) {
		int i = conv(s[0]);

		printf("%03x: ", p++);
		fflush(stdout);
		
		cout << name[i];
		if (use[i]) cout << " " << s.substr(1,s.length()-1);
		cout << endl;
	}
	cout << endl;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string s;
	while (cin>>s)
		program.push_back(s);
	n = s.size();
	compiled = vector<bool>(n,0);

	dfs(0);


	return 0;
}
