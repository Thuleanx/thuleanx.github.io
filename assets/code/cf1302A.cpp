#include <bits/stdc++.h>
using namespace std;

const int oo = 1e9+7;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m; cin>>n>>m;
	int a[n][m];
	int mr[n], mc[m], cr[n], cc[m];
	for (int i =0 ;i < n; i++) mr[i] = oo, cr[i] = 0;
	for (int i = 0; i < m; i++) mc[i] =0 , cc[i] = 0;

	int bi = -1, bj = -1;
	for (int j = 0; j < m; j++) 
	for (int i = 0; i < n; i++) {
		cin>>a[i][j];

		if (a[i][j] == mr[i])
			cr[i]++;	
		else if (a[i][j] < mr[i])
			mr[i] = a[i][j], cr[i] = 1;

		if (a[i][j] == mc[j])
			cc[j]++;
		else if (a[i][j] > mc[j])
			mc[j] = a[i][j], cc[j] = 1;
	}


	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (((a[i][j] == mr[i] && cr[i] == 1) && (a[i][j] == mc[j] && cc[j] == 1)))
				bi = i, bj = j;
	cout << bj+1 << " " << bi+1 << endl;

	
	return 0;
}
