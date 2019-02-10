// BZOJ 1023
#include <cstdio>
#include <cstring>
#include <algorithm>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int MAXV = 5e4 + 5;
const int MAXE = 1e7 + 5;

typedef int IntAr[MAXV];

struct Edge {
	int to, next;
} E[MAXE << 1];

int N, M, tote, ans, dfs_clock, A[MAXV << 1], Q[MAXV << 1];
IntAr last, fa, F, dfn, low, dep;

inline void add_edge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, last[v]}, last[v] = tote;
}
void dfs(int u);

int main() {
	while (scanf("%d%d", &N, &M) == 2) {
		tote = 0;
		memset(last, 0, sizeof last);
		memset(dfn, 0, sizeof dfn);
		memset(F, 0, sizeof F);

		for (int k, u, v; M--; ) {
			scanf("%d%d", &k, &u);
			for (--k; k--; u = v) {
				scanf("%d", &v);
				add_edge(u, v);
			}
		}

		ans = dfs_clock = 0, dep[1] = 1;
		dfs(1);
		printf("%d\n", ans);
	}

	return 0;
}

void dp(int tp, int bt) {
	int sz = dep[bt] - dep[tp] + 1, len = 0;
	for (int u = bt; u != tp; u = fa[u]) A[len++] = F[u];
	A[len++] = F[tp];
	for (int i = 0; i < sz; i++) A[len++] = A[i];
	int hd = 0, tl = 0;
	Q[tl++] = 0;
	for (int i = 1; i < len; i++) {
		while (hd < tl && i - Q[hd] << 1 > sz) ++hd;
		if (hd < tl) ans = std::max(ans, A[i] + A[Q[hd]] + i - Q[hd]);
		while (hd < tl && A[i] - i >= A[Q[tl - 1]] - Q[tl - 1]) --tl;
		Q[tl++] = i;
	}
	for (int i = 0; i + 1 < sz; i++) F[tp] = std::max(F[tp], A[i] + std::min(sz - 1 - i, i + 1));
}

void dfs(int u) {
	dfn[u] = low[u] = ++dfs_clock;
	forto(u) {
		if (v == fa[u]) continue;
		if (!dfn[v]) {
			fa[v] = u, dep[v] = dep[u] + 1;
			dfs(v);
			low[u] = std::min(low[u], low[v]);
		}
		else low[u] = std::min(low[u], dfn[v]);
		if (dfn[u] < low[v]) {
		//	means the current-edge is a bridge
			ans = std::max(ans, F[u] + F[v] + 1);
			F[u] = std::max(F[u], F[v] + 1);
		}
	}
	forto(u)
		if (fa[v] != u && dfn[u] < dfn[v]) {
		//	find a loop
			dp(u, v);
		}
}
