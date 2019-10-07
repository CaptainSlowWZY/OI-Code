// head
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

const int kMaxn = 2e5 + 5;

int n;
LL A[kMaxn];

inline LL LowBit(LL x) { return x & -x; }

namespace trie {
	void Insert(LL);
	LL Query(LL);
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%lld", A + i);

	std::sort(A, A + n);
	LL topb = 0;
	for (int i = n - 2; i >= 0; --i)
		UMax(topb, A[i] ^ A[i + 1]);
	while (topb ^ LowBit(topb)) topb ^= LowBit(topb);
	LL ans = kInf64;
	for (int i = 0; i < n; ++i) {
		if (A[i] & topb) UMin(ans, trie::Query(A[i]));
		else trie::Insert(A[i]);
	}
	if (ans == kInf64) ans = 0;
	printf("%lld\n", ans);
	return 0;
}

namespace trie {
	int last;
	int A[kMaxn * 60][2];

	void Insert(LL x) {
		int rt = 0;
		for (int i = 59, b; i >= 0; --i) {
			b = x >> i & 1;
			if (!A[rt][b]) {
				A[rt][b] = ++last;
				// memset(A[last], 0, sizeof A[last]);
			} rt = A[rt][b];
		}
	}
	LL Query(LL x) {
		LL res = 0;
		int rt = 0;
		for (int i = 59, b; i >= 0; --i) {
			b = x >> i & 1;
			if (A[rt][b]) rt = A[rt][b];
			else { res ^= 1ll << i; rt = A[rt][b ^ 1]; }
		}
		return res;
	}
}