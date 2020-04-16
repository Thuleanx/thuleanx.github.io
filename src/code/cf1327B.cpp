
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

	int t; cin>>t;
	stringstream ss;
	while (t--) {
		int n; cin>>n;
		vector<int> adj[n];
		f(i,0,n) {
			int g; cin>>g;
			while (g--) {
				int x; cin>>x;
				adj[i].push_back(--x);
			}
		}
		bool take[n], make[n];
		f(i,0,n) take[i] = 0, make[i] = 0;
		int cnt = 0;
		f(i,0,n) {
			sort(begin(adj[i]),end(adj[i]));
			for (int x : adj[i]) if (!take[x]) {
				take[x] = 1;
				make[i] = 1;
				cnt++;
				break;
			}
		}
		if (cnt == n) ss << "OPTIMAL" << endl;
		else {
			int per = -1, thing = -1;
			f(i,0,n) if (!take[i]) thing = i;
			f(i,0,n) if (!make[i]) per = i;
			ss << "IMPROVE" << endl;
			ss << per+1 << " " << thing+1 << endl;
		}
		
	}
	cout << ss.str();
		

	return 0;
}
