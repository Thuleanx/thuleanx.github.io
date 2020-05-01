#ifndef POLY
#define POLY

#include <bits/stdc++.h>
using namespace std;


const int DIM = 20;
using ld = long double;
using ll = long long;
const ll oo = 1e9;
const ll loo = 1e18;

#define f(i,a,b) for (int i = a; i < b; i++)
#define IN(i,a,b) (a<=i && i<=b)

// for 2d computation is much faster if this is represented as a complex number
// for 3d the same is true if you represent points as quaternions
using point = array<ld, DIM>;  

struct poly {
	ld dia = -1;
	ld Lmax = -1;
	point lo, hi;
	bool ccen = 0;
	point cen;
	poly() { f(j,0,DIM) lo[j] = -loo, hi[j] = loo; }
	poly(point lo, point hi) : lo(lo), hi(hi) {}
	poly(vector<point> pa) {
		f(i,0,DIM) lo[i] = loo, hi[i] = -loo;
		for (point &p : pa) {
			f(i,0,DIM) {
				lo[i] = min(lo[i], p[i]);
				hi[i] = max(hi[i], p[i]);
			}
		}
	}
	/* poly(const poly &o) : lo(o.lo), hi(o.hi) {} */
	ld dist2(point p) {
		ld d2 = 0;
		f(j,0,DIM) if (!IN(p[j], lo[j], hi[j])) {
			ld md = max(lo[j]-p[j], p[j]-hi[j]);
			d2 += md*md;
		}
		return d2;
	}
	poly cut(int i, ld val, bool lt) {
		poly cp(lo,hi);
		if (lt) cp.lo[i] = val;
		else cp.hi[i] = val;
		return cp;
	}
	ld diam2() {
		if (dia != -1) return dia;
		dia = 0;
		f(i,0,DIM) {
			ld dist = hi[i]-lo[i];
			dia += dist*dist;
		}
		return dia; // squared diameter
	}
	void add(point &p) {
		f(i,0,DIM) {
			lo[i] = min(lo[i], p[i]);
			hi[i] = max(hi[i], p[i]);
		}
	}
	ld computeLmax() {
		if (Lmax != -1) return Lmax;
		f(i,0,DIM) Lmax = max(Lmax, hi[i]-lo[i]);
		return Lmax;
	}
	point center() {
		if (ccen) return cen;
		f(i,0,DIM) cen[i] = (hi[i]+lo[i]) / 2;
		ccen = 1;
		return cen;
	}
	void reset() {
		dia = -1;
		f(i,0,DIM) lo[i] = loo, hi[i] = -loo;
	}
	string to_string() {
		stringstream ss;
		ss << lo[0] << " " << hi[0] << " " << lo[1] << " " << hi[1];
		return ss.str();
	}
};

ld dist2(point a, point b) {
	ld res = 0;
	f(j,0,DIM) {
		ld md = a[j]-b[j];
		res += md*md;
	}
	return res;
}

// dball
ld dball(poly &a, poly &b) {
	ld ans = 0;
	point aa = a.center(), bb = b.center();
	f(i,0,DIM) {
		ld dist = (aa[i]-bb[i]);
		ans += dist*dist;
	}
	return sqrt(ans) - sqrt(a.diam2()) - sqrt(b.diam2());
}

// dbox distance squared
ld dbox2(poly &a, poly &b) {
	ld ans = 0;
	f(i,0,DIM) {
		ld dist = 0;
		if (a.lo[i] >= b.hi[i]) dist = (a.lo[i] - b.hi[i]);	
		if (a.hi[i] <= b.lo[i]) dist = (b.lo[i] - a.hi[i]);
		ans += dist*dist;
	}
	return ans;
}

#endif
