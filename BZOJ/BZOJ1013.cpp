// BZOJ 1013
// JSOI 2008
#include <cstdio>
#include <cmath>
#include <algorithm>

int N;
double P[15], A[15][15];

inline double sqr(double x) { return x * x; }
void gauss();

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%lf", P + i); 
	for (int i = 0; i < N; i++) {
		double xi;
		for (int j = 0; j < N; j++) {
			scanf("%lf", &xi);
			A[i][j] = 2 * (xi - P[j]);
			A[i][N] += sqr(xi) - sqr(P[j]);
		}
	}

	gauss();

	for (int i = 0; i < N; i++) printf("%.3lf ", A[i][N]);
	putchar('\n');
	return 0;
}

void gauss() {
	for (int i = 0; i < N; i++) {
		int r = i;
		for (int j = i + 1; j < N; j++)
			if (fabs(A[j][i]) > fabs(A[r][i])) r = j;
		if (r ^ i) {
			for (int j = i; j <= N; j++)
				std::swap(A[i][j], A[r][j]);
		}

		for (int j = N; j >= i; j--)
			for (int k = i + 1; k < N; k++)
				A[k][j] -= A[k][i] / A[i][i] * A[i][j];
	}
	for (int i = N - 1; i >= 0; i--) {
		for (int j = i + 1; j < N; j++)
			A[i][N] -= A[i][j] * A[j][N];
		A[i][N] /= A[i][i];
	}
}
