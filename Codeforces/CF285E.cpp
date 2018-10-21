// Codeforces 285 E
// Round #175 (Div. 2)
#include <cstdio>
#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
typedef long long LL;
const int MAXN = 1010;
const int MOD = 1e9 + 7;

int DP[MAXN][MAXN][2][2], N, K, fac[MAXN], inv[MAXN];

inline LL C(int n, int r) { return (LL)fac[n] * inv[r] % MOD * inv[n - r] % MOD; }
void add(int & x, int d) { (x += d) %= MOD; }
void init();

int main() {
	scanf("%d%d", &N, &K);
	init();
	DP[0][0][0][0] = 1;
	for (int i = 1; i <= N; i++)
		for (int j = 0; j <= N; j++) {
			add(DP[i][j][0][0], DP[i - 1][j][0][0]);
			add(DP[i][j][0][0], DP[i - 1][j][0][1]);
			add(DP[i][j][0][0], DP[i - 1][j][1][0]);
			add(DP[i][j][0][0], DP[i - 1][j][1][1]);
			if (j >= 1 && i > 1) {
				add(DP[i][j][0][1], DP[i - 1][j - 1][0][0]), add(DP[i][j][0][1], DP[i - 1][j - 1][0][1]);
				add(DP[i][j][1][0], DP[i - 1][j - 1][0][0]), add(DP[i][j][1][0], DP[i - 1][j - 1][1][0]);
			}
			if (j >= 2 && i > 1) add(DP[i][j][1][1], DP[i - 1][j - 2][0][0]);
		}
	int ans = 0;
	for (int i = K; i <= N; i++)
		add(ans, (i - K & 1 ? -1LL : 1LL) * C(i, K) * fac[N - i] % MOD * (((LL)DP[N][i][0][0] + DP[N][i][0][1] + DP[N][i][1][0] + DP[N][i][1][1]) % MOD) % MOD);
	ans = (ans + MOD) % MOD;
	printf("%d\n", ans);
	return 0;
}

LL fast_pow(LL bs, int ex) {
	LL res = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1) if (ex & 1) (res *= bs) %= MOD;
	return res;
}

void init() {
	fac[0] = 1;
	for (LL i = 1; i <= N; i++) fac[i] = i * fac[i - 1] % MOD;
	inv[N] = fast_pow(fac[N], MOD - 2);
	for (LL i = N - 1; i >= 0; i--) inv[i] = (i + 1) * inv[i + 1] % MOD;
}

// AC!!!
