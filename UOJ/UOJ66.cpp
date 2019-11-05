#include <cstdio>
int main() {
	int t; scanf("%d", &t);
	for (int n; t--; ) {
		scanf("%d", &n);
		long long ans = 0;
		for (int i = 0; i < 30; ++i)
			if (n >> i & 1) ans += (1 << i) - 1;
		printf("%lld\n", ans);
	} return 0;
}
