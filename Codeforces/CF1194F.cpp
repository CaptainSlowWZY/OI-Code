#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>
// #include <cmath>
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

const int kInf = 0x3f3f3f3f, kMod = 1e9 + 7, kInv2 = 500000004;
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

const int kMaxn = 2e5 + 5;

int n;
int fac[kMaxn], ifc[kMaxn];
LL T;

inline int C(int n, int r) {
	// if (n < r) return 0;
	return Mul(fac[n], Mul(ifc[r], ifc[n - r]));
}

int main() {
	scanf("%d%lld", &n, &T);
	for (int i = fac[0] = 1; i <= n; i++)
		fac[i] = Mul(fac[i - 1], i);
	ifc[n] = FPow(fac[n]);
	for (int i = n - 1; i >= 0; i--)
		ifc[i] = Mul(ifc[i + 1], i + 1);
	LL sum0 = 0, sum1 = 0;
	int sc = 0, l0 = 0, r0 = 0;
	int ans = 0, pw = 1;
	for (int i = 0, ti; i < n; i++) {
		scanf("%d", &ti);
		sum1 = sum0 + ti;
		LL l = std::max(0ll, T - sum1 + 1), r = std::min(T - sum0, (LL)(i + 1));
		pw = Mul(pw, kInv2);
		int tmp = Mul(pw, i);
		if (l <= r) {
			// if (r0 == -1) r0 = 0;
			while (r0 <= r) {
				// printf(" C(%d, %d) = %d\n", i, r0, C(i, r0));
				sc = Add(sc, C(i, r0++));
			}
			while (r0 - 1 > r) {
				sc = Sub(sc, C(i, --r0));
			}
			while (l0 < l)
				sc = Sub(sc, C(i, l0++));
			while (l0 > l)
				sc = Add(sc, C(i, --l0));
			// printf(" [%lld, %lld], sc = %d, sct = %d\n", l, r, sc, sct);
			ans = Add(ans, Mul(tmp, sc));
		}
		r = std::min(T - sum0 + 1, (LL)(i + 1));
		// printf(" [l1 %lld, r1 %lld]\n", l, r);
		if (l <= r && r) {
			--l, --r;
			l = std::max(l, 0ll);
			// if (r0 == -1) r0 = 0;
			// while (r0 <= r)
			// 	sc = Add(sc, C(i, r0++));
			while (r0 <= r) {
				// printf(" C(%d, %d) = %d\n", i, r0, C(i, r0));
				sc = Add(sc, C(i, r0++));
			}
			while (r0 - 1 > r) {
				sc = Sub(sc, C(i, --r0));
			}
			while (l0 < l)
				sc = Sub(sc, C(i, l0++));
			while (l0 > l)
				sc = Add(sc, C(i, --l0));
			// printf(" [%lld, %lld], sc = %d, sct = %d\n", l, r, sc, sct);
			ans = Add(ans, Mul(tmp, sc));
		}
		if (l0 < r0)
			sc = Add(Mul(sc, 2), Add(C(i, r0++), l0 ? C(i, l0 - 1) : 0));
		// printf(" i = %d, [%d, %d) s = %d\n", i, l0, r0, sc);
		sum0 = sum1;
	}
	pw = Mul(pw, n);
	// printf("  ans = %d\n", ans);
	for (int i = 0; i <= n && sum0 + i <= T; i++)
		ans = Add(ans, Mul(pw, C(n, i)));
	printf("%d\n", ans);
	return 0;
}

/*

3 5
2 2 2

3 5
2 1 2

*/