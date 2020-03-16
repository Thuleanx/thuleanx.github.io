#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = b-1; i >= a; i--)
#define pb push_back
#define mp make_pair
#define mt make_tuple

const int oo = 1e9+7;

class Prominence {
  public:
	long long sumOfProminences(int N, vector <int> coef, vector <int> idx, vector <int> val) {
		vector<int> H(N);		
		f(i,0,N) {
			long long a = coef[3*(i&1)], b = coef[3*(i&1)+1], c = coef[3*(i&1)+2];
			H[i] = (((a*i+b) % oo)*i + c)%oo;
		}
		f(j,0,idx.size())
			H[ idx[j]] = val[j];

		vector<pair<int,int>> sol;
		long long ans = 0;

		int res[N];
		f(i,0,N) res[i] = 0;
		f(k,0,2) {
			sol.clear();
			f(i,0,N) {
				pair<int,int> part = mp(H[i],H[i]);
				while (sol.size() && sol.back().first <= H[i]) {
					part = mp(H[i], min(part.second, sol.back().second));
					sol.pop_back();
				}
				if (!sol.size())
					part = mp(part.first, 0);
				res[i] = max(res[i], part.second);
				sol.push_back(part);
			}
			reverse(res,res+N);
			reverse(begin(H),end(H));
		}
		f(i,0,N) {
			if (i<N-1 && H[i] <= H[i+1]) continue;
			if (i && H[i] <= H[i-1]) continue;
			ans += H[i]-res[i];
		}
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
	
	int verify_case(int casenum, const long long &expected, const long long &received, std::clock_t elapsed) { 
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
			int N                     = 7;
			int coef[]                = {0, 0, 47, 0, 0, 47};
			int idx[]                 = {};
			int val[]                 = {};
			long long expected__      = 0;

			std::clock_t start__      = std::clock();
			long long received__      = Prominence().sumOfProminences(N, vector <int>(coef, coef + (sizeof coef / sizeof coef[0])), vector <int>(idx, idx + (sizeof idx / sizeof idx[0])), vector <int>(val, val + (sizeof val / sizeof val[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 8;
			int coef[]                = {0, 0, 47, 0, 0, 42};
			int idx[]                 = {};
			int val[]                 = {};
			long long expected__      = 188;

			std::clock_t start__      = std::clock();
			long long received__      = Prominence().sumOfProminences(N, vector <int>(coef, coef + (sizeof coef / sizeof coef[0])), vector <int>(idx, idx + (sizeof idx / sizeof idx[0])), vector <int>(val, val + (sizeof val / sizeof val[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 10;
			int coef[]                = {0, 0, 0, 0, 0, 0};
			int idx[]                 = {0, 1, 2, 3, 4, 5, 6, 7, 9, 8};
			int val[]                 = {500, 300, 400, 200, 400, 700, 100, 300, 300, 100};
			long long expected__      = 1500;

			std::clock_t start__      = std::clock();
			long long received__      = Prominence().sumOfProminences(N, vector <int>(coef, coef + (sizeof coef / sizeof coef[0])), vector <int>(idx, idx + (sizeof idx / sizeof idx[0])), vector <int>(val, val + (sizeof val / sizeof val[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 16;
			int coef[]                = {123456789, 234567890, 345678901, 456789012, 567890123, 678901234};
			int idx[]                 = {7};
			int val[]                 = {890123456};
			long long expected__      = 4543586810LL;

			std::clock_t start__      = std::clock();
			long long received__      = Prominence().sumOfProminences(N, vector <int>(coef, coef + (sizeof coef / sizeof coef[0])), vector <int>(idx, idx + (sizeof idx / sizeof idx[0])), vector <int>(val, val + (sizeof val / sizeof val[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int N                     = ;
			int coef[]                = ;
			int idx[]                 = ;
			int val[]                 = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = Prominence().sumOfProminences(N, vector <int>(coef, coef + (sizeof coef / sizeof coef[0])), vector <int>(idx, idx + (sizeof idx / sizeof idx[0])), vector <int>(val, val + (sizeof val / sizeof val[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int N                     = ;
			int coef[]                = ;
			int idx[]                 = ;
			int val[]                 = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = Prominence().sumOfProminences(N, vector <int>(coef, coef + (sizeof coef / sizeof coef[0])), vector <int>(idx, idx + (sizeof idx / sizeof idx[0])), vector <int>(val, val + (sizeof val / sizeof val[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int N                     = ;
			int coef[]                = ;
			int idx[]                 = ;
			int val[]                 = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = Prominence().sumOfProminences(N, vector <int>(coef, coef + (sizeof coef / sizeof coef[0])), vector <int>(idx, idx + (sizeof idx / sizeof idx[0])), vector <int>(val, val + (sizeof val / sizeof val[0])));
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
