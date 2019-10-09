#include <algorithm>
// #include <cassert>
#include <cctype>
#include <cmath>
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
// const double kPie = acos(-1), kEps = 1e-9;

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

DB a, b, c, d, L, R;

inline DB F(DB x) { return (c * x + d) / (a * x + b); }
inline DB Int(DB l, DB r) {
	return (F(l) + 4.0 * F((l + r) / 2.0) +
		F(r)) * (r - l) / 6.0;
}
DB Simpson(DB l, DB r, DB eps, DB x);

int main() {
	scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &L, &R);
	printf("%.6lf\n", Simpson(L, R, 1e-6, Int(L, R)));
	return 0;
}

DB Simpson(DB l, DB r, DB eps, DB x) {
	DB mid = (l + r) / 2.0,
	   ls = Int(l, mid), rs = Int(mid, r);
	if (fabs(ls + rs - x) <= 15.0 * eps)
		return ls + rs + (ls + rs - x) / 15.0;
	return Simpson(l, mid, eps / 2, ls) +
		Simpson(mid, r, eps / 2, rs);
}
