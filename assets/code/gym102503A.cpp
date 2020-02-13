#include <bits/stdc++.h>
using namespace std;

const int N = 4;
int a[N];
int h;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 0; i < N; i++)
		cin>>a[i];
	cin>>h;
	
	for (int i = 0; i < N; i++)
	for (int j = 0; j < N; j++)
	for (int k = 0; k < N; k++) if (i != j && j != k && i != k && a[i] + a[j] + a[k] >= h) {
		cout << "WAW" << endl;
		return 0;
	}
	cout << "AWW" << endl;



	return 0;
}
