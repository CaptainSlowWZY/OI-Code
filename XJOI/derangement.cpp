// derangement
#include <cstdio>
#include <algorithm>

#ifdef LOCAL 
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...)
#endif

typedef long long LL;

const int MAXN = 5010;
const int MOD = 1e9 + 9;

int N, p[MAXN], DP[MAXN][MAXN];

namespace FastIO {
	template <typename T>
		void read(T & x) {
			x = 0; register char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
}
LL fast_pow(LL bs, int ex) {
	LL res = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1) if (ex & 1) (res *= bs) %= MOD;
	return res;
}
template <typename T1, typename T2>
inline void add(T1 & x, T2 d) { (x += d) %= MOD; }

int main() {
/*
#if !defined(LOCAL) && !defined(ONLINE_JUDGE)
	freopen("derangement.in", "r", stdin);
	freopen("derangement.out", "w", stdout);
#endif
*/
	using FastIO::read;

	read(N);
	for (int i = 1, pi; i <= N; i++) read(pi), p[pi] = i;

#ifdef _DEBUG_MD_
	for (int i = 1; i <= N; i++) debug("%d%c", p[i], i == N ? '\n' : ' ' );
#endif

	DP[0][0] = 1;
	for (int i = 1; i <= N; i++) {
		if (i > 0) add(DP[i][0], (LL)(i - 1) * DP[i - 1][0] % MOD);
		if (i > 1) add(DP[i][0], (LL)(i - 1) * DP[i - 2][0] % MOD);
	}
	DP[0][1] = 1, DP[0][2] = 2;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= 2; j++) {
			if (i > 0) add(DP[i][j], (LL)i * DP[i - 1][j] % MOD);
			add(DP[i][j], (LL)j * DP[i][j - 1] % MOD);
		}
	LL inv2 = fast_pow(2, MOD - 2);

	LL ans = 0;
	LL s1 = 0;
	for (int i = 1; i < N; i++) add(s1, (LL)(N - i) * i);
	debug("s1=%lld\n", s1);
	for (int i = 1; i < N; i++)
		for (int j = i + 1; j <= N; j++) {
			LL c1 = std::max(0, p[j] - p[i]);
			LL c2 = (((LL)(p[j] - 1) * p[j] % MOD + (LL)(N - p[i] + 1) * (N - p[i]) % MOD) * inv2 % MOD - 2LL * c1 % MOD) % MOD;
			LL c3 = (s1 - c1 - c2 - ((LL)(p[i] - 1) * p[i] % MOD + (LL)(N - p[j] + 1) * (N - p[j]) % MOD) % MOD * inv2 % MOD + std::max(0, p[i] - p[j])) % MOD;
			debug("i=%d, j=%d, c1=%lld, c2=%lld, c3=%lld\n", i, j, c1, c2, c3);
			add(ans, (LL)(j - i) * ((N > 1 ? c1 * DP[N - 2][0] % MOD : 0) + (N > 2 ? c2 * DP[N - 3][1] % MOD : 0) + (N > 3 ? c3 * DP[N - 4][2] % MOD : 0)) % MOD);
		}
	ans = (ans + MOD) % MOD;
	printf("%lld\n", ans);

/*
#if !defined(LOCAL) && !defined(ONLINE_JUDGE)
	fclose(stdin); fclose(stdout);
#endif
*/
	return 0;
}
