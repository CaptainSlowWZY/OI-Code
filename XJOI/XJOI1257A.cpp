#include <algorithm>
#include <cassert>
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
const DB kPie = acos(-1), kEps = 1e-7;

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

const int kMaxn = 205;

int n;
int X[kMaxn], Y[kMaxn], U[kMaxn], L[kMaxn];

DB F(DB x);
DB Simpson(DB l, DB r, DB eps, DB x);
inline DB Sqr(DB x) { return x * x; }
inline DB Int(DB l, DB r) {
	return (F(l) + 4.0 * F((l + r) / 2.0) +
		F(r)) * (r - l) / 6.0;
}

int main() {
	scanf("%d", &n);
	int lb = kInf, ub = -kInf;
	for (int i = 0; i < n; ++i) {
		scanf("%d%d%d%d", X + i, Y + i, U + i, L + i);
		UMax(ub, X[i] + U[i]); UMin(lb, X[i] - U[i]);
	} printf("%.3lf\n", Simpson(lb, ub, 1e-4, Int(lb, ub)));
	return 0;
}

typedef std::pair<DB, int> Pdi;

DB F(DB x) {
	static Pdi sb[kMaxn << 2];
	int zz = 0;
	for (int i = 0; i < n; ++i) {
		if (X[i] - U[i] < x && x < X[i] + U[i]) {
			DB d = sqrt(Sqr(U[i]) - Sqr(x - X[i]));
			sb[zz++] = {Y[i] - d, 1}; sb[zz++] = {Y[i] + d, -1};
			if (X[i] - L[i] < x && x < X[i] + L[i]) {
				d = sqrt(Sqr(L[i]) - Sqr(x - X[i]));
				sb[zz++] = {Y[i] - d, -1}; sb[zz++] = {Y[i] + d, 1};
			}
		}
	} std::sort(sb, sb + zz);
	DB res = 0;
	int flag = 0;
	for (int i = 0, j; i < zz; i = j + 1) {
		for (flag += sb[j = i].sec; j < zz &&
			fabs(sb[j + 1].fir - sb[j].fir) <= kEps; )
			flag += sb[++j].sec;
		if (j + 1 < zz && flag)
			res += sb[j + 1].fir - sb[i].fir;
	} return res;
}

DB Simpson(DB l, DB r, DB eps, DB x) {
//	printf(" [%.5lf, %.5lf] eps %.5lf, x %.5lf\n", l, r, eps, x);
	DB mid = (l + r) / 2.0,
	   ls = Int(l, mid), rs = Int(mid, r);
	if (fabs(ls + rs - x) <= 15.0 * eps)
		return ls + rs + (ls + rs - x) / 15.0;
	return Simpson(l, mid, eps / 2, ls) + Simpson(mid, r, eps / 2, rs);
}
