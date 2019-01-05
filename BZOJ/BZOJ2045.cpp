// BZOJ 2045
#include <cstdio>
#include <algorithm>

typedef long long LL;

const int MAXN = 1e6 + 10;

int A, B, d, totp, mu[MAXN], flag[MAXN], P[MAXN];

void init(int);

int main() {
	scanf("%d%d%d", &A, &B, &d);

	A /= d, B /= d;
	if (A < B) std::swap(A, B);
	init(A);

	LL ans = 0;
	for (int i = 1; i <= A; i++)
		ans += mu[i] * LL(A / i) * LL(B / i);

	printf("%lld\n", ans);

	return 0;
}

void init(int lmt) {
	mu[1] = 1;
	for (int i = 2; i <= lmt; i++) {
		if (!flag[i]) P[totp++] = i, mu[i] = -1;
		for (int j = 0, pd; j < totp && (pd = i * P[j]) <= lmt; j++) {
			flag[pd] = 1;
			if (i % P[j] == 0) {
				mu[pd] = 0;
				break;
			}
			mu[pd] = -mu[i];
		}
	}
}
