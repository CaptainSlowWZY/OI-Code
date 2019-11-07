#include <cstdio>

const int kMaxn = 3005, kMod = 998244353;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1) if (ex & 1) res = Mul(res, bs);
	return res;
}

int n, m, B[kMaxn], ifc[kMaxn], fac[kMaxn];

inline int C(int n, int r) { return Mul(fac[n], Mul(ifc[r], ifc[n - r])); }

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) scanf("%d", B + i);
	for (int i = fac[0] = 1; i <= m; ++i) fac[i] = Mul(fac[i - 1], i);
	ifc[m] = FPow(fac[m]);
	for (int i = m - 1; ~i; --i) ifc[i] = Mul(ifc[i + 1], i + 1);
	int ans = 0, u = 1;
	for (int t, i = --m; ~i; --i) {
		if (m - i) for (int j = 0; j < n; ++j) u = Mul(u, B[j] + m - i);
		t = Mul(C(m, i), Mul(u, FPow(ifc[m - i], n)));
		if (i & 1) ans = Sub(ans, t); else ans = Add(ans, t);
	} printf("%d\n", ans); return 0;
}
