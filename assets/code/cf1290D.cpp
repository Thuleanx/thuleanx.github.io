#include <bits/stdc++.h>
using namespace std;

const int N = 1024;
int n,k,ans=0;
bool pres[N];

bool ask(int x) {
	cout << "? " << (x+1) << endl;
	fflush(stdout);
	string s; cin >> s;
	return s == "Y";
}

void reset() {
	cout << "R" << endl;
	fflush(stdout);
}

void declare(int x) {
	cout << "! " << x << endl;
	fflush(stdout);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>k;
	for (int i = 0; i < n/k; i++) {
		// uniques in a chunk
		for (int j = i*k; j < (i+1)*k; j++)
			pres[j] = !ask(j);
		reset();
	} 
	for (int i = 0; i < n/k; i++) {
		for (int j = i+1; j < n/k; j++) {
				
			int lsy = -1, num = 0;
			for (int y = j*k; y < (j+1)*k; y++) if (pres[y]) {
				ask(y);
				lsy = y;
				num++;
			}
			while (lsy != -1 && num++<k) ask(lsy); // pad by lsy
			int lsx = -1; num = 0;
			for (int x = i*k; x < (i+1)*k; x++) if (pres[x]) {
				pres[x] = !ask(x);
				lsx = x; // x got to compare itself with only last element in y. 
				num++;
			}
			if (lsx!=-1 && lsy!=-1) {
				while (num++<k+1) ask(lsy); // pad by lsy
				for (int y = j*k; y < (j+1)*k; y++) if (pres[y] && y != lsy)
					pres[y] = !ask(y);
			}
			reset();
		}
	}
	for (int i = 0; i < n; i++)
		ans += pres[i];

	declare(ans);

	return 0;
}
