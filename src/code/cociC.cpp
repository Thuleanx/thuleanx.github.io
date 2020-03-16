
#include <bits/stdc++.h>
using namespace std;

#define fr(i,a,b) for (int i = (b)-1; i >= a; i--)
#define f(i,a,b) for (int i = a; i < b; i++)
#define IN(i,a,b) (a<=i&&i<=b)

const int oo = 1e9;

const int N = 1000;
int s, t, p;
vector<int> adj[N], rev[N];

void addEdge(int v, int w) {
	adj[v].push_back(w);
	rev[w].push_back(v);
}

void init() {
	s = 0, t = 2, p = 3;
	addEdge(s, 1);
	addEdge(1, t); // this makes it 0
}

void add1() {
	addEdge(s,p);
	addEdge(p,t);
	p++;
}

void muln2() {
	int a = p++, b = p++, nt = p++;
	for (int x : {a,b}) {
		for (int v : rev[t]) addEdge(v,x);
		addEdge(x,nt);
	}
	addEdge(t,nt);
	t = nt;
}

void neg() {
	int a = p++, nt = p++;
	for (int x : {a}) {
		for (int v : rev[t]) addEdge(v,x);
		addEdge(x,nt);
	}
	addEdge(t,nt);
	t = nt;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	long long K; cin>>K; 
	bool flipped = K < 0;
	K = abs(K);

	vector<int> op;
	while (K) {
		if (K&1) op.push_back(1);
		op.push_back(0);
		K /= 2;
	}
	if (op.size()) {
		op.pop_back();
	}
	init();
	while (op.size()) {
		if (op.back()) add1();
		else {
			muln2();
			neg();
		}
		op.pop_back();
	}
	if (flipped) neg();

	stringstream ss;
	int m = 0;
	f(i,0,p) m += adj[i].size();
	ss << p << " " << m << endl;
	int display[p];
	f(i,0,p) display[i] = i;
	if (p-1 != t)
		swap(display[t], display[p-1]);	
	f(i,0,p)
		for (int w : adj[i])
			ss << display[i]+1 << " " << display[w]+1 << endl;
	cout << ss.str();


	return 0;
}
