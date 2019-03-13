#include <cstdio>
#include <algorithm>

const int kMaxn = 5e5, MOD = 998244353;

typedef long long LL;

int n, m, t;
LL fac[kMaxn * 2 + 10], ifac[kMaxn * 2 + 10];

inline LL C(int n, int r) {
	return fac[n] * ifac[r] % MOD * ifac[n - r] % MOD;
}
LL FastPow(LL bs, int ex = MOD - 2) {
	LL ret = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1)
		if (ex & 1) (ret *= bs) %= MOD;
	return ret;
}

int main() {
	scanf("%d%d", &n, &m);
	t = n + m;
	
	fac[0] = 1;
	for (LL i = 1; i <= t; i++) fac[i] = fac[i - 1] * i % MOD;
	ifac[t] = FastPow(fac[t]);
	for (LL i = t - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

	if (n > m) std::swap(n, m);
	LL sum = 0;
	for (int i = 1; i <= n; i++) {
		(sum += C(i << 1, i) * C(n - i + m - i, m - i) % MOD) %= MOD;
	}
	(sum *= FastPow(2)) %= MOD;
	LL ans = m + sum * FastPow(C(n + m, n)) % MOD;
	(ans += MOD) %= MOD;
	
	printf("%lld\n", ans);
	return 0;
}
