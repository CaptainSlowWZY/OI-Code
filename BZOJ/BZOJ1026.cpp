#include <cstdio>
#include <cstring>
#include <algorithm>

int len, N[12], DP[12][2][10];

int solve(int n);

int main() {
	int a, b;
	scanf("%d%d", &a, &b);
	memset(DP, 0xff, sizeof DP);
	printf("%d\n", solve(b) - solve(a - 1));
	return 0;
}

int dfs(int pos, int is0, int pre, int lim) {
	if (pos < 0) return 1;
	if (!lim && ~DP[pos][is0][pre]) return DP[pos][is0][pre];
	int ret = 0;
	for (int i = 0, l = lim ? N[pos] : 9; i <= l; i++)
		if (is0 || abs(i - pre) >= 2) ret += dfs(pos - 1, is0 & !i, i, lim & i == N[pos]);
	if (!lim) return DP[pos][is0][pre] = ret;
	return ret;
}

int solve(int n) {
	for (len = 0; n; n /= 10) N[len++] = n % 10;
	N[len] = 0;
	return dfs(len - 1, 1, 0, 1);
}
