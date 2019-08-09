#include <cstdio>

typedef long long LL;

int n;
LL W[100010];

int main() {
	scanf("%d", &n);
	LL sumw = 0, sumw2 = 0;
	for (int i = 0; i < n; i++) {
		scanf("%lld", W + i);
		sumw += W[i];
		sumw2 += W[i] * W[i];
	}
	for (int i = 0; i < n; i++) {
		printf("%lld ", sumw2 - 2 * sumw * W[i] +
				W[i] * W[i] * n);
	} putchar('\n'); return 0;
}
