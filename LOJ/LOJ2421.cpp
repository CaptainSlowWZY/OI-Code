#include <algorithm>
#include <cstdio>

const int kMaxn = 2e5 + 10;

int n, top, dfs_clock, ans = kMaxn;
int G[kMaxn], dfn[kMaxn], low[kMaxn], ins[kMaxn], S[kMaxn];

void Dfs(int);

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", G + i);

	for (int i = 1; i <= n; i++) {
		if (dfn[i]) continue;
		Dfs(i);
	} printf("%d\n", ans);
	return 0;
}

void Dfs(int u) {
	dfn[u] = low[u] = ++dfs_clock;
	S[top++] = u, ins[u] = 1;
	int v = G[u];
	if (!dfn[v]) {
		Dfs(v); low[u] = std::min(low[u], low[v]);
	} else if (ins[v]) {
		low[u] = std::min(low[u], dfn[v]);
	} if (low[u] == dfn[u]) {
		int size = 1;
		for (; S[top - 1] != u; ++size) ins[S[--top]] = 0;
		ins[u] = 0, --top;
		if (size > 1) ans = std::min(ans, size);
	}
}
