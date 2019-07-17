#include <algorithm>
#include <cstdio>

const int kMaxn = 2005, kInf = 0x3fffffff;
int n;
int sum[kMaxn], DP[kMaxn][kMaxn], P[kMaxn][kMaxn];

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++) {
			scanf("%d", sum + i);
			sum[n + i] = sum[i];
			DP[i][i] = DP[n + i][n + i] = 0;
			P[i][i] = i, P[n + i][n + i] = n + i;
		}

		for (int i = 1; i <= n * 2; i++) sum[i] += sum[i - 1];
		for (int i = 2; i <= n; i++) {
			for (int l = 1, r = i; r <= n * 2; l++, r++) {
				DP[l][r] = kInf;
				for (int k = P[l][r - 1];
						k <= P[l + 1][r] && k < r; k++) {
					if (DP[l][k] + DP[k + 1][r] < DP[l][r]) {
						DP[l][r] = DP[l][k] + DP[k + 1][r];
						P[l][r] = k;
					}
				}
				DP[l][r] += sum[r] - sum[l - 1];
			}
		}
		int ans = kInf;
		for (int i = 1; i <= n; i++) {
			ans = std::min(ans, DP[i][i + n - 1]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
