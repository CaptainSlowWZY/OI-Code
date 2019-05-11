// Codeforces #236 (Div. 2)
#include <cstdio>
#include <algorithm>

const int kMaxn = 2005;

int n, top, totscc;
int dfn[kMaxn], low[kMaxn], S[kMaxn], ins[kMaxn];
int A[kMaxn][kMaxn];

void Tarjan(int u);

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) scanf("%d", &A[i][j]);
	}

	for (int i = 0; i < n; i++) {
		if (!dfn[i]) Tarjan(i);
	}

	puts(totscc > 1 ? "NO" : "YES");
	return 0;
}

void Tarjan(int u) {
	static int dfs_clock = 0;
	dfn[u] = low[u] = ++dfs_clock;
	S[top++] = u, ins[u] = 1;
	for (int i = 0; i < n; i++) {
		if (!A[u][i]) continue;
		if (!dfn[i]) {
			Tarjan(i);
			low[u] = std::min(low[u], low[i]);
		} else if (ins[i]) low[u] = std::min(low[u], dfn[i]);
	}
	if (low[u] == dfn[u]) {
		for (; top && S[top - 1] != u; ) ins[S[--top]] = 0;
		ins[u] = 0, --top, ++totscc;
	}
}
