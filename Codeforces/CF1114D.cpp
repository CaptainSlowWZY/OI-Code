#include <bits/stdc++.h>

const int MAXN = 5005;
int N, A[MAXN], DP[MAXN][MAXN][2];

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d", A + i);

	N = std::unique(A, A + N) - A;
	using std::min;
	for (int i = 0; i < N; i++) DP[i][i][0] = DP[i][i][1] = 0;
	for (int t = 1; t < N; t++)
		for (int i = 0, j; i + t < N; i++) {
			j = i + t;
			DP[i][j][0] = min(	min(DP[i + 1][j][0] + (A[i + 1] == A[i] ? 0 : 1),
									DP[i + 1][j][1] + (A[j] == A[i] ? 0 : 1)),
								min(DP[i][j - 1][0] + (A[i] == A[j] ? 0 : 2),
									DP[i][j - 1][1] + (A[i] == A[j] ? 0 : 1) + (A[j] == A[j - 1] ? 0 : 1)));
			DP[i][j][1] = min(	min(DP[i + 1][j][0] + (A[i + 1] == A[i] ? 0 : 1) + (A[i] == A[j] ? 0 : 1),
									DP[i + 1][j][1] + (A[i] == A[j] ? 0 : 2)),
								min(DP[i][j - 1][0] + (A[i] == A[j] ? 0 : 1),
									DP[i][j - 1][1] + (A[j] == A[j - 1] ? 0 : 1)));
		}
	printf("%d\n", min(DP[0][N - 1][0], DP[0][N - 1][1]));
	return 0;
}
