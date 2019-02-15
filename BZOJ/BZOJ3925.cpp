// BZOJ 3925
// ZJOI 2015
#include <cstdio>

const int MAXU = (1 << 10) + 10;

int N, M, U, A[12][12], cnt[MAXU];
long long C[50][50], F[MAXU][50], G[MAXU][50];

int main() {
	scanf("%d%d", &N, &M);
	U = 1 << N;
	for (int i = 0, u, v; i < M; i++) {
		scanf("%d%d", &u, &v);
		--u, --v;
		A[u][v] = A[v][u] = 1;
	}

	C[0][0] = 1;
	for (int i = 1; i <= 45; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
	}

	for (int S = 1; S < U; S++) {
		for (int i = 0; i < N; i++)
			if (S >> i & 1) {
				cnt[S] = cnt[S ^ 1 << i];
				for (int j = i + 1; j < N; j++)
					if (S >> j & 1) cnt[S] += A[i][j];
				break;
			}
		int u = S & -S;
		for (int T = (S - 1) & S; T; T = (T - 1) & S) {
			if (!(T & u)) continue;
			for (int i = 0; i <= cnt[T]; i++)
				for (int j = 0; j <= cnt[S ^ T]; j++)
					F[S][i + j] += G[T][i] * C[cnt[S ^ T]][j];
		}
		for (int i = 0; i <= cnt[S]; i++) G[S][i] = C[cnt[S]][i] - F[S][i];
	}

	double ans = 0;
	for (int i = 0; i < M; i++) ans += (double)F[U - 1][i] / C[cnt[U - 1]][i];
	ans /= M + 1.0;
	printf("%.6lf\n", ans);
	return 0;
}
