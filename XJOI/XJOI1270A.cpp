// 我觉得qinyuyang说的对
#include <cstdio>

const int kMaxn = 1e6 + 5, kMod = 998244353;

int fac[kMaxn], ifc[kMaxn];

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}
inline int C(int n, int r) {
	return r > n ? 0 : Mul(fac[n], Mul(ifc[r], ifc[n - r]));
}

int main() {
	int N = 1e6 + 3;
	for (int i = fac[0] = 1; i <= N; ++i)
		fac[i] = Mul(fac[i - 1], i);
	ifc[N] = FPow(fac[N]);
	for (int i = N - 1; ~i; --i)
		ifc[i] = Mul(ifc[i + 1], i + 1);
	int T; scanf("%d", &T);
	for (int n, m, lim; T--; ) {
		scanf("%d%d", &n, &m);
		printf("%d\n", C(n + m >> 1, m));
	} return 0;
}
