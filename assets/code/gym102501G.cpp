#include <bits/stdc++.h>
using namespace std;

const int S = 201, N = 1e5;
int s,n,l;
string rev[S];
bool able[S][S];
long double whereat[S];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	map<string,int> nmap;
	cin>>s>>l>>n;

	for (int i = 0; i < s; i++) 
		cin>>rev[i];

	sort(rev, rev+s);

	for (int i = 0; i < s; i++)
		nmap[rev[i]] = i;

	for (int i = 0; i < l; i++) {
		string a, b; cin>>a>>b;
		int v = nmap[a], w = nmap[b];
		if (v > w) swap(v,w);
		able[v][w] = 1;
	}

	set<long double> sset;
	sset.insert(0); sset.insert(1);

	vector<pair<long double, int>> sol;

	for (int i = 0; i < n; i++) {
		string arr; cin>>arr;
		int j = nmap[arr];

		int ls = -1;
		for (int z = 0; z < s; z++)
			if (!able[j][z] && (ls == -1 || whereat[ls] < whereat[z]))
				ls = z;
		if (sset.upper_bound(whereat[ls]) == sset.end()) {
			cout << whereat[ls] << endl;
			return 0;
		}
		long double nxt = (*sset.upper_bound(whereat[ls]) + whereat[ls]) / 2;
		cout << j << " " << ls << " " << whereat[ls] << " " << nxt << endl;
		sset.insert(nxt);
		sol.push_back( make_pair(nxt, j) );

		whereat[j] = nxt;
	}

	sort(begin(sol),end(sol));
	stringstream ss;
	for (auto pp : sol)
		ss << rev[pp.second] << " ";
	cout << ss.str() << endl;


	return 0;
}
