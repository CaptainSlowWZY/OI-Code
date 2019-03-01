#include <cstdio>
#include <algorithm>

const int MOD = 12345678;

int n, m, k, DP[152][152][22][22];

int main() {
	scanf("%d%d%d", &n, &m, &k);

	DP[0][0][0][0] = 1;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			for (int l1 = 0; l1 <= k; l1++)
				for (int l2 = 0; l2 <= k; l2++) {
					if (!DP[i][j][l1][l2]) continue;
					if (i + 1 <= n && l1 + 1 <= k)
						(DP[i + 1][j][l1 + 1][std::max(0, l2 - 1)] += DP[i][j][l1][l2]) %= MOD;
					if (j + 1 <= m && l2 + 1 <= k)
						(DP[i][j + 1][std::max(0, l1 - 1)][l2 + 1] += DP[i][j][l1][l2]) %= MOD;
				}
	int ans = 0;
	for (int i = 0; i <= k; i++)
		for (int j = 0; j <= k; j++)
			(ans += DP[n][m][i][j]) %= MOD;
	printf("%d\n", ans);
	return 0;
}
