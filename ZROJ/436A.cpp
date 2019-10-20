#include <cstdio>

int n, A[100010];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d", A + i);
	double ans = 1;
	for (int i = 1; i < n; ++i)
		ans += (double)A[i] / (A[i] + A[0]);
	printf("%.10lf\n", ans);
	return 0;
}
