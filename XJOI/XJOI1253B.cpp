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

const int kLen = 1e5 + 5;

char S[kLen], T[kLen];
int F[kLen], ex[kLen];

int main() {
	scanf("%s%s", S, T + 1);
	int lent = strlen(T + 1);
	for (int i = 2, j = 0; i <= lent; ++i) {
		while (j && T[i] != T[j + 1]) j = F[j];
		if (T[i] == T[j + 1]) ++j;
		F[i] = j;
	}
	ex[1] = lent;
	int x = 1, k = 2;
	while (x < lent && T[x] == T[x + 1]) ++x;
	ex[2] = x - 1;
	for (int i = 3, p, l, j; i <= lent; ++i) {
		p = k + ex[k] - 1, l = ex[i - k + 1];
		if (i + l < p + 1) ex[i] = l;
		else {
			for (j = std::max(0, p - i + 1);
				i + j <= lent && T[j + 1] == T[j + i]; ++j);
			ex[k = i] = j;
		}
	}
	ex[1] = 0;
	for (int i = 1; i <= lent; ++i)
		UMax(ex[i + 1], ex[F[i] + 1]);
	LL ans = 1ll * lent * strlen(S);
	for (int i = 1, j = 0; S[i]; ++i) {
		while (j && T[j + 1] != S[i]) j = F[j];
		if (T[j + 1] == S[i]) ++j;
		ans -= ex[j + 1];
	} printf("%lld\n", ans);
	return 0;
}