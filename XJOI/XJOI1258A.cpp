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

const int kMaxn = 1e5 + 5;

int n;
int A[kMaxn];
LL k;

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%lld", &n, &k);
		LL sum = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d", A + i);
			sum += A[i];
		}
		int avg = sum / n, ov = sum - avg * n,
			eq = n - ov, ovv = ov;
		std::sort(A, A + n);
		LL cost = 0, sumo = 0, suml = 0;
		int cnto = 0, cntl = 0, gap = -1;
		for (int i = 0, la; i < n; ++i) {
			la = eq ? (--eq, avg) : (--ov, avg + 1);
			if (A[i] >= la) {
				cost += A[i] - la;
				sumo += A[i], ++cnto;
			} else {
				cost += la - A[i];
				suml += A[i], ++cntl;
				gap = i;
			}
		} cost >>= 1;
		if (cost <= k) printf("%d\n", (bool)ovv);
		else {
			suml += k;
			for (int i = gap; i >= 0; --i) {
				int cur = std::max((LL)A[i], suml / (i + 1));
				A[i] = cur, suml -= cur;
			} sumo -= k;
			for (int i = gap + 1; i < n; ++i) {
				int cur = std::min((LL)A[i], sumo / (n - i));
				A[i] = cur, sumo -= cur;
			}
			int min = kInf, max = 0;
			for (int i = 0; i < n; ++i) {
				UMin(min, A[i]); UMax(max, A[i]);
			}
			printf("%d\n", max - min);
		}
	} return 0;
}
