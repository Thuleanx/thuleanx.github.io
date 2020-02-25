#include <bits/stdc++.h>
using namespace std;

const int N = 4e4, oo = 1e9;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int t; cin>>t;
    int a[3];
    
    stringstream ss;
    while (t--) {
        cin>>a[0]>>a[1]>>a[2];
        int dp[3][N];
        int nxt[3][N];
        for (int i = 0; i < N; i++)
            dp[2][i] = abs(a[2]-i);
        for (int z = 1; z >= 0; z--) {
            dp[z][0] = oo;
            for (int i = 1; i < N; i++) {
                dp[z][i] = oo;
                int d = abs(a[z]-i);
                for (int j = i; j < N; j += i) {
                    if (dp[z][i] > d+dp[z+1][j])
                    	nxt[z][i] = j;
                    dp[z][i] = min(dp[z][i], d + dp[z+1][j]);
				}
            }
        }
        
        int ans = oo, j = 0;
        for (int i = 1; i < N; i++) {
            if (ans > dp[0][i]) j = i;
            ans = min(ans, dp[0][i]);
		}
        ss << ans << endl;
        for (int z = 0; z <= 2; z++) {
			ss << j << " \n"[z==2];
        	j = nxt[z][j];
		}
    }
    
    cout << ss.str();
    
    return 0;
}
