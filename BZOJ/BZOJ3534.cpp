// BZOJ 3534
// SDOI 2014
#include <cstdio>
#include <cmath>
#include <algorithm>

const double EPS = 1e-8;

int N;
double A[55][55];

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) scanf("%lf", &A[i][j]);

	double prd = 1;
	for (int i = 0; i < N; i++) {
		A[i][i] = 0;
		for (int j = 0; j < N; j++) {
			if (i == j) continue;
			if (fabs(A[i][j]) < EPS) A[i][j] = EPS;
			if (fabs(1.0 - A[i][j]) < EPS) A[i][j] = 1 - EPS;
			if (i < j) prd *= 1 - A[i][j];
			A[i][j] = A[i][j] / (1.0 - A[i][j]);
			A[i][i] -= A[i][j];
		}
	}

	--N;
	double ans = 1;
	for (int i = 0; i < N; i++) {
		int r = i;
		for (int j = i + 1; j < N; j++)
			if (fabs(A[j][i]) > fabs(A[r][i])) r = j;
		if (fabs(A[r][i]) < EPS) {
			ans = 0;
			break;
		}
		if (r != i) {
			for (int j = i; j < N; j++) std::swap(A[i][j], A[r][j]);
		}
		for (int j = N - 1; j >= i; j--)
			for (int k = i + 1; k < N; k++)
				A[k][j] -= A[k][i] / A[i][i] * A[i][j];
	}
	for (int i = 0; i < N; i++) ans *= A[i][i];
	ans *= prd;

	printf("%lf\n", fabs(ans));
	return 0;
}
