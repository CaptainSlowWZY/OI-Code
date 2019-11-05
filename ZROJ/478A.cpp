#include <cstdio>

const int kMaxn = 1e5 + 5, kMaxm = 105;

int n, m;
long long DP[kMaxn][kMaxm];
char A[kMaxn], B[kMaxm];

int main() {
	scanf("%d%d%s%s", &n, &m, A + 1, B + 1);
	long long ans = 0;
	DP[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		DP[i][0] = DP[i - 1][0] + 1;
		for (int j = 1; j <= m; ++j)
			DP[i][j] += (A[i] == B[j] ? DP[i - 1][j - 1] : DP[i - 1][j]);
		ans += DP[i][m];
	} printf("%lld\n", ans); return 0;
}
