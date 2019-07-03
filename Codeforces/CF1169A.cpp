#include <cstdio>

int main() {
	int n, a, x, b, y;
	scanf("%d%d%d%d%d", &n, &a, &x, &b, &y);
	
	do {
		if (++a > n) a = 1;
		if (--b == 0) b = n;
		if (a == b) {
			puts("YES");
			return 0;
		}
	} while (a != x && b != y);

	puts("NO");
	return 0;
}
