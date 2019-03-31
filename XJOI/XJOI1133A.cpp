#include <cstdio>
#include <cassert>

typedef long long LL;

const int MOD = 1e9 + 7;

int n, m, k;
LL fac[305], ifac[305], DP[305][605];

LL FPow(LL bs, int ex = MOD - 2) {
	assert(ex >= 0);
	LL ret = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1) {
		if (ex & 1) (ret *= bs) %= MOD;
	}
	return ret;
}
LL C(int n, int r) {
	assert(r >= 0);
	LL ret = 1;
	for (int i = 0; i < r; i++) (ret *= n - i) %= MOD;
	return ret * ifac[r] % MOD;
}

int main() {
	for (LL i = fac[0] = 1; i <= 300; i++) {
		fac[i] = i * fac[i - 1] % MOD;
	}
	ifac[300] = FPow(fac[300]);
	for (LL i = 299; i >= 0; i--) {
		ifac[i] = ifac[i + 1] * (i + 1) % MOD;
	}

	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d%d%d", &n, &m, &k);
		n -= m;
		DP[0][0] = 1;
		for (int i = 1; i <= k; i++) {
			for (int j = i; j <= k; j++) {
				DP[i][j] = (DP[i - 1][j - 1] << 1) % MOD;
				if (j - 2 >= i - 1) (DP[i][j] += DP[i - 1][j - 2]) %= MOD;
			}
		}

		LL ans = 0;
		for (int i = 0; i <= k; i++) {
			LL cur = 0;
			for (int j = 0; j <= i && j <= m; j++) {
				(cur += DP[j][i] * C(m, j) % MOD *
				 FPow(2, m - j) % MOD) %= MOD;
			}
			(ans += cur * C(n, k - i) % MOD) %= MOD;
		}

		printf("%lld\n", ans);
	}
	return 0;
}
