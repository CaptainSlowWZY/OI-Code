#include <algorithm>
#include <cstdio>
#include <vector>

#define pb push_back

const int kMaxn = 1e5 + 5, kLg = 17, kDeg = 505, kMod = 998244353;

int n, q, L;
int dep[kMaxn], sz[kMaxn], F[kMaxn][kLg], deg[kMaxn];
int fac[kMaxn], ifc[kMaxn], P[kMaxn][kDeg], inv[kMaxn];
std::vector<int> G[kMaxn];

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}
inline void Upd(int & x, int y) { x = Add(x, y); }
int Climb(int, int);
int Inv(int, int, int);
int Lca(int, int);
void Dfs(int);

int main() {
	scanf("%d%d%d", &n, &q, &L);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		G[u].pb(v); G[v].pb(u);
	} dep[1] = 1; Dfs(1);
	for (int i = fac[0] = 1; i <= n; ++i)
		fac[i] = Mul(fac[i - 1], i);
	ifc[n] = FPow(fac[n]);
	for (int i = n - 1; i >= 0; --i)
		ifc[i] = Mul(ifc[i + 1], i + 1);
	inv[1] = 1;
	for (int i = 2; i <= n; ++i)
		inv[i] = Sub(kMod, Mul(kMod / i, inv[kMod % i]));
	for (int l, u, v, k; q--; ) {
		scanf("%d%d%d", &u, &v, &k);
		if (dep[u] > dep[v]) std::swap(u, v);
		l = Lca(u, v);
		printf("%d\n", Mul(Inv(v, n - sz[v], k),
				Inv(u, l == u ? sz[Climb(v,
				dep[v] - dep[u] - 1)] : n - sz[u], k)));
	} return 0;
}

int Climb(int u, int d) {
	for (int i = 0; i < kLg; ++i)
		if (d >> i & 1) u = F[u][i];
	return u;
}

int Lca(int u, int v) {
	v = Climb(v, dep[v] - dep[u]);
	if (v == u) return u;
	for (int i = kLg - 1; i >= 0; --i)
		if (F[u][i] != F[v][i]) {
			u = F[u][i], v = F[v][i];
		}
	return F[u][0];
}

int Inv(int u, int szi, int k) {
	int res = 0;
	for (int i = deg[u] - 1, la = Mul(P[u][deg[u]],
				inv[szi]); i >= 0; --i) {
		if (i <= k)
			Upd(res, Mul(la, Mul(fac[k], ifc[k - i])));
		la = Mul(Sub(P[u][i], la), inv[szi]);
	} // printf(" inv %d, sz %d, k %d = %d\n", u, szi, k, res);
	return res;
}

void Dfs(int u) {
	for (int i = 1; i < kLg && F[u][i - 1]; ++i)
		F[u][i] = F[F[u][i - 1]][i - 1];
	sz[u] = P[u][0] = 1, deg[u] = 0;
	for (auto v : G[u]) {
		if (v == F[u][0]) continue;
		dep[v] = dep[u] + 1; F[v][0] = u; Dfs(v);
		for (int i = deg[u]; i >= 0; --i)
			Upd(P[u][i + 1], Mul(P[u][i], sz[v]));
		sz[u] += sz[v], ++deg[u];
	}
	int szo = n - sz[u];
	for (int i = deg[u]++; i >= 0; --i)
		Upd(P[u][i + 1], Mul(P[u][i], szo));
}
