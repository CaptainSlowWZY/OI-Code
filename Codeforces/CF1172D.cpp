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

struct Door { int x1, y1, x2, y2; };

const int kMaxn = 1005;

int n;
int R[kMaxn], C[kMaxn];
std::vector<Door> dr;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", R + i);
	for (int i = 1; i <= n; ++i) scanf("%d", C + i);
	for (int i = 1; i < n; ++i) {
		int x, y;
		for (int j = 1; j <= n; ++j) {
			if (R[j] == i) x = j;
			if (C[j] == i) y = j;
		}
		if (x == i && y == i) continue;
		dr.pb({i, y, x, i});
		std::swap(R[i], R[x]);
		std::swap(C[i], C[y]);
	}
	printf("%d\n", SZ(dr));
	for (auto & d : dr) printf("%d %d %d %d\n", d.x1, d.y1, d.x2, d.y2);
	return 0;
}
