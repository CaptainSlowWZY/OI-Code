#include <cstdio>

typedef long double Db;

const int kN = 2505;

int n, k;
Db X[kN << 1], Y[kN << 1], C[kN][kN];

inline Db Crs(Db x1, Db y1, Db x2, Db y2) {
	return x1 * y2 - x2 * y1;
}
inline Db Area(int i, int j, int k) {
	return Crs(X[k] - X[i], Y[k] - Y[i], X[j] - X[i], Y[j] - Y[i]) / 2.0;
}

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; ++i) {
		scanf("%Lf%Lf", X + i, Y + i);
		X[n + i] = X[i], Y[n + i] = Y[i];
	}
/*	for (int i = n - k + 2, nn; i; --i) {
		P[i] = 1, nn = n - i;
		for (int j = 0; j < k; ++j) {
			P[i] = P[i] / (n - j) * (j + 1);
			if (j < k - 2) P[i] = P[i] / (nn - j) * (j + 1);
		}
	} */
	C[0][0] = 1;
	for (int i = 1; i <= n; ++i) {	
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
	}
	Db ans = 0;
	for (int i = 2; i < n; ++i) ans += Area(0, i - 1, i);
//	printf(" ans %.10lf\n", ans);
	for (int i = 0; i < n; ++i) {
		Db S = 0;
		for (int j = i + 2; j < n * 2; ++j) {
			if (n - j + i - 1 < k - 2) break;
			S += Area(i, j - 1, j);
		//	printf(" n - (j - i + 1) = %d\n", n - j + i - 1);
		//	printf(" choose %d & %d, P %.5lf, S = %.5lf\n", i, j, C[n - j + i - 1][k - 2] / C[n][k], S);
			ans -= C[n - j + i - 1][k - 2] / C[n][k] * S;
		//	ans -= P[j - i - 1] * S;
		}
	} printf("%.10Lf\n", ans);
	return 0;
}

