#include <cstdio>

typedef long long LL;

LL n, k, P[100005];
int m;

int main() {
	scanf("%lld%d%lld", &n, &m, &k);
	for (int i = 0; i < m; i++) scanf("%lld", P + i);
	LL l = 0, r = 0;
	int cnt = 0;
	for (int i = 0; i < m; i++) {
		if (P[i] < r) continue;
		++cnt;
		r = (l = (P[i] - i - 1) / k * k + i + 1) + k;
	} printf("%d\n", cnt);
	return 0;
}
