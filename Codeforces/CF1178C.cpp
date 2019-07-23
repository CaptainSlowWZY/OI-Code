#include <cstdio>

const int MOD = 998244353;

long long FPow(long long bs, int ex) {
	long long res = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1)
		if (ex & 1) (res *= bs) %= MOD;
	return res;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	printf("%lld\n", FPow(2, n + m));
	return 0;
}
