#include <algorithm>
#include <cassert>
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

const int kInf = 0x3f3f3f3f, kMod = 1e9 + 7;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;
// const double kPie = acos(-1), kEps = 1e-9;

int mod;

template <typename T> inline
void UMin(T & x, const T & y) { if (x > y) x = y; }
template <typename T> inline
void UMax(T & x, const T & y) { if (x < y) x = y; }
inline int Add(int a, int b) { return (a += b) >= mod ? a - mod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + mod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % mod; }
int FPow(int bs, int ex = mod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

/* NOTICE! The default mod number is 1e9 + 7 ! */

void ExtGcd(LL a, LL b, LL & x, LL & y) {
	if (!b) { x = 1, y = 0; return; }
	ExtGcd(b, a % b, y, x);
	y -= a / b * x;
}

LL n, p, w, d;

int main() {
	scanf("%lld%lld%lld%lld", &n, &p, &w, &d);
	LL g = std::__gcd(w, d);
	if (p % g) { puts("-1"); return 0; }
	LL x, y;
	ExtGcd(w, d, x, y); // x = x0 + k * b / g, y = y0 - k * a / g
	LL t1 = d / g, t2 = w / g;
	x = x % t1 * ((p / g) % t1);
	x = (x % t1 + t1) % t1;
	if (x * w <= p && (p - x * w) / d + x <= n) {
		y = (p - x * w) / d;
		printf("%lld %lld %lld\n", x, y, n - x - y);
		return 0;
	} else {
		y = y % t2 * ((p / g) % t2);
		y = (y % t2 + t2) % t2;
		if (y * d <= p && (p - y * d) / w + y <= n) {
			x = (p - y * d) / w;
			printf("%lld %lld %lld\n", x, y, n - x - y);
			return 0;
		}
	} puts("-1");
	return 0;
}
