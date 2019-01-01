// BZOJ 1257
#include <cstdio>
#include <algorithm>
typedef long long LL;
int N, K;

int main() {
	scanf("%d%d", &N, &K);

	LL ans = 0;
	for (int i = 1, j; i <= N; i = j + 1) {
		if (K / i > 0) j = std::min(N, K / (K / i));
		else break;
		ans += (LL)K / i * LL(i + j) * (j - i + 1) / 2;
	}
	ans = (LL)K * N - ans;
	
	printf("%lld\n", ans);

	return 0;
}
