// math
#include <cstdio>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif

const int MAXN = 155;

int N, DP[MAXN][MAXN][8];

int main() {
#if !defined(LOCAL) && !defined(ONLINE_JUDGE)
	freopen("math.in", "r", stdin);
	freopen("math.out", "w", stdout);
#endif
	scanf("%d", &N);
	for (int Ai, i = 1; i <= N; i++) {
		scanf("%d", &Ai);
		DP[i][i][Ai] = 1;
	}

	for (int i = N - 1; i >= 1; i--)
		for (int j = i + 1; j <= N; j++)
			for (int v = 0; v <= 7; v++) {
				for (int k = i, vv = (v << 1), vv1 = vv + 1; k < j && !DP[i][j][v]; k++)
					for (int v0 = 0; v0 <= v; v0++) {
						debug(" k=%d, v0=%d, vv-v0=%d, vv1-v0=%d\n", k, v0, vv-v0, vv1-v0);
						debug("  [%d, k] == %d ? %d, [k + 1, %d] == %d ? %d, [%d, k] == %d ? %d, [k + 1, %d] == %d ? %d\n", i, v0, DP[i][k][v0], j, vv - v0, DP[k + 1][j][vv - v0], i, vv - v0, DP[i][k][vv - v0], j, v0, DP[k + 1][j][v0]);
						debug("  [%d, k] == %d ? %d, [k + 1, %d] == %d ? %d, [%d, k] == %d ? %d, [k + 1, %d] == %d ? %d\n", i, v0, DP[i][k][v0], j, vv1 - v0, DP[k + 1][j][vv1 - v0], i, vv1 - v0, DP[i][k][vv1 - v0], j, v0, DP[k + 1][j][v0]);
						if (vv - v0 <= 7 && (DP[i][k][v0] && DP[k + 1][j][vv - v0] || DP[i][k][vv - v0] && DP[k + 1][j][v0]) ||
							vv1 - v0 <= 7 && (DP[i][k][v0] && DP[k + 1][j][vv1 - v0] || DP[i][k][vv1 - v0] && DP[k + 1][j][v0]))
						{
							DP[i][j][v] = 1;
							break;
						}
					}
				debug("[%d, %d] == %d ? %d\n", i, j, v, DP[i][j][v]);
			}

	for (int i = 0; i <= 7; i++)
		if (DP[1][N][i]) printf("%d ", i);
	putchar('\n');
#if !defined(LOCAL) && !defined(ONLINE_JUDGE)
	fclose(stdin); fclose(stdout);
#endif
	return 0;
}

// AC!!!
