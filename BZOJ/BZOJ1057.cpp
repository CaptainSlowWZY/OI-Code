// BZOJ 1057
// ZJOI 2007
#include <cstdio>
#include <algorithm>

const int MAXN = 2005, INF = 0x3f3f3f3f;

int N, M, A[MAXN][MAXN], L[MAXN][MAXN], R[MAXN][MAXN], U[MAXN][MAXN];

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++) {
			scanf("%d", &A[i][j]);
			L[i][j] = R[i][j] = j;
			U[i][j] = 1;
		}

	int mx1 = 0, mx2 = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 2; j <= M; j++)
			if (A[i][j] ^ A[i][j - 1]) L[i][j] = L[i][j - 1];
		for (int j = M - 1; j > 0; j--)
			if (A[i][j] ^ A[i][j + 1]) R[i][j] = R[i][j + 1];
	}
	for (int i = 1; i <= M; i++) A[0][i] = A[1][i];
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++) {
			if (A[i][j] ^ A[i - 1][j]) {
				L[i][j] = std::max(L[i][j], L[i - 1][j]);
				R[i][j] = std::min(R[i][j], R[i - 1][j]);
				U[i][j] = U[i - 1][j] + 1;
			}
			int a = R[i][j] - L[i][j] + 1, b = U[i][j];
			if (a < b) std::swap(a, b);
			mx1 = std::max(mx1, b * b);
			mx2 = std::max(mx2, a * b);
		}

	printf("%d\n%d\n", mx1, mx2);
	return 0;
}
