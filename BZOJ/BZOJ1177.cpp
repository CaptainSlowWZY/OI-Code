// BZOJ 1177
// APIO 2009
#include <cstdio>
#include <algorithm>

const int kMaxn = 2005;

typedef long long Map[kMaxn][kMaxn];

int n, m, k;
Map A, lt, rt, lb, rb;

inline long long Calc(int x, int y) {
	return A[x][y] - A[x - k][y] - A[x][y - k] + A[x - k][y - k];
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			scanf("%lld", &A[i][j]);
			A[i][j] += A[i - 1][j] + A[i][j - 1];
			A[i][j] -= A[i - 1][j - 1];
		}

	for (int i = k; i <= n; i++)
		for (int j = k; j <= n; j++) {
			lt[i][j] = std::max(std::max(lt[i - 1][j], lt[i][j - 1]), 
								std::max(lt[i - 1][j - 1], Calc(i, j)));
		}
	for (int i = k; i <= n; i++)
		for (int j = n - k + 1; j > 0; j--) {
			rt[i][j] = std::max(std::max(rt[i - 1][j], rt[i][j + 1]),
								std::max(rt[i - 1][j + 1], Calc(i, j + k - 1)));
		}
	for (int i = n - k + 1; i > 0; i--)
		for (int j = k; j <= n; j++) {
			lb[i][j] = std::max(std::max(lb[i + 1][j], lb[i][j - 1]),
								std::max(lb[i + 1][j - 1], Calc(i + k - 1, j)));
		}
	for (int i = n - k + 1; i > 0; i--)
		for (int j = n - k + 1; j > 0; j--) {
			rb[i][j] = std::max(std::max(rb[i + 1][j], rb[i][j + 1]),
								std::max(rb[i + 1][j + 1], Calc(i + k - 1, j + k - 1)));
		}
	long long ans = 0;
	for (int i = k; i + k <= n; i++)
		for (int j = k; j + k <= n; j++) {
			ans = std::max(ans, lt[i][j] + lb[i + 1][j] + rb[1][j]);
			ans = std::max(ans, lt[i][j] + rt[i][j + 1] + rb[i + 1][1]);
			ans = std::max(ans, lt[n][j] + rt[i][j + 1] + rb[i + 1][j + 1]);
			ans = std::max(ans, lt[i][n] + lb[i + 1][j] + rb[i + 1][j + 1]);
		}
	for (int i = k; i <= n; i++)
		for (int j = 2 * k; j + k <= n; j++) {
			ans = std::max(ans, lt[n][j - k] + Calc(i, j) + rb[1][j + 1]);
			ans = std::max(ans, lt[j - k][n] + Calc(j, i) + rb[j + 1][1]);
		}
	
	printf("%lld\n", ans);
	return 0;
}
