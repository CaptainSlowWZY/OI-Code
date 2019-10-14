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
#ifdef DEBUG
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif

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

const int kInf = 0x3f3f3f3f, kMod = 998244353;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;
// const double kPie = acos(-1), kEps = 1e-9;

template <typename T> inline
void UMin(T & x, const T & y) { if (x > y) x = y; }
template <typename T> inline
void UMax(T & x, const T & y) { if (x < y) x = y; }
inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, LL ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

/* NOTICE! The default mod number is 1e9 + 7 ! */

const int kMaxn = 1e6 + 5, kInv2 = FPow(2);

int n, a, b;
int V[kMaxn], P[kMaxn], Q[kMaxn];

void Solve1();
void Solve2();

int main() {
	scanf("%d%d%d", &n, &a, &b);
	if (Mul(a, 2) == b) Solve1();
	else Solve2();
	int ans = 0;
	for (int i = 1, f = 1; i < n; ++i) {
		ans = Add(ans, Mul(V[i], f));
		f = Add(Mul(f, f), 2);
	} printf("%d\n", ans);
	return 0;
}

inline int C(int n, int r) {
	return Mul(P[n], Mul(Q[r], Q[n - r]));
}

void Solve1() {
	for (int i = P[0] = 1; i <= n; ++i)
		P[i] = Mul(P[i - 1], i);
	Q[n] = FPow(P[n]);
	for (int i = n - 1; i >= 0; --i)
		Q[i] = Mul(Q[i + 1], i + 1);
	for (int i = 1; i <= n; ++i)
		V[i] = Mul(C(n, i), FPow(kInv2, 1ll * i * (n - i)));
}

void Solve2() {
	int p = Mul(a, FPow(b)), q = Sub(1, p);
	for (int i = P[0] = Q[0] = 1; i <= n; ++i) {
		P[i] = Mul(P[i - 1], p); Q[i] = Mul(Q[i - 1], q);
	}
	for (int i = V[0] = 1; i < n; ++i)
		V[i] = Mul(Mul(V[i - 1], Sub(P[n - i + 1], Q[n - i + 1])),
				FPow(Sub(P[i], Q[i])));
}
