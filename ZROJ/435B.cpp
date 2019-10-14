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

const int kMaxn = 2e5 + 5;

int n, q, k;
int C[kMaxn];

namespace solver1 {
	void Solve();
}

int main() {
	scanf("%d%d%d", &n, &q, &k);
	for (int i = 0; i < n; ++i) scanf("%d", C + i);
	solver1::Solve();
	return 0;
}

namespace solver1 {
	Mii cnt[kMaxn];
	int sta[kMaxn], apr[kMaxn], lig[kMaxn];
	std::vector<Pii> G[kMaxn];

	void Solve() {
		n = std::unique(C, C + n) - C;
		for (int i = 0; i < n; ++i) {
			if (i) ++cnt[C[i]][C[i - 1]];
			if (i + 1 < n) ++cnt[C[i]][C[i + 1]];
			++apr[C[i]];
		}
		int rt = (int)ceil(sqrt(k + 0.5));
		for (int i = 1; i <= k; ++i) {
			if (SZ(cnt[i]) >= rt) {
				for (auto & p : cnt[i]) {
					if (SZ(cnt[p.fir]) >= rt)
						G[i].pb(p);
				}
			} else {
				for (auto & p : cnt[i])
					G[i].pb(p);
			}
		}
		int ans = 0;
		for (int x; q--; ) {
			scanf("%d", &x);
			int deg = 0, f = sta[x] ? -1 : 1;
			if (SZ(cnt[x]) < rt) {
				for (auto & p : G[x]) {
					if (sta[p.fir]) deg += p.sec;
					if (SZ(cnt[p.fir]) >= rt)
						lig[p.fir] += p.sec * f;
				}
			} else {
				for (auto & p : G[x])
					if (sta[p.fir]) deg += p.sec;
				deg += lig[x];
			} sta[x] ^= 1, ans += f * (apr[x] - deg);
			printf("%d\n", ans);
		}
	}
}
