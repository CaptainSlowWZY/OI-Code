#include <cstdio>

const int kMod = 998244353;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}
inline void Upd(int & a, int b) { a = Add(a, b); }

const int kMaxn = 1e5 + 5;

int n;
char S[kMaxn];

namespace solver2 {
	void Solve();
}

int main() {
	scanf("%d%s", &n, S);
//	solver1::Solve();
	solver2::Solve();
	return 0;
}

namespace solver2 {
	int ifc[kMaxn << 1], fac[kMaxn << 1];

	inline int C(int n, int r) {
		return Mul(fac[n], Mul(ifc[r], ifc[n - r]));
	}
	inline int Catalan(int n) {
		return Sub(C(n << 1, n), C(n << 1, n + 1));
	}
	void Solve() {
		for (int i = fac[0] = 1; i <= 2 * n; ++i)
			fac[i] = Mul(fac[i - 1], i);
		ifc[n * 2] = FPow(fac[n * 2]);
		for (int i = n * 2 - 1; i >= 0; --i)
		   ifc[i] = Mul(ifc[i + 1], i + 1);
		int la = 0, len = 1, ans = 1;
		for (int i = 1; i <= n; ++i) {
			if (S[i] == S[la]) ++len;
			else {
				ans = Mul(ans, Catalan(len));
				la = i, len = 1;
			}
		} printf("%d\n", ans);
	}
}
