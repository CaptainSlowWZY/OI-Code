// fair
#include <cstdio>

typedef long long LL;

const int MOD = 998244353;
const int MAXN = 20;
const int MAXM = 400;
const int MAXS = 1 << 18;

struct Edge {
	int u, v, p;
} E[MAXM];

int N, M, Pin[MAXS], Pout[MAXS], inv[MAXS], f[MAXS];

LL fast_pow(LL bs, int ex) {
	LL ret = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1) if (ex & 1) (ret *= bs) %= MOD;
	return ret;
}
inline int get_inv(int x) { return fast_pow(x, MOD - 2); }
inline void mult(int & x, LL y) { x = y * x % MOD; }
inline void add(int & x, int y) { (x += y) %= MOD; }

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].p);
		--E[i].u, --E[i].v;
	}

	for (int mask = (1 << N) - 1; mask > 0; --mask) {
		Pin[mask] = Pout[mask] = 1;
		int & pin = Pin[mask], & pout = Pout[mask];
		for (int i = 0; i < M; i++) {
			if (mask >> E[i].u & 1 && mask >> E[i].v & 1) mult(pin, E[i].p);
			if (mask >> E[i].u & 1 ^ mask >> E[i].v & 1) mult(pout, E[i].p);
		}
		inv[mask] = get_inv(pin);
	}

	int ans = 0;
	for (int mask = 1, lmt = 1 << N; mask < lmt; ++mask) {
		int & fs = f[mask], s = mask ^ mask & -mask;
		for (int t = s; t; t = t - 1 & s) add(fs, (LL)f[mask ^ t] * inv[t] % MOD * inv[mask ^ t] % MOD);
		fs = (1 - (LL)Pin[mask] * fs % MOD) % MOD;
		add(ans, (LL)fs * Pout[mask] % MOD);
	}

	ans = (ans + MOD) % MOD;
	printf("%d\n", ans);
	return 0;
}
