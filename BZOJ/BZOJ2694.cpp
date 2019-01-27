// BZOJ 2694
#include <cstdio>
#include <algorithm>

const int MAXN = 4e6;
const int MOD = 1 << 30;

typedef long long LL;
typedef int IntAr[MAXN + 10];

int N, M, totp;
IntAr flag, P, g, ex;

void init();
void solve();

int main() {
	init();

	int t;
	for (scanf("%d", &t); t--; ) solve();

	return 0;
}

LL fast_pow(LL bs, int ex) {
	LL ret = 1;
	for (; ex; bs *= bs, ex >>= 1)
		if (ex & 1) ret *= bs;
	return ret;
}

void extgcd(int a, int b, int & x, int & y) {
	if (b) {
		extgcd(b, a % b, y, x);
		y -= a / b * x;
	}
	else { x = 1; y = 0; }
}

int inv(int a) {
	int x, y;
	extgcd(a, MOD, x, y);
	x = (x % MOD + MOD) % MOD;
}

inline LL sqr(LL x) { return x * x % MOD; }
inline void add(int & x, int y) { (x += y) %= MOD; }
inline LL sum(LL x, LL y) { return (x * (x + 1) / 2 % MOD) * (y * (y + 1) / 2 % MOD) % MOD; }

void init() {
	g[1] = 1, ex[1] = 0;
	for (int i = 2; i <= MAXN; i++) {
		if (!flag[i]) {
			P[totp++] = i;
			g[i] = LL(1 - i) * i % MOD;
			ex[i] = 1;
		}
		for (int j = 0, pd; j < totp && (pd = i * P[j]) <= MAXN; j++) {
			flag[pd] = 1;
			if (i % P[j] == 0) {
				ex[pd] = ex[i] + 1;
/*				int ppow = fast_pow(P[j], ex[pd]);
				g[pd] = (LL)g[pd / ppow] * g[ppow] % MOD;*/
				if (ex[pd] <= 2) g[pd] = (LL)g[i / P[j]] * ((LL)-P[j] * P[j] % MOD * P[j]) % MOD;
				else g[pd] = 0;
				break;
			}
			g[pd] = (LL)g[i] * g[P[j]] % MOD;
			ex[pd] = 1;
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
		add(ans, LL(g[j] - g[i - 1]) * sum(N / i, M / i) % MOD);
	}
	ans = (ans + MOD) % MOD;
	printf("%d\n", ans);
}
