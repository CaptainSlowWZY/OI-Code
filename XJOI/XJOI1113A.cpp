#include <cstdio>
#include <cstring>
#include <algorithm>

const int MOD = 1e9;

int T, N, M, U, DP[2][(1 << 18) + 5], C[12];

inline void add(int & x, int y) { (x += y) >= MOD ? x -= MOD : 0; }
void FMT(int A[]) {
	for (int i = 0; i < M; i++)
		for (int j = 0; j < U; j++)
			if (j >> i & 1) add(A[j], A[j ^ 1 << i]);
}

int main() {
	for (scanf("%d", &T); T--; ) {
		scanf("%d%d", &N, &M);
		for (int i = 0; i < N; i++) scanf("%d", C + i);

		U = 1 << M;
		memset(DP[0], 0, sizeof DP[0]);
		int *prv = DP[0], *nxt = DP[1];
		prv[0] = 1;
		for (int i = 0; i < N; i++) {
			FMT(prv);
			for (int j = 0; j < U; j++) nxt[j] = j % C[i] ? prv[U - 1 ^ j] : 0;
			std::swap(prv, nxt);
		}

		int ans = 0;
		for (int j = 0; j < U; j++) add(ans, prv[j]);
		printf("%d\n", ans);
	}
	return 0;
}
