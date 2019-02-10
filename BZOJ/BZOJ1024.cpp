#include <bits/stdc++.h>

double dfs(double x, double y, int n) {
	if (n == 1) return std::max(x / y, y / x);
	double ans = 1000000;
	for (int i = 1; i + i <= n; i++)
		ans = std::min(ans, std::max(dfs((double)i / n * x, y, i), dfs(double(n - i) / n * x, y, n - i)));
	for (int i = 1; i + i <= n; i++)
		ans = std::min(ans, std::max(dfs(x, (double)i / n * y, i), dfs(x, double(n - i) / n * y, n - i)));
	return ans;
}

int main() {
	int X, Y, N;
	scanf("%d%d%d", &X, &Y, &N);
	printf("%.6lf\n", dfs(X, Y, N));
	return 0;
}
