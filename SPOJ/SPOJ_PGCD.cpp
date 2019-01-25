// SPOJ PGCD
#include <cstdio>
#include <algorithm>

const int INIT_LIM = 1e7;

typedef int IntArr[INIT_LIM + 10];
typedef long long LL;

IntArr mu, g, P, flag;
int totp, a, b;

void init();
void solve();

int main() {
	init();
	int t;
	for (scanf("%d", &t); t--; ) solve();

	return 0;
}

void init() {
	mu[1] = 1, g[1] = 0;
	for (int i = 2; i <= INIT_LIM; i++) {
		if (!flag[i]) P[totp++] = i, mu[i] = -1, g[i] = 1;
		for (int j = 0, pd; j < totp && (pd = i * P[j]) <= INIT_LIM; j++) {
			flag[pd] = 1;
			if (i % P[j] == 0) {
				mu[pd] = 0, g[pd] = mu[i];
				break;
			}
			mu[pd] = -mu[i], g[pd] = -g[i] + mu[i];
		}
	}
}

void solve() {
	scanf("%d%d", &a, &b);
	if (a > b) std::swap(a, b);
	LL ans = 0;
	for (int i = 1; i <= a; i++) ans += LL(a / i) * (b / i) * g[i];

	printf("%lld\n", ans);
}
