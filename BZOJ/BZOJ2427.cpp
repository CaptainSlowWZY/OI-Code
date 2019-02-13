// BZOJ 2427
// HAOI 2010
#include <cstdio>
#include <algorithm>

#define forto(_, __) for (int e = _.last[__], v = _.E[e].to; e; v = _.E[e = _.E[e].next].to)
// _ - Graph, __ - u

const int MAXN = 105, MAXM = 505;

typedef int IntAr[MAXN];

struct Graph {
	struct Edge {
		int to, next;
	} E[MAXN << 1];
	int tote, last[MAXN];

	void adde(int u, int v) {
		E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	}
} OG, T;

int N, M, top, dfs_clock, totscc, DP[MAXN][MAXM];
IntAr S, W0, W, V0, V, col, dfn, low, vis, indgr;

inline void upd_max(int & x, int y) { x < y ? x = y : 0; }
void tarjan(int u);
void dfs(int u);

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++) scanf("%d", W0 + i);
	for (int i = 1; i <= N; i++) scanf("%d", V0 + i);
	for (int i = 1, fa; i <= N; i++) {
		scanf("%d", &fa);
		if (!fa) continue;
		OG.adde(fa, i);
	}

	for (int i = 1; i <= N; i++)
		if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= N; i++) {
		W[col[i]] += W0[i], V[col[i]] += V0[i];
		forto(OG, i) {
		   if (col[v] == col[i]) continue;	   
		   T.adde(col[i], col[v]);
		   ++indgr[col[v]];
		}
	}
	for (int i = 1; i <= totscc; i++)
		if (!indgr[i]) T.adde(0, i);
	dfs(0);

	printf("%d\n", DP[0][M]);
	return 0;
}

void tarjan(int u) {
	dfn[u] = low[u] = ++dfs_clock;
	S[top++] = u;
	forto(OG, u) {
		if (!dfn[v]) {
			tarjan(v);
			low[u] = std::min(low[u], low[v]);
		}
		else if (!col[v]) low[u] = std::min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		col[u] = ++totscc;
		for (; top && S[top - 1] != u; --top) col[S[top - 1]] = totscc;
		if (top) --top;
	}
}	

void dfs(int u) {
	vis[u] = 1;
	for (int i = W[u]; i <= M; i++) DP[u][i] = V[u];
	forto(T, u) {
		if (!vis[v]) dfs(v);
		for (int i = M; i >= W[u]; i--) {
			for (int j = 0; i - j >= W[u]; j++)
				upd_max(DP[u][i], DP[u][i - j] + DP[v][j]);
		}
	}
}
