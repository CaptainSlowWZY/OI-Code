#include <cstdio>

typedef long long LL;

const int k1e5 = 1e5, kMaxn = 1e3 + 5, kMod = 1e9 + 7, kInv2 = 5e8 + 4;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upa(int & a, int b) { a = Add(a, b); }
inline void Ups(int & a, int b) { a = Sub(a, b); }
inline void Upm(int & a, int b) { a = Mul(a, b); }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

int tp, ans, F[kMaxn], fac[kMaxn], ifc[kMaxn];
LL n, x, y;

inline int C(int n, int r) { return Mul(fac[n], Mul(ifc[r], ifc[n - r])); }

int main() {
#ifndef LOCAL
	freopen("freshmen.in", "r", stdin);
	freopen("freshmen.out", "w", stdout);
#endif
	scanf("%d%lld%lld%lld", &tp, &n, &x, &y);
	x %= kMod, y %= kMod;
	if (tp == 1) {
		if (y <= k1e5) {
			int l = FPow(y - x + 1);
			for (int p, i = x; i <= y; ++i) { p = i - x; Upa(ans, Mul(i, Sub(FPow(Mul(p + 1, l), n), FPow(Mul(p, l), n)))); }
		} else {
			int u = F[0] = Sub(y, x);
			for (int i = fac[0] = 1; i <= n + 2; ++i) fac[i] = Mul(fac[i - 1], i);
			ifc[n + 2] = FPow(fac[n + 2]);
			for (int i = n + 1; ~i; --i) ifc[i] = Mul(ifc[i + 1], i + 1);
			for (int i = 1; i <= n + 1; ++i) {
				for (int j = 0; j < i; ++j) Upa(F[i], Mul(C(i + 1, j), F[j]));
				F[i] = Mul(Sub(FPow(u + 1, i + 1), Add(1, F[i])), FPow(i + 1));
			} 
			int l = FPow(Add(u, 1));
			ans = x;
			for (int i = 0; i <= n; ++i) Upa(ans, Mul(C(n, i), Add(Mul(x, F[i]), F[i + 1])));
			Ups(ans, Add(Mul(x, F[n]), F[n + 1])); Upm(ans, FPow(l, n));
		}
	} else {
		n %= kMod;
		ans = Add(x, Mul(Mul(n, Sub(y, x)), FPow(n + 1)));
	} printf("%d\n", ans);
#ifndef LOCAL
	fclose(stdin); fclose(stdout);
#endif
	return 0;
}
