#include <cstdio>
#include <cassert>

const int kMaxn = 225;

int n, r, D[kMaxn];
double P[kMaxn], DP[kMaxn][kMaxn];

double FPow(double bs, int ex) {
	assert(ex >= 0);
	double ret = 1;
	for (; ex; bs *= bs, ex >>= 1)
		if (ex & 1) ret *= bs;
	return ret;
}

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d%d", &n, &r);
		for (int i = 1; i <= n; i++) {
			scanf("%lf%d", P + i, D + i);
			P[i] = 1 - P[i];
		}

		DP[0][0] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= i && j <= r; j++) {
				DP[i][j] = 0;
				if (j) {
					DP[i][j] += (1 - FPow(P[i], r - j + 1)) * DP[i - 1][j - 1];
				}
				if (j < i) {
					DP[i][j] += FPow(P[i], r - j) * DP[i - 1][j];
				}
			}
		}

		double ans = 0;
		for (int i = 1; i <= n; i++) {
			double p = 0;
			for (int j = 0; j < i && j <= r; j++) {
				p += DP[i - 1][j] * (1 - FPow(P[i], r - j));
			}
			ans += p * D[i];
		}
		printf("%.10lf\n", ans);
	}
	return 0;
}
