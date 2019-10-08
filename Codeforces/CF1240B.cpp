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

void Solve();

int main() {
	int q;
	scanf("%d", &q);
	while (q--) Solve();
	return 0;
}

const int kMaxn = 3e5 + 5;

int n;
int minp[kMaxn], maxp[kMaxn], DP[kMaxn], A[kMaxn];

void Solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		minp[i] = kInf; maxp[i] = 0;
	}
	for (int i = 0; i < n; ++i) {
		scanf("%d", A + i);
		UMin(minp[A[i]], i); UMax(maxp[A[i]], i);
	}
	std::sort(A, A + n);
	n = std::unique(A, A + n) - A;
	int ans = kInf;
	for (int i = n - 1; i >= 0; --i) {
		if (i + 1 == n || maxp[A[i]] > minp[A[i + 1]])
			DP[i] = 1;
		else
			DP[i] = DP[i + 1] + 1;
		UMin(ans, n - DP[i]);
	}
	printf("%d\n", ans);
}
