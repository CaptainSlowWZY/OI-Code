#include <algorithm>
#include <cstdio>

const int kMaxn = 1005, kMaxm = 205, kMod = 1e9 + 7;

int n, m, k;
int DP[2][kMaxn][kMaxm];
char A[kMaxn], B[kMaxm];

inline void Add(int & x, int y) {
	if ((x += y) >= kMod) x -= kMod;
}

int main() {
	scanf("%d%d%d%s%s", &n, &m, &k, A + 1, B + 1);

	int (*prv)[kMaxm] = DP[0], (*nxt)[kMaxm] = DP[1];
	for (int i = 1; i <= n; i++) prv[i][1] = A[i] == B[1];
	for (int j = 2; j <= m; j++) {
		for (int l = 1; l <= k; l++) {
			int sum = 0;
			for (int i = 1; i <= n; i++) {
				Add(sum, prv[i - 1][l - 1]);
				nxt[i][l] = A[i] == B[j] ?
					(prv[i - 1][l] + sum) % kMod : 0;
			//	printf(" DP[%2d][%2d][%2d] = %d, sum = %d\n",
			//			i, j, l, nxt[i][l], sum);
			}
		} std::swap(prv, nxt);
	} int ans = 0;
	for (int i = 1; i <= n; i++) Add(ans, prv[i][k]);
	printf("%d\n", ans);
	return 0;
}
