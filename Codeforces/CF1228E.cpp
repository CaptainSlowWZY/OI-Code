#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
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

const int kMaxn = 250, kTot = kMaxn * kMaxn + 5;

int n, k;
int ifc[kTot], fac[kTot];

inline int C(int n, int r) {
	return Mul(fac[n], Mul(ifc[r], ifc[n - r]));
}

int main() {
	scanf("%d%d", &n, &k);
	int tot = n * n;
	for (int i = fac[0] = 1; i <= tot; i++)
		fac[i] = Mul(fac[i - 1], i);
	ifc[tot] = FPow(fac[tot]);
	for (int i = tot - 1; i >= 0; i--)
		ifc[i] = Mul(ifc[i + 1], i + 1);
	int ans = 0;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			int x = i * j;
			if (2 * n - i - j & 1)
				ans = Sub(ans, Mul(Mul(C(n, i), C(n, j)),
					Mul(FPow(k, x), FPow(k - 1, tot - x))));
			else 
				ans = Add(ans, Mul(Mul(C(n, i), C(n, j)),
					Mul(FPow(k, x), FPow(k - 1, tot - x))));
		}
	} printf("%d\n", ans);
	return 0;
}
