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

const int MAXN = 3010;
const int MOD = 1e9 + 7;
const int INIT = 3005;

int N, D, f[MAXN][MAXN], g[MAXN][MAXN], fac[MAXN], inv[MAXN];
std::vector<int> G[MAXN];

namespace FastIO {
	template <typename T>
		void read(T & x) {
			x = 0; register char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
}
inline LL C(int n, int r) { return (LL)fac[n] * inv[r] % MOD * inv[n - r] % MOD; }
inline void mult(int &x, int y) { x = (LL)y * x % MOD; }
inline void add(LL &x, LL d) { (x += d) %= MOD; }
LL BigC(int n, int r) {
	LL res = inv[r];
	for (LL i = n - r + 1; i <= n; i++) (res *= i) %= MOD; 
	return res;
}
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

	LL ans = 0;
//	for (int i = 1; i <= N; i++) debug("DP[1][%d]=%d\n", i, f[1][i]);
	for (int i = 1; i <= N && i <= D; i++) {
		LL tmp = 0;
		for (int j = 1; j <= i; j++) add(tmp, (i - j & 1 ? -1LL : 1LL) * C(i - 1, j - 1) * f[1][j] % MOD);	
		tmp = (tmp + MOD) % MOD;
//		debug("i=%d, g[i]=%lld\n", i, tmp);
		add(ans, tmp * BigC(D, i) % MOD);
	}
	ans = (ans + MOD) % MOD;
	std::cout << ans << std::endl;
	return 0;
}

void dfs(int u) {
	for (int i = 1; i <= N; i++) f[u][i] = 1;
	for (auto v : G[u]) {
		dfs(v);
		for (int i = 1; i <= N; i++) mult(f[u][i], g[v][i]);
	}
	for (int i = 1; i <= N; i++) g[u][i] = (g[u][i - 1] + f[u][i]) % MOD;
}

LL fast_pow(LL bs, int ex) {
	LL res = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1) if (ex & 1) (res *= bs) %= MOD;
	return res;
}

void init() {
	fac[0] = 1;
	for (LL i = 1; i <= INIT; i++) fac[i] = i * fac[i - 1] % MOD;	
	inv[INIT] = fast_pow(fac[INIT], MOD - 2);
	for (LL i = INIT - 1; i >= 0; i--) inv[i] = (i + 1) * inv[i + 1] % MOD;
}

// AC!!!
