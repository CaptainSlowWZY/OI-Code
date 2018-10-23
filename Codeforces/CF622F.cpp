// Codeforces 622 F
// Edu Round 7
#include <cstdio>
#include <iostream>

typedef long long LL;

const int MOD = 1e9 + 7;
const int MAXK = 1e6 + 15;
const int INIT_LIM = MAXK - 5;

int fac[MAXK], inv[MAXK], N, K;

inline void add(LL &x, LL d) { (x += d) %= MOD; }
LL fast_pow(LL bs, int ex) {
	LL res = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1) if (ex & 1) (res *= bs) %= MOD;
	return res;
}
void init();

int main() {
	init();

	scanf("%d%d", &N, &K);

	if (N <= K + 2) {
		LL ans = 1;
		for (int i = 2; i <= N; i++) add(ans, fast_pow(i, K));
		std::cout << ans << std::endl;
		return 0;
	}
	LL prd1 = 1, ans = 0, yi = 0;
	for (LL i = N - K - 2; i < N; i++) (prd1 *= i) %= MOD;
	for (int i = 1; i <= K + 2; i++) {
		add(yi, fast_pow(i, K));
		LL tmp1 = prd1 * fast_pow(N - i, MOD - 2) % MOD, tmp2 = (LL)inv[i - 1] * inv[K + 2 - i] % MOD;
		add(ans, (K + 2 - i & 1 ? -1LL : 1LL) * (tmp1 * tmp2 % MOD * yi % MOD));
	}
	ans = (ans + MOD) % MOD;
	std::cout << ans << std::endl;
	return 0;
}

void init() {
	fac[0] = 1;
	for (LL i = 1; i <= INIT_LIM; i++) fac[i] = i * fac[i - 1] % MOD;
	inv[INIT_LIM] = fast_pow(fac[INIT_LIM], MOD - 2);
	for (LL i = INIT_LIM - 1; i >= 0; i--) inv[i] = (i + 1) * inv[i + 1] % MOD;
}

// AC!!!