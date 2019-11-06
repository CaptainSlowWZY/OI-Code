#include <cstdio>

int main() {
	int t; scanf("%d", &t);
	for (long long n; t--; ) {
		scanf("%lld", &n);
		if (!n) { puts("2 5"); continue; }
		if (n & 1) {
			if (n > 3) printf("%lld %lld\n", n - 3, n - 1);
			else printf("%lld %lld\n", n, n + 4);
		} else {
			if (n > 4) printf("%lld %lld\n", n - 4, n);
			else printf("%lld %lld\n", n + 1, n + 3);
		}
	} return 0;
}
