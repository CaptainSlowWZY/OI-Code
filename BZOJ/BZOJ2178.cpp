#include <algorithm>
// #include <cassert>
#include <cctype>
// #include <cmath>
#include <cstdio>
// #include <cstdlib>
#include <cstring>
// #include <ctime>
#include <map>
#include <queue>
#include <set>
#include <vector>

#define fir first
#define sec second
#define pb push_back
#define pch putchar
#define rg register
#define SZ(_) (int)_.size()
#define SORT(_) std::sort(_.begin(), _.end())
#define LB(_, __) std::lower_bound(_.begin(), _.end(), __)
#define UB(_, __) std::upper_bound(_.begin(), _.end(), __)

typedef long long LL;
typedef double DB;
typedef std::pair<DB, DB> Pdd;
typedef std::pair<int, int> Pii;
typedef std::pair<LL, int> Pli;
typedef std::pair<int, LL> Pil;
typedef std::pair<LL, LL> Pll;
typedef std::vector<int> Vi;
typedef std::vector<LL> Vl;
typedef std::map<int, int> Mii;
typedef std::map<LL, int> Mli;
typedef std::map<int, LL> Mil;
typedef std::map<LL, LL> Mll;
typedef std::set<int> Si;
typedef std::set<LL> Sl;

const int kInf = 0x3f3f3f3f, kMod = 1e9 + 7;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;
const double kPie = acos(-1), kEps = 1e-6;

template <typename T> inline
void UMin(T & x, const T & y) { if (x > y) x = y; }
template <typename T> inline
void UMax(T & x, const T & y) { if (x < y) x = y; }
inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

const int kMaxn = 1005;

struct Circle {
	int x, y, r;
	bool operator<(const Circle & c) const {
		return r > c.r;
	}
} C[kMaxn], B[kMaxn];

int n, nn, lb, ub;
int sub[kMaxn];

DB F(DB l);
DB Simpson(DB l, DB r, DB eps, DB x);
inline DB Sqr(DB x) { return x * x; }
inline DB Dist(DB x1, DB y1, DB x2, DB y2) {
	return sqrt(Sqr(x1 - x2) + Sqr(y1 - y2));
}
inline DB Int(DB l, DB r) {
	return (F(l) + 4 * F((l + r) / 2) + F(r)) * (r - l) / 6;
}

int main() {
	scanf("%d", &n);
	lb = kInf, ub = -kInf;
	for (int i = 0; i < n; ++i) {
		scanf("%d%d%d", &C[i].x, &C[i].y, &C[i].r);
		UMin(lb, C[i].x - C[i].r);
		UMax(ub, C[i].x + C[i].r);
	} std::sort(C, C + n);
	for (int i = 0; i < n; ++i) {
		if (sub[i]) continue;
		for (int j = i + 1; j < n; ++j) {
			if (sub[j]) continue;
			if (Dist(C[i].x, C[i].y, C[j].x, C[j].y) +
				C[j].r < C[i].r + kEps) sub[j] = 1;
		}
	}
	for (int i = 0; i < n; ++i) {
		if (sub[i]) continue;
		B[nn++] = C[i];
	} n = nn;
	DB ans = 0;
	for (int x = lb; x < ub; ++x) {
		for (int i = nn = 0; i < n; ++i) {
			if (B[i].x + B[i].r <= x ||
				B[i].x - B[i].r >= x + 1) continue;
			C[nn++] = B[i];
		}
		ans += Simpson(x, x + 1, 1e-7, Int(x, x + 1));
	} printf("%.3lf\n", ans);
	return 0;
}

DB F(DB l) {
	static Pdd seg[kMaxn];
	int cs = 0;
	for (int i = 0; i < nn; ++i) {
		if (fabs(C[i].x - l) > C[i].r - kEps)
			continue;
		DB dy = sqrt(Sqr(C[i].r) - Sqr(C[i].x - l));
		seg[cs++] = {C[i].y - dy, C[i].y + dy};
	} std::sort(seg, seg + cs);
	DB res = 0, la = -1e9;
	for (int i = 0; i < cs; ++i) {
		if (seg[i].fir > la) {
			res += seg[i].sec - seg[i].fir;
			la = seg[i].sec;
		} else if (seg[i].sec > la) {
			res += seg[i].sec - la;
			la = seg[i].sec;
		}
	} return res;
}

DB Simpson(DB l, DB r, DB eps, DB x) {
	DB mid = (l + r) / 2,
	   ls = Int(l, mid), rs = Int(mid, r);
	if (fabs(ls + rs - x) <= 15 * eps)
		return ls + rs + (ls + rs - x) / 15;
	return Simpson(l, mid, eps / 2, ls) +
		Simpson(mid, r, eps / 2, rs);
}
