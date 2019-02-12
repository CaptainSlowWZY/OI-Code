#include <cstdio>

typedef long long LL;

const int ARSZ = 105, MOD = 9999973;

int DP[ARSZ][ARSZ][ARSZ], N, M;

inline LL C2(int x) {
	return x * LL(x - 1) / 2;
}
inline void add(int &x, int y) { (x += y) %= MOD; }

int main() {
	scanf("%d%d", &N, &M);
	
	DP[0][0][0] = 1;
	for (int i = 1; i <= N; i++)
		for (int j = 0; j <= M; j++)
			for (int k = 0; j + k <= M; k++) {
				DP[i][j][k] = DP[i - 1][j][k];
			//	put one
			//	on the column that already have one
				if (k) add(DP[i][j][k], DP[i - 1][j + 1][k - 1] * LL(j + 1) % MOD);
			//	on a empty column
				if (j) add(DP[i][j][k], DP[i - 1][j - 1][k] * LL(M - j + 1 - k) % MOD);
			//	put two
			//	all on the column that already have one
				if (k > 1) add(DP[i][j][k], DP[i - 1][j + 2][k - 2] * C2(j + 2) % MOD);
			//	all on empty columns
				if (j > 1) add(DP[i][j][k], DP[i - 1][j - 2][k] * C2(M - j + 2 - k) % MOD);
			//	one-one
				if (k) add(DP[i][j][k], DP[i - 1][j][k - 1] * LL((M - j - k + 1) * j % MOD) % MOD);
			}
	int ans = 0;
	for (int i = 0; i <= M; i++)
		for (int j = 0; i + j <= M; j++)
			add(ans, DP[N][i][j]);
	ans = (ans % MOD + MOD) % MOD;

	printf("%d\n", ans);
	return 0;
}
