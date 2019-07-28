#include <cstdio>

int n, k;

int main() {
	scanf("%d%d", &n, &k);

	printf("1 ");
	for (int del = k, pi = 1, f = 1; del; ) {
		pi += f * del--, f = -f;
		printf("%d ", pi);
	}
	for (int i = k + 2; i <= n; i++) printf("%d ", i);
	putchar('\n');
	return 0;
}
