#include <cstdio>

int n, A[40][40];

int main() {
	scanf("%d", &n);
	A[0][n >> 1] = 1;
	int x = 0, y = n >> 1;
	for (int k = 2; k <= n * n; k++) {
		if (!x && y + 1 < n) {
			A[x = n - 1][++y] = k;
		} else if (y + 1 == n && x) {
			A[--x][y = 0] = k;
		} else if (!x && y + 1 == n || A[x - 1][y + 1]) {
			A[++x][y] = k;
		} else {
			A[--x][++y] = k;
		} // printf(" %d at (%d, %d)\n", k, x, y);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) printf("%d ", A[i][j]);
		putchar('\n');
	} return 0;
}
