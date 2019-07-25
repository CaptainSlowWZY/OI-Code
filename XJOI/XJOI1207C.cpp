#include <cstdio>
#include <algorithm>

double DP[505][505];
int n;

int main() {
	scanf("%d", &n);
	
	for (int i = 0; i <= n; i++) DP[n][i] = 1;
	for (int i = n - 1; i >= 0; i--) {
		for (int j = n - 1; j >= 0; j--) {
			double & cur = DP[i][j];
			for (int k = 1, nxt; k <= (n << 1); k <<= 1) {
				nxt = std::min(i + k, n);
				cur = std::max(cur,
					(DP[nxt][j + 1] + DP[nxt][j] + (2 * k - 1) *
					 DP[i][j + 1]) / (double)(2 * k + 1));
			}
		}
	}
	printf("%.6lf\n", DP[0][0]);
	return 0;
}
