#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>

#define fi first
#define se second
#define pb push_back
#define ALL(_) _.begin(), _.end()
#define SZ(_) (int)_.size()

typedef double Db;
typedef std::pair<Db, Db> Pdd;
typedef std::vector<Pdd> Vp;

const Db kEps = 1e-9, kInfD = 1e13;
const int kMaxn = 4e4 + 5, kU = (1 << 5) + 2;

int n, m, q, u;
int X[kMaxn], Y[kMaxn], L[6], R[6], P[6];
Pdd in[kU], le[kU][kMaxn], ri[kU][kMaxn];

inline int Sign(Db x) {
	return fabs(x) <= kEps ? 0 : (x < 0 ? -1 : 1);
}
inline Db Line0(Db x1, Db y1, Db x2, Db y2) {
	return x1 - (x2 - x1) / (y2 - y1) * y1;
}
inline Pdd Inter(Db l, Db r, Db p, Db x, Db y) {
	return !Sign(p - y) ? Pdd(kInfD, kInfD) : 
		Pdd(Line0(l, p, x, y), Line0(r, p, x, y));
}
inline Pdd Cap(const Pdd & a, const Pdd & b) {
	return {std::max(a.fi, b.fi), std::min(a.se, b.se)};
}
inline bool Empty(const Pdd & a) { return Sign(a.fi - a.se) > 0; }
inline bool CmpL(const Pdd & a, const Pdd & b) { return b.fi > a.fi + kEps; }
inline bool CmpR(const Pdd & a, const Pdd & b) { return b.se + kEps < a.se ; }
int Calc(int s, const Pdd & p);

int main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 0; i < n; ++i)
		scanf("%d%d", X + i, Y + i);
	for (int i = 0; i < m; ++i) {
		scanf("%d%d%d", L + i, R + i, P + i);
		Pdd *cur = le[1 << i];
		for (int j = 0; j < n; ++j)
			*cur++ = Inter(L[i], R[i], P[i], X[j], Y[j]);
	} u = (1 << m) - 1;
	for (int t, s = 1; s <= u; ++s) {
		if (__builtin_popcount(s) == 1) continue;
		for (int i = 0; i < m; ++i)
			if (s >> i & 1) { t = i; break; }	
		Pdd *cur = le[s], *la = le[s ^ 1 << t],
			*lb = le[1 << t];
		for (int i = 0; i < n; ++i) *cur++ = Cap(*la++, *lb++);
	}
	for (int s = 1; s <= u; ++s) {
		int t = n;
		Pdd *cur = le[s], *la = le[s];
		for (int i = 0; i < n; ++i, ++cur) {
			if (Empty(*cur)) continue;
			*la++ = *cur;	
		} while (la < cur) *la++ = {kInfD, kInfD};
		cur = le[s], la = ri[s];
		for (int i = 0; i < n; ++i) *la++ = *cur++;
		std::sort(le[s], le[s] + n, CmpL);
		std::sort(ri[s], ri[s] + n, CmpR);
#ifdef SB_DUKE
		printf(" set %d\n   left: ", s);
		for (int i = 0; i < n; ++i) printf("(%.2lf, %.2lf) ", le[s][i].fi, le[s][i].se);
		printf("\n   right: ");
		for (int i = 0; i < n; ++i) printf("(%.2lf, %.2lf) ", ri[s][i].fi, ri[s][i].se);
		puts("");
#endif
	}
	for (int a, b, ans; q--; ) {
		scanf("%d%d", &a, &b);
		for (int i = 0; i < m; ++i)
			in[1 << i] = Inter(L[i], R[i], P[i], a, b);
		ans = n;
		for (int t, s = 1; s <= u; ++s) {
			if (__builtin_popcount(s) > 1) {
				for (int i = 0; i < m; ++i)
					if (s >> i & 1) { t = i; break; }
				in[s] = Cap(in[s ^ 1 << t], in[1 << t]);
			} if (Empty(in[s])) continue;
			ans += (__builtin_popcount(s) & 1 ? -1 : 1) * (n - Calc(s, in[s]));
		} printf("%d\n", ans);
	} return 0;
}

int Calc(int s, const Pdd & p) {
//	printf("  calc_set %d, point(%.3lf, %.3lf)\n", s, p.fi, p.se);
	Pdd *i1 = std::upper_bound(le[s], le[s] + n, (Pdd){p.fi + kEps, p.se}, CmpL),
		*i2 = std::upper_bound(ri[s], ri[s] + n, (Pdd){p.fi, p.se - kEps}, CmpR);
//	printf("    i1 %d; i2 %d\n", i1 - le[s], i2 - ri[s]);
	return n - (i1 - le[s]) + n - (i2 - ri[s]);
}
