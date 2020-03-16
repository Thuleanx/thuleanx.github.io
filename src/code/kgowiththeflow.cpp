#include <bits/stdc++.h>
using namespace std;

const int N = 2500;
int n;
string text;
int di[] = {1,0,-1};

#define mp make_pair
#define f(i,a,b) for (int i = a; i < b; i++)

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n;
	stringstream ss;

	int lo = 1;
	f(i,0,n) {
		string s; cin>>s;
		lo = max(lo, int(s.length()));
		ss << s;
		if (i != n-1) ss << " ";
	}
	text = ss.str();

	pair<int,int> ans;

	cout << lo << endl;

	f(d,lo,2500) { // O(d)
		int i = 0;
		unordered_map<int,int> res;
		while (i < text.length()) {
			while (i < text.length() && text[i] == ' ') i++;
			if (i == text.length()) break;
			unordered_map<int,int> layer;
			int j = i+d-1;
			while (j < text.length() || text[j] != ' ') j--;
			f(k,0,j-i) if (text[k] == ' ') {
				layer[k] = (res.count(k)?res[k]+1:1);
				if (k && res.count(k-1)) layer[k] = max(layer[k], res[k-1]+1);
				if (k < d-1 && res.count(k+1)) layer[k] = max(layer[k], res[k+1]+1);
				ans = max(ans, mp(layer[k], d));
			}
			res = layer;
			i = j+1;
		}
	}

	cout << ans.second << " " << ans.first << endl;


	return 0;
}
