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
typedef std::vector<Pii> Vp;
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

const int kLim = 1e5, kMaxn = 1e5 + 5;

int n, k, totp;
int np[kMaxn], P[kMaxn], dw[kMaxn];
std::map<Vp, int> cnt;

Vp Fact(int n);

int main() {
	for (int i = 2; i <= kLim; ++i) {
		if (!np[i]) P[totp++] = dw[i] = i;
		for (int j = 0, d; j < totp && (d = i * P[j]) <= kLim; ++j) {
			np[d] = 1, dw[d] = P[j];
			if (i % P[j] == 0) break;
		}
	}
	scanf("%d%d", &n, &k);
	LL ans = 0;
	for (int i = 0, ai; i < n; ++i) {
		scanf("%d", &ai);
		Vp cur = Fact(ai);
		Vp nd = cur;
		for (auto & p : nd) p.se = (k - p.se) % k;
		ans += cnt[nd];
		++cnt[cur];
	} printf("%I64d\n", ans);
	return 0;
}

Vp Fact(int n) {
	Vp res;
//	printf(" n = %d\n", n);
	int a = 0, p = -1;
	for (; n > 1; n /= dw[n]) {
		if (p != dw[n]) {
			if (a %= k) res.pb({p, a});
			p = dw[n], a = 1;
		} else ++a;
	} if (a %= k) res.pb({p, a});
	if (res.empty()) res.pb({0, 0});
//	for (auto & p : res) printf(" %d^%d\n", p.fi, p.se);
//	puts("");
	return res;
}
