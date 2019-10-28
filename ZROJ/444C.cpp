#include <algorithm>
#include <cstdio>
#include <vector>

#define pb push_back

const int kMaxn = 2e3 + 5, kMod = 998244353;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upd(int & a, int b) { a = Add(a, b); }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

int n;
int DP[kMaxn][kMaxn], sz[kMaxn];
std::vector<int> G[kMaxn];

void Dfs(int, int);

int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		G[u].pb(v); G[v].pb(u);
	} Dfs(1, 0);
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		Upd(ans, DP[1][i]);
	printf("%d\n", ans);
	return 0;
}

void Dfs(int u, int fa) {
	static int nxt[kMaxn];
	DP[u][0] = 1;
	for (auto v : G[u]) {
		if (v == fa) continue;
		Dfs(v, u);
		std::fill(nxt, nxt + sz[u] + sz[v] + 1, 0);
		for (int i = 0; i <= sz[u]; ++i) {
			for (int j = 0; j <= sz[v]; ++j) 
				Upd(nxt[i + j], Mul(DP[u][i], DP[v][j]));
		} sz[u] += sz[v];
		for (int i = 0; i <= sz[u]; ++i)
			DP[u][i] = nxt[i];
	} std::fill(nxt, nxt + sz[u] + 2, 0);
	for (int i = 0; i <= sz[u]; ++i)
		nxt[i] = Add(DP[u][i], DP[u][i + 1]);
	Upd(nxt[1], DP[u][0]);
	++sz[u];
	for (int i = 0; i <= sz[u]; ++i)
		DP[u][i] = nxt[i];
}
