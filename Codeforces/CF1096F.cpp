#include <cstdio>

const int kMaxn = 2e5 + 5, kMod = 998244353;

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

int n, sum[kMaxn], P[kMaxn], cnt[kMaxn], fac[kMaxn];

namespace bit {
	int T[kMaxn];
	void Add(int p) { for (; p <= n; p += p & -p) ++T[p]; }
	int Sum(int p) { int r = 0; for (; p; p &= p - 1) r += T[p]; return r; }
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", P + i); sum[i] = sum[i - 1] + (P[i] == -1);
		if (~P[i]) cnt[P[i]] = 1;
	}
	for (int i = fac[0] = 1; i <= n; ++i) { cnt[i] += cnt[i - 1]; fac[i] = Mul(fac[i - 1], i); }
	int ans = 0;
	for (int i = 1; i <= n; ++i) if (~P[i])
		Upa(ans, Mul(fac[sum[n] - 1], Add(Mul(sum[i], n - P[i] - cnt[n] + cnt[P[i]]), Mul(sum[n] - sum[i], P[i] - cnt[P[i]]))));
	Upm(ans, FPow(fac[sum[n]])); Upa(ans, Mul(Mul(sum[n], sum[n] - 1), FPow(4)));
	for (int i = 1; i <= n; ++i) if (~P[i]) { Upa(ans, i - 1 - sum[i] - bit::Sum(P[i])); bit::Add(P[i]); }
	printf("%d\n", ans); return 0;
}
