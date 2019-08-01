#include <cstdio>

const int kMaxm = 2010;

int n, m;
int DP[kMaxm];

template <typename T> inline
void UMax(T & x, const T & y) {
	if (x < y) x = y;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0, tp, A, B, C; i < n; i++) {
		scanf("%d", &tp);
		if (tp == 1) {
			scanf("%d%d", &A, &B);
			for (int i = m; i; i--) {
				for (int j = 1; j <= i; j++)
					UMax(DP[i], DP[i - j] + A * j * j - B * j);
			}
		} else if (tp == 2) {
			scanf("%d%d%d", &A, &B, &C);
			for (int i = m; i >= B; i--) {
				for (int j = 1; j * B <= i && j <= C; j++)
					UMax(DP[i], DP[i - j * B] + A * j);
			}
		} else {
			scanf("%d%d", &A, &B);
			for (int i = B; i <= m; i++) {
				UMax(DP[i], DP[i - B] + A);
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= m; i++) UMax(ans, DP[i]);
	printf("%d\n", ans);
	return 0;
}
