#include <bits/stdc++.h>
using namespace std;

const int N = 1e6, M = 1e7;
int n;
vector<int> p[N], pos[M];

void dfs(int l, int r, set<int> &avai, unordered_map<int,int> &ds) {
	int v = avai.top(); avai.pop();

	set<int> other;
	unordered_map<int,int> low;

	// remove v
	for (int pr : p[v])
		if (!--ds[pr])
			ds.erase(pr);

	// move thingies
	if (v-l <= r-v) {

	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n;


	return 0;
}
