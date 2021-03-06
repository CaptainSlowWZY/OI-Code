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

const int kMaxn = 3e5 + 5;

int n, m, tot, ans, sum[kMaxn << 1];
Pii anp = {1, 1};
char S[kMaxn];

void Gao(int, int);

int main() {
	scanf("%d%s", &n, S);
	m = kInf;
	for (int i = 0; i < n; ++i) {
		sum[i + 1] = sum[i] + (S[i] == '(' ? 1 : -1);
		UMin(m, sum[i + 1]);
	}
	if (sum[n]) { puts("0\n1 1"); return 0; }
	for (int i = 1; i <= n; ++i) {
		if (sum[i] == m) ++tot;
		sum[i + n] = sum[i];
	} ans = tot;
	Gao(m + 2, tot);
	Gao(m + 1, 0);
	printf("%d\n%d %d\n", ans, anp.fir, anp.sec);
	return 0;
}

void Gao(int x, int d) {
	for (int cnt = 0, i = 1, l = 1; i <= (n << 1); ++i) {
		if (sum[i] == x) ++cnt;
		if (sum[i] < x) {
			cnt = 0, l = i + 1 > n ? i % n + 1 : i + 1;
		}
		if (d + cnt >= ans) {
			ans = d + cnt;
			anp = {l, i + 1 > n ? i % n + 1 : i + 1};
		}
	}
}
