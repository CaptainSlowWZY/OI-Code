#include <cstdio>

typedef double Db;

const int kMaxn = 2e3 + 5;

int n, m, r, c, R[kMaxn], C[kMaxn];
Db E[kMaxn][kMaxn];

int main() {
	scanf("%d%d", &n, &m);
	for (int x, y; m--; ) { scanf("%d%d", &x, &y); ++R[x], ++C[y]; }
	for (int i = 1; i <= n; ++i) { r += (bool)R[i]; c += (bool)C[i]; }
	int n2 = n * n;
	for (int i = n; i >= r; --i) {
		for (int j = n; j >= c; --j) {
			if (i == n && j == n) continue;
			Db t = i * (n - j) * E[i][j + 1] + j * (n - i) * E[i + 1][j] + (n - i) * (n - j) * E[i + 1][j + 1];
			E[i][j] = (t + n2) / Db(n2 - i * j);
		}
	} printf("%.10lf\n", E[r][c]); return 0;
}
