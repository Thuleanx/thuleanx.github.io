#include <bits/stdc++.h>
using namespace std;

const long long M = 1LL<<40;
const long long S = 1611516670, K = 12345;

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n; cin>>n;

	long long cur = S;
	int times = 0;
	int cnt = 0;
	while (n--) {
		if (!(times++%74)) cout << endl;
		if (cur&1) cout << RED << 1;
		else cout << WHITE << 0;
		cur = (cur + (cur>>20) + K) & (M-1);
	}
	cout << cnt << endl;

	return 0;
}

