
#include <bits/stdc++.h>
using namespace std;

#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define f(i,a,b) for (int i = a; i < b; i++)
#define IN(i,a,b) (a<=i&&i<=b)

const int N = 50, K = 1500, oo = 1e9+7, R = 26;
int n, k;
map<string,vector<int>> id;
vector<string> box[N];
long long dp[N][K];
bool same[N][K];

struct Node {
	Node* nxt[R];
	vector<int> idx;
};

Node* root;

void init() {
	root = new Node();
}

void add(long long &a, long long b) {
	a += b;
	if (a >= oo) a-=oo;
}

void insert_string(string &s, int i) {
	Node* cur = root;
	for (char c : s) {
		if (!cur->nxt[c-'a'])
			cur->nxt[c-'a'] = new Node();
		cur = cur->nxt[c-'a'];
	}
	cur->idx.push_back(i);
}

Node* find_node(Node* cur, string &s) {
	if (cur == 0) return 0;
	for (char c : s) {
		if (!cur->nxt[c-'a'])
			return 0;
		cur = cur->nxt[c-'a'];
	}
	return cur;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	clock_t start = clock();
	cin>>n>>k;
	init();

	f(i,0,n) {
		f(j,0,k) {
			string s; cin>>s;
			while (s.length() < i+1) s += 'a';
			same[i][j] = 1;
			f(i,1,s.length()) if (s[i] != s[i-1]) same[i][j] = 0;
			box[i].push_back(s);
			insert_string(s,j);
		}
	}

	long long ans = 0;
	fr(i,0,n) {
		f(j,0,k) {
			if (i == n-1) dp[i][j] = 1;
			else {
				dp[i][j] = 0;
				f(c,'a','z'+1) {
					Node* cur = root;
					cur = find_node(cur->nxt[c-'a'], box[i][j]);
					if (cur) for (int kk : cur->idx) 
							add(dp[i][j], dp[i+1][kk]);
					if (!(same[i][j] && c == box[i][j][0])) {
						cur = root;
						cur = find_node(cur, box[i][j]);
						cur = cur->nxt[c-'a'];
						if (cur) for (int kk : cur->idx) 
							add(dp[i][j], dp[i+1][kk]);
					}
				}
			}
			if (!i) add(ans, dp[i][j]);
		}
	}
	cout << ans << endl;


	return 0;
}
