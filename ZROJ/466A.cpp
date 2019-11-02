#include <cstdio>

int n, m, k;
int B[300010];

int main() {
	scanf("%d%d%d", &n, &m, &k);
	long long len = 0;
	for (int i = 0; i < k; ++i) {
		scanf("%d", B + i);
		len += m - B[i] + 1;
	}
	if (len < n) { puts("No"); return 0; }
	puts("Yes"); n -= k;
	for (int i = 0; i < k; ++i) {
		for (int j = m; j > B[i] && n; --n, --j) printf("%d ", j);
		printf("%d ", B[i]);
	} puts("");
	return 0;
}
