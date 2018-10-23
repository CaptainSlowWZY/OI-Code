// Codeforces 408 E
// Round #239 (Div. 2)
#include <cstdio>

#ifdef LOCAL
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...)
#endif

typedef long long LL;
const int MAXN = 1e5 + 10;
const int MAXK = 110;
const int MOD = 1e9 + 7;

int N, M, D[MAXK][MAXN], fac[MAXN + MAXK], inv[MAXN + MAXK];

namespace FastIO {
	template <typename T>
		void read(T & x) {
			register char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (x = 0; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
}
inline void add(int & x, int d) { (x += d) %= MOD; }
inline int C(int n, int r) { return (LL)fac[n] * inv[r] % MOD * inv[n - r] % MOD; }
void init();

int main() {
	init();
	using FastIO::read;

	read(N), read(M);
	for (int i = 1; i <= N; i++) read(D[0][i]);
	
	for (int li, ri, ki; M--; ) {
	   read(li), read(ri), read(ki);	   
	   add(D[ki + 1][li], 1);
	   for (int i = ki + 1; i > 0; i--) add(D[i][ri + 1], -C(ri - li + ki + 1 - i, ki + 1 - i));
	}

	for (int i = 1; i <= N; i++) add(D[101][i], D[101][i - 1]);
	for (int i = 100; i >= 0; i--) {
		for (int j = 1; j <= N; j++) add(D[i][j], D[i + 1][j]);
		if (i > 0)
			for (int j = 1; j <= N; j++) add(D[i][j], D[i][j - 1]);
	}
	
	for (int i = 1; i <= N; i++) printf("%d ", (D[0][i] + MOD) % MOD);
	putchar('\n');

	return 0;
}

LL fast_pow(LL bs, int ex) {
	LL res = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1) if (ex & 1) (res *= bs) %= MOD;
	return res;
}

void init() {
	fac[0] = 1;
	for (LL i = 1; i <= 100115; i++) fac[i] = i * fac[i - 1] % MOD;
	inv[100115] = fast_pow(fac[100115], MOD - 2);
	for (LL i = 100114; i >= 0; i--) inv[i] = (i + 1) * inv[i + 1] % MOD;
}
