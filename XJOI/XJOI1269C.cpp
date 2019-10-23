#include <cstdio>

const int kMod = 1e9 + 7;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}
inline void Upd(int & a, int b) { a = Add(a, b); }

const int kMaxn = 1e6 + 6;

int n, y, x;
int fac[kMaxn << 1], ifc[kMaxn << 1];

inline int C(int n, int r) {
	return Mul(fac[n], Mul(ifc[r], ifc[n - r]));
}
inline int Catlan(int n) {
	return Sub(C(n << 1, n), C(n << 1, n + 1));
}
inline int Walk(int x, int y) {
	return Sub(C(x + y, x), C(x + y, y + 1));
}

int main() {
	scanf("%d%d%d", &n, &x, &y);
	int m = n << 1;
	for (int i = fac[0] = 1; i <= m; ++i)
		fac[i] = Mul(fac[i - 1], i);
	ifc[m] = FPow(fac[m]);
	for (int i = m - 1; i >= 0; --i)
		ifc[i] = Mul(ifc[i + 1], i + 1);
	int ans = 0;
	for (int b, i = 0; i < x; ++i) {	
		b = y - i - 1;
		if (b < 0 || n - b - x < 0 || n - y < 0)
			continue;
		Upd(ans, Mul(Walk(i, x - 1),
			Mul(Catlan(b), Walk(n - b - x, n - y))));
	} printf("%d\n", ans);
	return 0;
}
