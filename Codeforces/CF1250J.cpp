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

#define fi first
#define se second
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

/* NOTICE! The default mod number is 1e9 + 7 ! */

const int kMaxn = 3e4 + 5;

int n;
LL k, sum;
LL C[kMaxn];

void Solve();

int main() {
	int t; scanf("%d", &t);
	while (t--) {
		scanf("%d%lld", &n, &k);
		sum = C[0] = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", C + i);
			UMax(sum, C[i] + C[i - 1]);
		} Solve();
	} return 0;
}

bool Check(LL per) {
	LL r = k, la = C[0], cur, t;
	for (int i = 1; i <= n; ++i) {
		cur = C[i];	
		t = (la + cur) / per;
		r -= t;
		if (r <= 0) return true;
		la = cur - (per * t - std::min(la, per * t));
	} return false;
}

void Solve() {
	LL lb = 0, ub = sum + 1;
	for (LL mid; ub - lb > 1; ) {
		mid = lb + ub >> 1;
		if (Check(mid)) lb = mid;
		else ub = mid;
	}
	printf("%lld\n", lb * k);
}
