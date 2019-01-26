// BZOJ 2154
#include <cstdio>
#include <algorithm>

typedef long long LL;

const int MAXN = 1e7;
const int MOD = 20101009;

int N, M, totp, g[MAXN + 10], flag[MAXN + 10], P[MAXN + 10];

inline void add(int & x, int y) { x = (x + y) % MOD; }
inline LL sum(LL x, LL y) { return (x * (x + 1) / 2 % MOD) * (y * (y + 1) / 2 % MOD) % MOD; }

void init();
void solve();

int main() {
	init();
	solve();
	return 0;
}

void init() {
	g[1] = 1;
	for (int i = 2; i <= MAXN; i++) {
		if (!flag[i]) P[totp++] = i, g[i] = LL(1 - i) * i % MOD;
		for (int j = 0, pd; j < totp && (pd = i * P[j]) <= MAXN; j++) {
			flag[pd] = 1;
			if (i % P[j] == 0) {
				g[pd] = (LL)g[i] * P[j] % MOD;
				break;
			}
			g[pd] = (LL)g[P[j]] * g[i] % MOD;
		}
	}
	for (int i = 1; i <= MAXN; i++) add(g[i], g[i - 1]);
}

void solve() {
	scanf("%d%d", &N, &M);
	if (N > M) std::swap(N, M);
	int ans = 0;
	for (int i = 1, j; i <= N; i = j + 1) {
		j = std::min(N / (N / i), M / (M / i));
		add(ans, sum(N / i, M / i) * (g[j] - g[i - 1]) % MOD);
	}
	ans = (ans + MOD) % MOD;
	printf("%d\n", ans);
}
