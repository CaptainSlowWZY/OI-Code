// nightmare 80pts
#include <algorithm>
// #include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>
// #include <cmath>
#include <map>
#include <queue>
#include <set>
#include <vector>

typedef long long LL;

const int kInf = 0x3f3f3f3f, kMod = 998244353;
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

namespace solver1 {
	void Solve();
}

int n, k;

int main() {
	scanf("%d%d", &n, &k);
	if (k == 2) solver1::Solve();
	return 0;
}

namespace solver1 {
	void Solve() {
		int tn = 1, sn = 1, fn;
		for (int i = 1; i <= n; i++) {
			fn = Mul(Mul(2, Add(Mul(i, sn), tn)), FPow(Mul(i, i)));
			tn = Add(Mul(Mul(i + 4, FPow(i)), tn), fn);
			sn = Add(sn, fn);
		} printf("%d\n", fn);
	}
}