#include <cstdio>
#include <algorithm>
#include <queue>
#include <set>

#define forto(__, _) for (int e = __.last[_], v = __.E[e].to; e; v = __.E[e = __.E[e].next].to)

const int MAXV = 1e5 + 5, MAXE = 1e6 + 5;

typedef int IntAr[MAXV];

struct Graph {
	struct Edge {
		int to, next;
	} E[MAXE];
	int tote, last[MAXV];

	void adde(int u, int v) {
		E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	}
} OG, G;

int N, M, MOD, totscc, top, dfs_clock;
IntAr dfn, low, col, idgr, DP, size, way, S;
std::queue<int> que;
std::set<long long> SE;

void tarjan(int);

int main() {
	scanf("%d%d%d", &N, &M, &MOD);
	for (int u, v; M--; ) {
		scanf("%d%d", &u, &v);
		OG.adde(u, v);
	}

	for (int i = 1; i <= N; i++)
		if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= N; i++) {
		forto(OG, i) {
			long long cur = col[i] * 10000000ll + col[v];
			if (col[i] == col[v] || SE.count(cur)) continue;
			SE.insert(cur);
			G.adde(col[i], col[v]);
			++idgr[col[v]];
		}
	}
	for (int i = 1; i <= totscc; i++)
		if (!idgr[i]) {
			que.push(i);
			DP[i] = size[i], way[i] = 1;
		}
	int ans = 0;
	for (; !que.empty(); ) {
		int u = que.front(); que.pop();
		ans = std::max(ans, DP[u]);
		forto(G, u) {
			if (DP[u] + size[v] > DP[v]) {
				DP[v] = DP[u] + size[v];
				way[v] = way[u];
			}
			else if (DP[u] + size[v] == DP[v]) (way[v] += way[u]) %= MOD;
			if (--idgr[v] == 0) que.push(v);
		}
	}
	int tot = 0;
	for (int i = 1; i <= totscc; i++)
		if (DP[i] == ans) (tot += way[i]) %= MOD;
	
	printf("%d\n%d\n", ans, tot);
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
		size[col[u] = ++totscc] = 1;
		for (; top && S[top - 1] != u; --top) col[S[top - 1]] = totscc, ++size[totscc];
		--top;
	}
}
