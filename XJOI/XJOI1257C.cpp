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

const int kMaxn = 1e5 + 5;

int n, k;
Vi coi[kMaxn];

LL Solve(const Vi & C);

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0, ai; i < n; ++i) {
		scanf("%d", &ai);
		coi[i % k].pb(ai);
	}
	LL ans = 0;
	for (int i = 0; i < k; ++i)
		ans += Solve(coi[i]);
	printf("%lld\n", ans);
	return 0;
}

LL Solve(const Vi & C) {
	if (C.empty()) return 0;
	static LL DP[kMaxn][2];
	DP[0][0] = DP[0][1] = 0;
	for (int i = 0; i < SZ(C); ++i) {
		DP[i + 1][0] = std::max(DP[i][0], DP[i][1]);
		if (i)
			DP[i + 1][1] = DP[i][0] + C[i] + C[i - 1];
	} return std::max(DP[SZ(C)][0], DP[SZ(C)][1]);
}
