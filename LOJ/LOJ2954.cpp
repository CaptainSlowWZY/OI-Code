#include <algorithm>
#include <cstdio>

const int kMod = 1e9 + 7;
const int kTab[9][2] = {{0, 0}, {0, 0}, {0, 0}, {112, 336}, {912, 2688}, {7136, 21312}, {56768, 170112}, {453504, 1360128}, {3626752, 10879488}};

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1) if (ex & 1) res = Mul(res, bs);
	return res;
}

int n, m;

namespace solver1 { void Solve(); }
namespace solver2 { void Solve(); }
namespace solver3 { void Solve(); }

int main() {
#ifndef LOCAL
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	if (n > m) std::swap(n, m);
	if (n == 2) solver2::Solve();
	else if (n <= 3 && m <= 3) solver1::Solve();
	else solver3::Solve();
	return 0;
}

namespace solver1 {
	void Solve() {
		if (n == 1) printf("%d\n", FPow(2, m));
		if (n == 3) puts("112");
	}
}

namespace solver2 {
	void Solve() {
		printf("%d\n", Mul(4, FPow(3, m - 1)));
	}
}

namespace solver3 {
	void Solve() {
		if (n == m) printf("%d\n", kTab[n][0]);
		else printf("%d\n", Mul(kTab[n][1], FPow(3, m - n - 1)));
	}
}
