#include <cstdio>

int n, U;
double P[(1 << 20) + 5];

int main() {
	scanf("%d", &n);
	U = 1 << n;
	for (int i = 0; i < U; ++i) scanf("%lf", P + i);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < U; ++j)
			if (j >> i & 1) P[j] += P[j ^ 1 << i];
	double ans = 0;
	for (int s = 1; s < U; ++s) {
		double tmp = 1.0 - P[U - 1 ^ s];
		if (tmp < 1e-8) { puts("INF"); return 0; }
		ans += (__builtin_popcount(s) & 1 ? 1.0 : -1.0) / tmp;
	}
	printf("%.10lf\n", ans);
	return 0;
}

