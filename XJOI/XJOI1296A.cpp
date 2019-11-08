#include <algorithm>
#include <cstdio>
#include <cstring>

#define pb push_back
#define SZ(_) (int)_.size()
#define FORTO(V, U) for (int e = bac[U], V = E[e].to; e; V = E[e = E[e].next].to)

const int kMaxn = 3e3 + 5, kMaxm = 4505, kBas = 2333;

typedef int Arr[kMaxn];

struct Edge { int to, tag, next; } E[kMaxm << 1];

int n, m, cnte = 1, totv, cntc, dfsc;
Arr col, dfn, low, ha, bac;

inline void AddEdge(int u, int v) {
	E[++cnte] = (Edge){v, 0, bac[u]}, bac[u] = cnte;
	E[++cnte] = (Edge){u, 0, bac[v]}, bac[v] = cnte;
}
void Tar(int, int);
void Dfs(int);

int main() {
	scanf("%d%d%*d", &n, &m);
	for (int u, v; m--; ) { scanf("%d%d", &u, &v); AddEdge(u, v); }
	long long ans = 0;
	for (int i = 1; i <= n; ++i) if (!dfn[i]) { totv = 0; Tar(i, 0); ans += 1ll * totv * (totv - 1); }
	std::fill(dfn, dfn + n + 1, 0);
	for (int i = 1; i <= n; ++i) if (!dfn[i]) { totv = 0; Dfs(i); ans += 1ll * totv * (totv - 1); }
	for (int i = 2; i <= cnte; i += 2) {
		for (int j = 2; j <= cnte; ++j) E[j].tag = 0;
		E[i].tag = E[i ^ 1].tag = 1, dfsc = 0; std::fill(dfn, dfn + n + 1, 0);	
//		printf(" erase edge %d, %d\n", E[i].to, E[i ^ 1].to);
		for (int j = 1; j <= n; ++j) if (!dfn[j]) Tar(j, 0);
		std::fill(dfn, dfn + n + 1, 0); cntc = 0;
		for (int j = 1; j <= n; ++j) if (!dfn[j]) { ++cntc; Dfs(j); }
		for (int j = 1; j <= n; ++j) ha[j] = ha[j] * kBas + col[j];
	} ans >>= 1;
	for (int i = 1; i <= n; ++i) for (int j = i + 1; j <= n; ++j) if (ha[i] == ha[j]) ++ans;
	printf("%lld\n", ans); return 0;
}

void Dfs(int u) {
	dfn[u] = 1, ++totv, col[u] = cntc;
	FORTO(v, u) if (!E[e].tag && !dfn[v]) Dfs(v);
}

void Tar(int u, int fa) {
	dfn[u] = low[u] = ++dfsc, ++totv;
	FORTO(v, u) if (v != fa && !E[e].tag) {
		if (!dfn[v]) {
			Tar(v, u); low[u] = std::min(low[u], low[v]);
			if (low[v] > dfn[u]) E[e].tag = E[e ^ 1].tag = 1;
		} else low[u] = std::min(low[u], dfn[v]);
	}
}
