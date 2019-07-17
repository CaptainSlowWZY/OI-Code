#include <cstdio>

const int kMaxn = 1010, kInf = 0x3f3f3f3f;

struct Info {
	int u, l, r;
} que[kMaxn];

int n;
int X[kMaxn], Y[kMaxn], DP[kMaxn][kMaxn], P[kMaxn][kMaxn];

inline int W(int l, int k, int r) {
	return X[k + 1] - X[l] + Y[k] - Y[r];
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", X + i, Y + i);
			DP[i][i] = 0, P[i][i] = i;
		}
		for (int i = 2; i <= n; i++) {
			for (int l = 1, r = i; r <= n; l++, r++) {
				DP[l][r] = kInf;
				for (int k = P[l][r - 1]; k <= P[l + 1][r] && k < r; k++) {
					if (DP[l][k] + DP[k + 1][r] + W(l, k, r) <= DP[l][r]) {
						DP[l][r] = DP[l][k] + DP[k + 1][r] + W(l, k, r);
						P[l][r] = k;
					}
				}
			}
		}
		printf("%d\n", DP[1][n]);
	}
	return 0;
}
