#include <cstdio>

typedef long long LL;

const int MOD = 998244353;

int n;
LL C[3005][3005], E[3005];

LL FPow(LL bs, int ex = MOD - 2) {
	LL res = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1)
		if (ex & 1) (res *= bs) %= MOD;
	return res;
}

int main() {
	C[0][0] = 1;
	for (int i = 1; i <= 3000; i++) {
		for (int j = C[i][0] = 1; j <= i; j++)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
	}
	E[1] = 0;
	LL pow2 = 4;
	for (int i = 2; i <= 3000; i++) {
		LL & e = E[i];
		e = 1ll * C[i][2] * FPow(2, i - 1) % MOD;
		for (int j = 1; j < i; j++)
			(e += 1ll * C[i][j] * E[j] % MOD) %= MOD;
		(e *= FPow(pow2 - 1)) %= MOD;
		(pow2 <<= 1) %= MOD;
	}
	for (int i = 1; i <= 3000; i++)
		(E[i] += E[i - 1]) %= MOD;
	for (int i = 1; i <= 3000; i++)
		(E[i] *= FPow(i)) %= MOD;
	while (~scanf("%d", &n)) printf("%lld\n", E[n]);
	return 0;
}
