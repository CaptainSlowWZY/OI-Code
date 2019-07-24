#include <cstdio>

const int MOD = 1e6 + 3;

int main() {
	int n;
	while (~scanf("%d", &n)) {
		if (n >= MOD) {
			puts("0");
			continue;
		}
		long long ans = 1;
		for (int i = 2; i <= n; i++)
			(ans *= i) %= MOD;
		printf("%lld\n", ans);
	}
	return 0;
}
