#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = b-1; i >= a; i--)
#define pb push_back
#define mp make_pair
#define mt make_tuple

const int N = 2000, oo = 1e9+7;
int n;
vector<int> adj[N];
// v,t,l,r
long long dp[N][2][2][2];

void add(long long &a, long long b) {
	a += b;
	if (a >= oo) a -= oo;
}

long long dfs(int v,int t,int l,int r);
long long val(int w, int t, int l, int r) {
	return t?dfs(w,0,l,r):(dfs(w,1,l,r)+dfs(w,0,l,r))%oo;
}

void init() {
	f(i,0,N) f(j,0,2) f(k,0,2) f(kk,0,2)
		dp[i][j][k][kk] = -1;
}

long long dfs(int v, int t, int l, int r) {
	if (dp[v][t][l][r] != -1) return dp[v][t][l][r];

	if (adj[v].size() == 0) {
		return dp[v][t][l][r] = l==r && (l == t);
	}

	for (int w : adj[v])
		f(tt,0,2) f(ll,0,2) f(rr,0,2) dfs(w,tt,ll,rr);

	int m = adj[v].size();
	long long dp2[m+1][2]; // edge, fi, ch
	f(i,0,m+1) f(k,0,2) dp2[i][k] = 0;
	dp2[0][r] = 1;
	
	f(i,0,m) f(k,0,2) if (dp2[i][k]) {
		int w = adj[v][i];
		if (i == 0) {
			// only two ways to prob
			add(dp2[i+1][1], dp2[i][k]*val(w,t,l,1)%oo);
			add(dp2[i+1][0], dp2[i][k]*val(w,t,l,0)%oo);
		} else {
			f(ll,0,2) f(rr,0,2) if (!(ll && k))
				add(dp2[i+1][rr], dp2[i][k]*val(w,t,ll,rr)%oo);
		}
	}
	if (dp2[m][r]) 
		cout << v << " " << t << " " << l << " " << r << " " << dp2[m][r] << endl;

	return dp[v][t][l][r] = dp2[m][r];
}

class RestrictedLeaves {
  public:
	int count(vector <int> parent) {
		n = parent.size();
		init();
		f(i,0,n) if (parent[i] != -1)
			adj[parent[i]].push_back(i);
		long long ans = 0;
		f(l,0,2) f(r,0,2) if (!(l&&r)) {
			f(t,0,2) add(ans, dfs(0,t,l,r));
		}
		cout << endl;
		return ans;
	}
};

// BEGIN CUT HERE
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
namespace moj_harness {
	using std::string;
	using std::vector;
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				std::cerr << "Illegal input! Test case " << casenum << " does not exist." << std::endl;
			}
			return;
		}
		
		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}
		
		if (total == 0) {
			std::cerr << "No test cases run." << std::endl;
		} else if (correct < total) {
			std::cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << std::endl;
		} else {
			std::cerr << "All " << total << " tests passed!" << std::endl;
		}
	}
	
	int verify_case(int casenum, const int &expected, const int &received, std::clock_t elapsed) { 
		std::cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}
		
		std::cerr << verdict;
		if (!info.empty()) {
			std::cerr << " (";
			for (size_t i=0; i<info.size(); ++i) {
				if (i > 0) std::cerr << ", ";
				std::cerr << info[i];
			}
			std::cerr << ")";
		}
		std::cerr << std::endl;
		
		if (verdict == "FAILED") {
			std::cerr << "    Expected: " << expected << std::endl; 
			std::cerr << "    Received: " << received << std::endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int parent[]              = {-1, 0, 0, 0, 0};
			int expected__            = 8;

			std::clock_t start__      = std::clock();
			int received__            = RestrictedLeaves().count(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int parent[]              = {-1, 0, 0, 1, 2, 1, 2};
			int expected__            = 21;

			std::clock_t start__      = std::clock();
			int received__            = RestrictedLeaves().count(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int parent[]              = {-1, 0, 0, 1, 2, 1, 2, 1, 4, 4};
			int expected__            = 75;

			std::clock_t start__      = std::clock();
			int received__            = RestrictedLeaves().count(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 3: {
			int parent[]              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = RestrictedLeaves().count(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 4: {
			int parent[]              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = RestrictedLeaves().count(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int parent[]              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = RestrictedLeaves().count(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}

#include <cstdlib>
int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(std::atoi(argv[i]));
	}
}
// END CUT HERE
