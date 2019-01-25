// BZOJ 2005
// NOI 2010
#include <cstdio>
#include <algorithm>

typedef long long LL;

const int MAXN = 1e5 + 10;

int N, M, totp, P[MAXN], flag[MAXN], mu[MAXN];

inline LL g(int x) { return LL(N / x) * (M / x); }
void init(int);

int main() {
	scanf("%d%d", &N, &M);
	
	if (N < M) std::swap(N, M);
	init(N);
	LL ans = 0;
	for (int i = 1; i <= N; i++) {
		LL fi = 0;
		for (int j = i; j <= N; j += i) fi += mu[j / i] * g(j);

		ans += fi * i;
	}
	ans = ans * 2 - (LL)N * M;

	printf("%lld\n", ans);
	
	return 0;
}

void init(int lim) {
	mu[1] = 1;
	for (int i = 2; i <= lim; i++) {
		if (!flag[i]) P[totp++] = i, mu[i] = -1;
		for (int j = 0, pd; j < totp && (pd = i * P[j]) <= lim; j++) {
			flag[pd] = 1;
			if (i % P[j] == 0) {
				mu[pd] = 0;
				break;
			}
			mu[pd] = -mu[i];
		}
	}
}
