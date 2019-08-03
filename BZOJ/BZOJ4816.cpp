#include <algorithm>
#include <cstdio>

const int kMaxn = 1e6, kMod = 1e9 + 7;

typedef long long LL;
typedef int IAr[kMaxn + 10];

int n, m, totp;
IAr fib, fiv, smu, P, np;

LL S(int n, int m);
LL FPow(LL bs, int ex = kMod - 2) {
	LL res = 1;
	for (; ex; (bs *= bs) %= kMod, ex >>= 1) {
		if (ex & 1) (res *= bs) %= kMod;
	} return res;
}

int main() {
	fib[0] = 0, fiv[0] = fib[1] = fiv[1] = smu[1] = 1;
	for (int i = 2; i <= kMaxn; i++) {
		fib[i] = (fib[i - 1] + fib[i - 2]) % kMod;
		if (!np[i]) { P[totp++] = i, smu[i] = -1; }
		for (int j = 0, d; j < totp && (d = i * P[j]) <= kMaxn; j++) {
			np[d] = 1;
			if (i % P[j] == 0) { smu[d] = 0; break; }
			smu[d] = -smu[i];
		} smu[i] += smu[i - 1];
	}
	for (int i = 2; i <= kMaxn; i++) {
		fib[i] = 1ll * fib[i] * fib[i - 1] % kMod;
		fiv[i] = FPow(fib[i]);
	}
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d%d", &n, &m);
		if (n > m) std::swap(n, m);
		LL ans = 1;
		for (int i = 1, j; i <= n; i = j + 1) {
			j = std::min(n / (n / i), m / (m / i));
		//	printf(" [%d, %d] mulfib = %lld\n", i, j, 1ll * fib[j] * fiv[i - 1] % kMod);
			(ans *=	FPow(1ll * fib[j] * fiv[i - 1] % kMod,
						 S(n / i, m / i)) % kMod) %= kMod;
		} printf("%lld\n", ans);
	} return 0;
}

LL S(int n, int m) {
	LL res = 0, mod = kMod - 1;
//	printf("  S[%d, %d]\n", n, m);
	for (int i = 1, j; i <= n; i = j + 1) {
		j = std::min(n / (n / i), m / (m / i));
	//	printf("   [%d, %d]\n", i, j);
		res += 1ll * (smu[j] - smu[i - 1]) * (n / i) * (m / i);
	} return res > mod ? res % mod + mod : res;
}
