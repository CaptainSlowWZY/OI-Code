// Codeforces 1060 B
// Round #513
#include <cstdio>
#include <algorithm>
typedef long long LL;

int S(LL n) {
	int res = 0;
	for (; n; n /= 10) res += n % 10;
	return res;
}

int main() {
	LL N, m = 0;
	scanf("%I64d", &N);
	int ans = 0;
	for (LL m = 0; m <= N; m = (m << 3) + (m << 1) + 9) ans = std::max(ans, S(m) + S(N - m));
	printf("%d\n", ans);
	return 0;
}
