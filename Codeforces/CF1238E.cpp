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

int mod;

template <typename T> inline
void UMin(T & x, const T & y) { if (x > y) x = y; }
template <typename T> inline
void UMax(T & x, const T & y) { if (x < y) x = y; }
inline int Add(int a, int b) { return (a += b) >= mod ? a - mod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + mod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % mod; }
int FPow(int bs, int ex = mod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

/* NOTICE! The default mod number is 1e9 + 7 ! */

const int kMaxn = 1e5 + 5, kU = (1 << 20) + 5;

int n, m;
int A[22][22], lg[kU], sum[22][kU], crs[kU], DP[kU];
char S[kMaxn];

inline int LowBit(int x) { return x & -x; }

int main() {
	scanf("%d%d%s", &n, &m, S);
	S[0] -= 'a';
	for (int i = 1; S[i]; ++i) {
		S[i] -= 'a';
		++A[S[i - 1]][S[i]];
	}
	for (int i = 0; i < m; ++i) {
		for (int j = i + 1; j < m; ++j) {
			A[i][j] += A[j][i]; A[j][i] = A[i][j];
		}
	}
	for (int i = 0; i < m; ++i) lg[1 << i] = i;
	int u = (1 << m) - 1;
	for (int i = 0; i < m; ++i) {
		for (int j = 1; j <= u; ++j)
			sum[i][j] = sum[i][j ^ LowBit(j)] + A[i][lg[LowBit(j)]];
	}
	for (int i = 1; i <= u; ++i) {
		for (int j = i; j; j ^= LowBit(j))
			crs[i] += sum[lg[LowBit(j)]][u ^ i];
	}
	for (int s = 1, t; s <= u; ++s) {
		DP[s] = kInf;
		for (int i = s; i; i ^= LowBit(i))
			UMin(DP[s], DP[s ^ LowBit(i)] + crs[s ^ LowBit(i)]);
	}
	printf("%d\n", DP[u]);
	return 0;
}
