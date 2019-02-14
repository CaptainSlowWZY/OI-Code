// BZOJ 1076
// SCOI 2008
#include <cstdio>
#include <algorithm>

int K, N, P[20], T[20];
double DP[105][33000];

int main() {
	scanf("%d%d", &K, &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", P + i);
		for (int v; scanf("%d", &v) == 1 && v; ) T[i] |= 1 << v - 1;
	}

	for (int i = K; i > 0; i--)
		for (int mask = (1 << N) - 1; mask >= 0; --mask) {
			for (int j = 0; j < N; j++) {
				if ((mask & T[j]) != T[j]) DP[i][mask] += DP[i + 1][mask];
				else DP[i][mask] += std::max(DP[i + 1][mask], DP[i + 1][mask | 1 << j] + P[j]);
			}
			DP[i][mask] /= N;
		}
	printf("%.6lf\n", DP[1][0]);
	return 0;
}
