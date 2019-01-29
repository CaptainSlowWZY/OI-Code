// BZOJ 1008
#include <cstdio>

const int MOD = 100003;

typedef long long LL;

LL fast_pow(LL bs, LL ex) {
	LL ret = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1)
		if (ex & 1) (ret *= bs) %= MOD;
	return ret;
}

int main() {
	LL N, M;
	scanf("%lld%lld", &M, &N);
	LL ans = M * (fast_pow(M, N - 1) - fast_pow(M - 1, N - 1)) % MOD;
	ans = (ans + MOD) % MOD;
	printf("%lld\n", ans);

	return 0;
}
