// BZOJ 1011
// HNOI 2008
#include <cstdio>
double A, M[(int)1e5 + 10], sum[(int)1e5 + 10];
int N;
int main() {
	scanf("%d%lf", &N, &A);
	for (int i = 1; i <= N; i++) {
		scanf("%lf", M + i);
		sum[i] = sum[i - 1] + M[i];
		int lim = i * A + 1e-8;
		if (lim > 2000) printf("%f\n", M[i] * sum[lim] / (i - lim * 0.5));
		else {
			double ans = 0;
			for (int j = 1; j <= lim; j++) ans += M[i] * M[j] / double(i - j);
			printf("%f\n", ans);
		}
	}
	return 0;
}
