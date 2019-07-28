#include <algorithm>
#include <cstdio>

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	printf("%d\n", std::min(n, m) + 1);
	for (int i = 0, x, y; i <= n && i <= m; i++) {
		if (n < m) {
			x = n - i, y = i;
		} else {
			x = i, y = m - i;
		}
		printf("%d %d\n", x, y);
	}
	return 0;
}
