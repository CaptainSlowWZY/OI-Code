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

const int kX = 4e5;

int ifc[kX + 5], fac[kX + 5];
int x, y, r;

inline int C(int n, int r) {
	return Mul(fac[n], Mul(ifc[r], ifc[n - r]));
}

int main() {
	for (int i = fac[0] = 1; i <= kX; ++i)
		fac[i] = Mul(fac[i - 1], i);
	ifc[kX] = FPow(fac[kX]);
	for (int i = kX - 1; i >= 0; --i)
		ifc[i] = Mul(ifc[i + 1], i + 1);
	int cs;
	scanf("%d", &cs);
	while (cs--) {
		scanf("%d%d%d", &x, &y, &r);	
		if (x + y + r & 1 || x + y > r) {
			puts("0"); continue;
		}
		int t = x + y + r >> 1;
		printf("%d\n", Mul(C((t << 1) - x - y, t - y),
			Mul(fac[r], Mul(ifc[t - x - y], ifc[t])))); 
	} return 0;
}
