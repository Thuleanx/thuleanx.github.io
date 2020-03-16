
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5+7;
const int oo = 1e9;
int n, q;
string s;
int cnt[N], num[N];

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define f(i,a,b) for (int i = a; i < b; i++)
#define mp make_pair
#define mt make_tuple

struct SuffixArray {
	vi sa, lcp;
	SuffixArray(string& s, int lim=256) { // or basic_string<int>
		int n = sz(s) + 1, k = 0, a, b;
		vi x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			rep(i,0,n) ws[x[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		rep(i,1,n) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};

struct SegTree {
	long long tree[N<<2], lazy[N<<2];
	SegTree () {
		f(i,0,N<<2) tree[i] = oo, lazy[i] = 0;
	}
	void add(int i, int lo, int hi, int l, int r, long long amt) {
		if (lo > hi) return ;
		push(i);
		if (lo > r || hi < l) return ;
		if (l <= lo && hi <= r) {
			lazy[i] += amt;
			push(i);
		} else {
			int mid = lo+hi>>1;
			add(i<<1, lo, mid, l, r, amt);
			add(i<<1|1, mid+1, hi, l, r, amt);
			tree[i] = min(tree[i<<1],tree[i<<1|1]);
		}
	}
	long long query(int i, int lo, int hi, int l, int r) {
		if (lo > hi) return oo;
		push(i);
		if (lo > r || hi < l) return oo;

		if (l <= lo && hi <= r)
			return tree[i];
		else {
			int mid = lo+hi>>1;
			return min(query(i<<1, lo, mid, l, r), query(i<<1|1, mid+1, hi, l, r));
		}
	}
	void push(int v) {
		if (lazy[v]) {
			tree[v] += lazy[v];
			if ((v<<1) < (N<<2)) {
				lazy[v<<1] += lazy[v];
				lazy[v<<1|1] += lazy[v];
			}
			lazy[v] = 0;
		}
	}
	void add(int lo, int hi, long long amt) { 
		add(1,0,N-1,lo,hi,amt); 
	}
	long long query(int lo, int hi) { return query(1,0,N-1,lo,hi); }
	void sett(int i, long long amt) {
		add(i,i,amt-query(i,i));
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>s>>q;
	f(i,0,n) {
		num[i] = (i?num[i-1]:0) + (s[i]=='1');
		cnt[i] = (i?cnt[i-1]+(s[i]=='1'&&s[i-1]=='1'):0);
	}

	SuffixArray arr(s);
	int where[n+1];
	f(i,0,n+1) where[arr.sa[i]] = i;
	SegTree ds;
	f(i,0,n+1) ds.sett(i,arr.lcp[i]);

	stringstream ss;
	while (q--) {
		int i,j, len; cin>>i>>j>>len;
		i--; j--;
		
		int ii = where[i], jj = where[j];
		if (ii > jj) {
			swap(ii,jj);
			swap(i,j);
		}

		if (i == j || ds.query(ii+1,jj) >= len) {
			// if exactly equal
			ss << "Yes" << endl;
		} else {
			// if can be transformed
			bool g1 = cnt[i+len-1]-cnt[i], g2 = cnt[j+len-1]-cnt[j];
			int n1 = num[i+len-1]-(i?num[i-1]:0), n2 = num[j+len-1]-(j?num[j-1]:0);

			if (g1 && g2 && n1 == n2)
				ss << "Yes" << endl;
			else ss << "No" << endl;
		}
	}
	cout << ss.str();
	
	
	return 0;
}
