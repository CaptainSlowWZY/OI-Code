// Codeforces 995F
// Round #492 (Div. 1)
#pragma GCC diagnostic error "-std=c++11"
#include <cstdio>
#include <iostream>
#include <vector>

#ifdef LOCAL
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...)
#endif
#define pb push_back

typedef long long LL;

const int MAXN = 3015;
const int INIT = 3010;
const int MOD = 1e9 + 7;

int N, D, fac[MAXN], inv[MAXN], f[MAXN][MAXN], g[MAXN][MAXN];
std::vector<int> G[MAXN];

namespace FastIO {
	template <typename T>
		void read(T & x) {
			x = 0; register char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
}
inline void mult(int &x, int y) { x = (LL)y * x % MOD; }
LL fast_pow(LL bs, int ex) {
	LL res = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1) if (ex & 1) (res *= bs) %= MOD;
	return res;
}
inline LL get_inv(LL x) { return fast_pow(x, MOD - 2); }
void init();
void dfs(int);

int main() {
	init();
	using FastIO::read;

	read(N), read(D);
	for (int i = 2, fa; i <= N; i++) {
		read(fa);
		G[fa].pb(i);
	}
	dfs(1);

	if (D <= N + 1) {
		std::cout << g[1][D] << std::endl;
		return 0;
	}
	LL prd = 1, ans = 0;
	for (LL i = D - N - 1; i < D; i++) (prd *= i) %= MOD;
	for (int i = 1; i <= N + 1; i++) {
		LL tmp = prd * get_inv(D - i) % MOD, ivv = (LL)inv[i - 1] * inv[N + 1 - i] % MOD;
		debug("tmp=%lld, ivv=%lld\n", tmp, ivv);
		(ans += (LL)g[1][i] * ivv % MOD * tmp % MOD * (N + 1 - i & 1 ? -1LL : 1LL)) %= MOD;
	}
	ans = (ans + MOD) % MOD;
	std::cout << ans << std::endl;
	return 0;
}

void dfs(int u) {
	for (int i = 1; i <= N + 1; i++) f[u][i] = 1;
	for (auto v : G[u]) {
		dfs(v);
		for (int i = 1; i <= N + 1; i++) mult(f[u][i], g[v][i]);
	}
	for (int i = 1; i <= N + 1; i++) g[u][i] = (g[u][i - 1] + f[u][i]) % MOD;
}

void init() {
	fac[0] = 1;
	for (LL i = 1; i <= INIT; i++) fac[i] = i * fac[i - 1] % MOD;
	inv[INIT] = get_inv(fac[INIT]);
	for (LL i = INIT - 1; i >= 0; i--) inv[i] = (i + 1) * inv[i + 1] % MOD;
}

// AC!!!
