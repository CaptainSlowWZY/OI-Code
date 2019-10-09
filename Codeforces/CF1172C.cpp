// C1 & C2
// Good expect problem
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
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

const int kMaxn = 2e5 + 5, kMaxm = 3005;

int n, m, sa, sb, ss;
int A[kMaxn], W[kMaxn], inv[kMaxm << 2];
int F[kMaxm][kMaxm], G[kMaxm][kMaxm];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) scanf("%d", A + i);
	for (int i = 0; i < n; ++i) {
		scanf("%d", W + i);
		if (A[i]) sa += W[i];
		else sb += W[i];
	} ss = sa + sb;
	for (int i = std::max(0, m - sb); i <= 2 * m; ++i)
		inv[i] = FPow(ss + i - m);
	for (int i = m; i >= 0; --i) {
		F[i][m - i] = G[i][m - i] = 1;
		for (int j = std::min(m - i - 1, sb); j >= 0; --j) {
			F[i][j] = Mul(Add(Mul(sa + i + 1, F[i + 1][j]),
				Mul(sb - j, F[i][j + 1])), inv[i - j + m]);
			G[i][j] = Mul(Add(Mul(sb - j - 1, G[i][j + 1]),
				Mul(sa + i, G[i + 1][j])), inv[i - j + m]);
		}
	}
	for (int i = 0; i < n; ++i)
		printf("%d\n", Mul(W[i], A[i] ? F[0][0] : G[0][0]));
	return 0;
}
