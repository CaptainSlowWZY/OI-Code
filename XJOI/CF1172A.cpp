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

const int kMaxn = 2e5 + 5;

int n;
int A[kMaxn], step[kMaxn];

int main() {
	scanf("%d", &n);
	int ans = 0;
	for (int i = 0, bi; i < n; ++i) {
		scanf("%d", &bi);
		if (bi) {
			UMax(ans, n - bi + 1);
			step[bi] = 1;
		}
	}
	for (int i = 0; i < n; ++i) scanf("%d", A + i);
	int p = n - 1;
	while (p && A[p] == A[p - 1] + 1) --p;
	int fail = 0;
	if (A[p] <= 1) {
		for (int i = 0; i < p; ++i) {
			if (A[i]) {
				UMax(ans, i + 2 + n - A[i]);
				step[A[i]] = i + 2;
			}
		}
		if (!A[p]) ++p;
		// printf(" p = %d\n", p);
		for (int i = A[n - 1] + 1; i <= n; ++i) {
			if (i - A[n - 1] < step[i]) { fail = 1; break; }
		}
	} else fail = 1;
	// printf(" fail = %d\n", fail);
	if (fail) {
		for (int i = 0; i < n; ++i) {
			if (A[i]) UMax(ans, i + 2 + n - A[i]);
		}
	} printf("%d\n", ans);
	return 0;
}