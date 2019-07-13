#include <algorithm>
#include <cstdio>

const int kMaxn = 1010, MOD = 998244353;

int n, k;
int A[kMaxn], DP[kMaxn][kMaxn], sum[kMaxn], le[kMaxn];

void Add(int & x, int y) { (x += y) >= MOD ? x -= MOD : 0; }
int Solve(int);

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", A + i);

	std::sort(A + 1, A + n + 1);
	int gap = A[n] - A[1], ans = 0;
	for (int i = 1; i * (k - 1) <= gap; i++)
		Add(ans, Solve(i));

	printf("%d\n", ans);
	return 0;
}

int Solve(int gp) {
	for (int i = 0; i <= k; i++) {
		for (int j = 0; j <= n; j++) DP[i][j] = 0;
	}
	le[0] = 0;
	for (int i = 1; i <= n; i++) {
		le[i] = le[i - 1];
		while (A[i] - A[le[i] + 1] >= gp) ++le[i];
	}
	DP[0][0] = 1;
	for (int i = 0; i < k; i++) {
		sum[0] = DP[i][0];
		for (int j = 1; j <= n; j++)
			sum[j] = (sum[j - 1] + DP[i][j]) % MOD;	
		for (int j = 1; j <= n; j++)
			DP[i + 1][j] = sum[le[j]];
	}
	int res = 0;
	for (int i = 1; i <= n; i++) Add(res, DP[k][i]);
	return res;
}
