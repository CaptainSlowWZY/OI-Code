// CF340 E
#include <cstdio>
#include <iostream>
typedef long long LL;
const int MAXN = 2010;
const int MOD = 1e9 + 7;

int N, cntfr, cntlm, num[MAXN], flag[MAXN], fac[MAXN], inv[MAXN];

namespace FastIO {
	template <typename T>
		void read(T & x) {
			x = 0; register char ch = getchar(); register int f = 0;
			for (; ch < '0' || ch > '9'; f |= ch == '-', ch = getchar());
			for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
			if (f) x = ~x + 1;
		}
}
LL fast_pow(LL bs, int ex) {
	LL res = 1;
	for (; ex;(bs *= bs) %= MOD, ex >>= 1) if (ex & 1) (res *= bs) %= MOD;
	return res;
}
inline LL get_inv(LL x) { return fast_pow(x, MOD - 2); }
inline LL C(int n, int r) { return (LL)fac[n] * inv[r] % MOD * inv[n - r] % MOD; }
inline void add(int & x, int d) { x = ((x + d) % MOD + MOD) % MOD; }
void init() {
	fac[0] = 1;
	for (LL i = 1; i <= N; i++) fac[i] = i * fac[i - 1] % MOD;
	inv[N] = get_inv(fac[N]);
	for (LL i = N - 1; i >= 0; i--) inv[i] = (i + 1) * inv[i + 1] % MOD;
}

int main() {
	using FastIO::read;
	read(N);
	for (int i = 1, ai; i <= N; i++) {
		scanf("%d", &ai);
		if (~ai) num[i] = ai, flag[ai] = 1;
	}
	init();
	for (int i = 1; i <= N; i++)
		if (!flag[i]) {
			if (num[i]) ++cntfr;
			else ++cntlm;
		}
	int ans = 0;
	for (int i = 0; i <= cntlm; i++)
		add(ans, (i & 1 ? -1LL : 1LL) * C(cntlm, i) * fac[cntfr + cntlm - i] % MOD);
	std::cout << ans << std::endl;
	return 0;
}
