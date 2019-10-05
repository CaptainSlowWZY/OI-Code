// gcd
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

const int kFib = 88;

int tot, lb, ub;
LL n, m;
LL F[kFib + 5];

void PreWork();
void Solve1();
void Solve2();

int main() {
	PreWork();
	// return 0;
	int o, t;
	scanf("%d%d", &o, &t);
	while (t--) {
		scanf("%lld%lld", &n, &m);
		if (n > m) std::swap(n, m);
		tot = lb = 0, ub = kFib + 1;
		while (ub - lb > 1) {
			int mid = lb + ub >> 1;
			if (F[mid] > n || F[mid + 1] > m) ub = mid;
			else lb = mid;
		} --lb;
		// printf(" lb = %d\n", lb);
		if (o == 1) Solve1(); else Solve2();
	}
	return 0;
}

void PreWork() {
	F[1] = 1;
	for (int i = 2; i <= kFib; ++i)
		F[i] = F[i - 1] + F[i - 2];
}

void Dfs1(LL x, LL y, int dep, int use2) {
	if (x > n || y > m) return;
	// if (x >= 1e18) return;
	// printf(" x %lld, y %lld, dep %d, use2 %d\n", x, y, dep, use2);
	if (use2 && dep > 1) {
		// printf(" 2 used, x = %lld, y = %lld, dep = %d\n", x, y, dep);
		--dep;
		LL x1 = x * F[dep - 1] + y * F[dep],
			y1 = x * F[dep] + y * F[dep + 1];
		// printf("   x1 = %lld, y1 = %lld\n", x1, y1);
		x = x1, y = y1, dep = 1;
	}
	if (dep == 1) {
		if (y <= n && x + y <= m)
			tot = Add(tot, (m - x) / y % kMod);
		if (y <= m && x + y <= n)
			tot = Add(tot, (n - x) / y % kMod);
		return;
	}
	Dfs1(y, x + y, dep - 1, use2);
	Dfs1(y, x + (y << 1), dep - 1, 1);
}

void Solve1() {
	if (n == 1 && m == 1) { puts("1 1"); return; }
	if (lb == 1) tot = n;
	Dfs1(1, 1, lb, 0);
	printf("%d %d\n", lb, tot);
}

void Dfs2(LL x, LL y, int dep, int use2) {
//	use2 : 0 - not yet, 1 - used but not behined, 2 - behind
	// if (x > n || y > m) return;
	if (y > n) return;
	if (use2 < 2) {
		if (y <= n && x + y <= m)
			tot = Add(tot, (m - x) / y % kMod);
		if (y <= m && x + y <= n)
			tot = Add(tot, (n - x) / y % kMod);
	} else {
		if (y <= n && x + y <= m) tot = Add(tot, 1);
		if (y <= m && x + y <= n) tot = Add(tot, 1);
	} if (dep == 1) return;
	Dfs2(y, x + y, dep - 1, (bool)use2);
	if (!use2) Dfs2(y, x + (y << 1), dep - 1, 2);
}

void Solve2() {
	tot = 1 + (n >= 2 && m >= 2);
	Dfs2(1, 1, lb, 0);
	printf("%d\n", tot);
}