// inverse
#include <cstdio>

#ifdef DEBUG_MD 
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...)
#endif

const int INIT = 1e7 + 5;
const int MAXN = INIT + 5;
const int MOD = 998244353;

typedef long long LL;
typedef int IntAr[MAXN];

IntAr DP, fac, inv;

namespace FastIO {
	template <typename T>
		void read(T & x);
	template <typename T>
		void write(T x);
	template <typename T>
		inline void writeln(T x) {
			write(x), putchar('\n');
		}
}
void init();

int main() {
#if !defined(LOCAL) && !defined(ONLINE_JUDGE)
	freopen("inverse.in", "r", stdin);
	freopen("inverse.out", "w", stdout);
#endif
	init();
	using FastIO::read;

	int t, N;
	for (read(t); t--; ) {
		read(N);
		debug("DP[%d]=%d, (%d)!^(-1)=%d\n", N, DP[N], N, inv[N]);
		FastIO::writeln((LL)DP[N] * inv[N] % MOD);
	}

#if !defined(LOCAL) && !defined(ONLINE_JUDGE)
	fclose(stdin); fclose(stdout);
#endif
	return 0;
}

LL fast_pow(LL bs, int ex) {
	LL res = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1) if (ex & 1) (res *= bs) %= MOD;
	return res;
}

inline LL get_inv(LL x) { return fast_pow(x, MOD - 2); }

void init() {
	DP[1] = 0, fac[1] = 1;
	for (LL i = 2; i <= INIT; i++) {
		DP[i] = (i * DP[i - 1] % MOD + (i - 1) * fac[i - 1]) % MOD;
		fac[i] = i * fac[i - 1] % MOD;
	}
	inv[INIT] = get_inv(fac[INIT]);
	for (LL i = INIT - 1; i > 0; i--) inv[i] = (i + 1) * inv[i + 1] % MOD;
}

namespace FastIO {
	template <typename T>
		void read(T & x) {
			register char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (x = 0; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
	template <typename T>
		void write(T x) {
			if (!x) return (void)putchar('0');
			if (x < 0) x = -x, putchar('-');
			int arr[20], len = 0;
			for (; x; x /= 10) arr[len++] = x % 10;
			while (len) putchar(arr[--len] ^ '0');
		}
}
