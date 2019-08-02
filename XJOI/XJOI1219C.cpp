#include <cstdio>

const int kMod = 1e8 + 7;

int n, DP[2005][2005];

int main() {
	DP[0][0] = 1;
	for (int i = 2; i <= 2000; i++) {
		for (int j = 2; j <= 2000; j++) {
			if (j > i) DP[i][j] = DP[i][i];
			else if (i == j) DP[i][j] = (DP[i][j - 1] + 1) % kMod;
			else DP[i][j] = (DP[i - j][j] + DP[i][j - 1]) % kMod;
		}
	}
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d", &n);
		printf("%d\n", DP[n][n]);
	} return 0;
}
