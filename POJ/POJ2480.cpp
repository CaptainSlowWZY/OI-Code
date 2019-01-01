// POJ 2480
#include <cstdio>

typedef long long LL;

const int INIT_LIM = 5e4;

int N, totp, P[INIT_LIM + 10], flag[INIT_LIM + 10];

void init();
void solve(int);

int main() {
	init();

	while (scanf("%d", &N) == 1) solve(N);

	return 0;
}

void init() {
	for (int i = 2; i <= INIT_LIM; i++) {
		if (!flag[i]) P[totp++] = i;
		for (int j = 0, pd; j < totp && (pd = i * P[j]) <= INIT_LIM; j++) {
			flag[pd] = 1;
			if (i % P[j] == 0) break;
		}
	}
}

LL fast_pow(LL bs, int ex) {
	LL ret = 1;
	for (; ex; bs *= bs, ex >>= 1)
		if (ex & 1) ret *= bs;
	return ret;
}

void solve(int n) {
	LL ans = 1;

	for (int i = 0; i < totp && n > 1; i++)
		if (n % P[i] == 0) {
			LL ex = 0;
			for (; n % P[i] == 0; ++ex, n /= P[i]);
			LL tmp = fast_pow(P[i], ex - 1);
			ans *= tmp * (ex * (P[i] - 1) + P[i]);
		}
	if (n > 1) ans *= 2LL * n - 1;

	printf("%lld\n", ans);
}
