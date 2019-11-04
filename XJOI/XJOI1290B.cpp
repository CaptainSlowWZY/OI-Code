#include <algorithm>
#include <cstdio>

#define FORTO(_) for (int e = bak[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)

const int kN = 1e5, kMaxn = 1e5 + 5, kMaxk = 102, kLg = 17, kMod = 998244353;

typedef int Arr[kMaxn];
typedef int Mat[kMaxn][kMaxk];

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upa(int & a, int b) { a = Add(a, b); }
inline void Ups(int & a, int b) { a = Sub(a, b); }
inline void Upm(int & a, int b) { a = Mul(a, b); }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}
void Solve();

struct Edge { int to, next; } E[kMaxn << 1];

int cnte, n, q;
int F[kMaxn][kLg];
Arr bak, dep, sz;
Mat pw, D, D1;

int main() {
	int t; scanf("%d", &t);
	while (t--) Solve();
	return 0;
}

void Dfs1(int u) {
	for (int i = 1; i < kLg && F[u][i - 1]; ++i)
		F[u][i] = F[F[u][i - 1]][i - 1];
	sz[u] = 1;
	FORTO(u) if (v != F[u][0]) {
		dep[v] = dep[u] + 1; F[v][0] = u;
		Dfs1(v); sz[u] += sz[v];
		for (int i = 1, p = 1; i <= 100; ++i)
			Upa(D[u][i], p = Mul(p, sz[v]));
	}
	FORTO(u) if (v != F[u][0]) {
		for (int i = 1; i <= 100; ++i)
			Upa(D1[v][i], Add(Sub(D[u][i], pw[sz[v]][i]), pw[n - sz[u]][i]));
	}
}

int Lca(int u, int v) {
	if (dep[u] > dep[v]) std::swap(u, v);
	for (int i = 0, d = dep[v] - dep[u];
			i < kLg && (1 << i) <= d; ++i)
		if (d >> i & 1) v = F[v][i];
	if (u == v) return u;
	for (int i = kLg - 1; i >= 0; --i)
		if (F[u][i] != F[v][i]) { u = F[u][i], v = F[v][i]; }
	return F[u][0];
}

inline void AddEdge(int u, int v) {
	E[++cnte] = (Edge){v, bak[u]}, bak[u] = cnte;
	E[++cnte] = (Edge){u, bak[v]}, bak[v] = cnte;
}

void Solve() {
	scanf("%d%d", &n, &q);
	cnte = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = bak[i] = 0; j < kLg; ++j) F[i][j] = 0;
		for (int j = pw[i][0] = 1; j <= 100; ++j) {
			pw[i][j] = Mul(pw[i][j - 1], i);
			D[i][j] = D1[i][j] = 0;
		}
	}
	for (int i = 1, x, y; i < n; ++i) {
		scanf("%d%d", &x, &y); AddEdge(x, y);
	} dep[1] = 1, Dfs1(1);
	for (int l, a, b, sl, k, x, y; q--; ) {
		scanf("%d%d%d", &k, &x, &y);
		l = Lca(x, y);
	//	printf(" sz[x %d] %d, sz[y %d] %d\n", x, sz[x], y, sz[y]);
	//	printf("  lca x, y = %d\n", l);
		if (l != x && l != y) {
			a = Sub(pw[sz[x]][k], D[x][k]);
			b = Sub(pw[sz[y]][k], D[y][k]);
			printf("%d\n", Mul(a, b));
		} else {
			if (l == x) x = y; sl = n - sz[l];
			a = Sub(pw[sz[x]][k], D[x][k]);
			for (int i = kLg - 1; ~i; --i)
				if (dep[F[x][i]] > dep[l]) x = F[x][i];
			sl += sz[l] - sz[x];
		//	printf(" x = %d, D1[x][k] = %d\n", x,D1[x][k]);
			b = Sub(pw[sl][k], D1[x][k]);
			printf("%d\n", Mul(a, b));
		}
	}
}
