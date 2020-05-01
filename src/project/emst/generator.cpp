#include <bits/stdc++.h>
#include "poly.cpp" // This is where we set dimensional constraints
using namespace std;

const int N = 1e4;

#define f(i,a,b) for (int i = a; i < b; i++)
using ld = long double;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void gen(int n) {
	stringstream ss;
	ss << n << endl;
	f(i,0,n) f(j,0,DIM)
		ss << setprecision(20) << uniform_real_distribution<long double>(0, 1)(rng) << " \n"[j==DIM-1];
	cout << ss.str();
}

int main() {

	int n = 10;
	int i = 0;
	while (n <= N) {
		f(_,0,10) {
			string title = "input";
			title += to_string(i);
			title += ".txt";
			freopen(title.c_str(), "w", stdout);
			gen(n);
			fclose(stdout);
			i++;
		}
		n *= 10;
	}

	return 0;
}
