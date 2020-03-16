#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = b-1; i >= a; i--)
#define pb push_back
#define mp make_pair
#define mt make_tuple

int gcd(int a, int b) { 
	return a?gcd(b%a, a):b;
}

struct NonSimilarTriangles {
	int count(vector <int> a) {
		int n = a.size();
		sort(begin(a),end(a));
		map<tuple<int,int,int>, int> ds;
		f(i,0,n) f(j,i+1,n) f(k,j+1,n) if (a[k] < a[i] + a[j]) {
			int g = gcd(gcd(a[i],a[j]), a[k]); 
			tuple<int,int,int> tp = mt(a[i]/g, a[j]/g, a[k]/g);
			ds[tp]++;
		}
		return ds.size();
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
			int L[]                   = {3,4,5};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = NonSimilarTriangles().count(vector <int>(L, L + (sizeof L / sizeof L[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int L[]                   = {1,1,1,1,1,1};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = NonSimilarTriangles().count(vector <int>(L, L + (sizeof L / sizeof L[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int L[]                   = {2,2,2,3,3,3};
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = NonSimilarTriangles().count(vector <int>(L, L + (sizeof L / sizeof L[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int L[]                   = {1,2,4,8,16,24};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = NonSimilarTriangles().count(vector <int>(L, L + (sizeof L / sizeof L[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int L[]                   = {10,3,10,4,10,5,10,6,10,7,10,8,10,9};
			int expected__            = 50;

			std::clock_t start__      = std::clock();
			int received__            = NonSimilarTriangles().count(vector <int>(L, L + (sizeof L / sizeof L[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int L[]                   = {5, 5, 10};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = NonSimilarTriangles().count(vector <int>(L, L + (sizeof L / sizeof L[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int L[]                   = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = NonSimilarTriangles().count(vector <int>(L, L + (sizeof L / sizeof L[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int L[]                   = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = NonSimilarTriangles().count(vector <int>(L, L + (sizeof L / sizeof L[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int L[]                   = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = NonSimilarTriangles().count(vector <int>(L, L + (sizeof L / sizeof L[0])));
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
