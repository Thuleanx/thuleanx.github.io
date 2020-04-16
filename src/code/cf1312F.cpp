#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for (int i = a; i < b; i++)
#define fr(i,a,b) for (int i = (b)-1; i>=a; i--)
#define IN(i,a,b) (a<=(i) && (i)<=b)
#define mp make_pair
#define mt make_tuple

const int NN = 1000, N = 1e4, D = 5;
int n, x, y, z;
int grundy[D][D][D][N][3];
int p[D][D][D][3];

vector<int> z_function(vector<int> s) {
    int n = (int) s.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}


int find_period(vector<int> &s) {
	vector<int> pi = z_function(s);	
	// border = n - period
	f(i,0,pi.size()) {
		if (i + pi[i] == pi.size()) {
			// possible border of p[i]
			// period of p[i] maybe take shortest period
			return pi.size() - pi[i];
		}
	}
	return -1;
}

int gez(long long i, int j) {
	return i > NN ? grundy[x][y][z][ (i - NN)%p[x][y][z][j] + NN ][j] : grundy[x][y][z][i][j];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	f(x,0,D) f(y,0,D) f(z,0,D) {
		f(j,0,3) grundy[x][y][z][0][j] = 0;

		f(i,1,N) f(j,0,3) {
			bool pres[5];
			f(i,0,5) pres[i] = 0;
			pres[grundy[x][y][z][max(0, i - x - 1)][0]] = 1;
			if (j != 1) pres[grundy[x][y][z][max(0, i - y - 1)][1]] = 1;
			if (j != 2) pres[grundy[x][y][z][max(0, i - z - 1)][2]] = 1;

			grundy[x][y][z][i][j] = 0;
			while (pres[grundy[x][y][z][i][j]]) 
				grundy[x][y][z][i][j]++;
		}
		
		f(j,0,3) {
			vector<int> s(N-NN);
			f(i,NN,N) s[i-NN] = grundy[x][y][z][i][j];
			p[x][y][z][j] = find_period(s);
		}
	}


	int t; cin>>t;
	stringstream ss;
	while (t--) {
		cin>>n>>x>>y>>z; x--; y--; z--;

		long long a[n];
		f(i,0,n) cin>>a[i];

		int res = 0;
		f(i,0,n) res ^= gez(a[i], 0);

		int cnt = 0;
		f(i,0,n) {
			cnt += res == (gez(a[i],0) ^ gez(max(0LL, a[i] - x - 1), 0));
			cnt += res == (gez(a[i],0) ^ gez(max(0LL, a[i] - y - 1), 1));
			cnt += res == (gez(a[i],0) ^ gez(max(0LL, a[i] - z - 1), 2));
		}

		ss << cnt << endl;
	}
	cout << ss.str();


	return 0;
}
