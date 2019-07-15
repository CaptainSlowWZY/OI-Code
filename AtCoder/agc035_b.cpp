#include <cstdio>

#define forto(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)

const int kMaxn = 1e5 + 10;

struct Edge {
	int to, next;
} E[kMaxn << 1];

int n, m, tote, dfs_clock;
int back[kMaxn], dfn[kMaxn], odeg[kMaxn];

inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, back[v]}, back[v] = tote;
}
void Dfs(int, int);

int main() {
	scanf("%d%d", &n, &m);
	if (m & 1) {
		puts("-1");
		return 0;
	}
	for (int i = 0, u, v; i < m; i++) {
		scanf("%d%d", &u, &v);
		AddEdge(u, v);
	}

	Dfs(1, 0);
	return 0;
}

void Dfs(int u, int fa) {
	dfn[u] = ++dfs_clock;
	forto(u) {
		if (v == fa) continue;
		if (!dfn[v]) Dfs(v, u);
		else if (dfn[v] < dfn[u]) {
			++odeg[u];
			printf("%d %d\n", u, v);
		}
	}
	if (u == 1) return;
	if (odeg[u] & 1) {
		++odeg[u];
		printf("%d %d\n", u, fa);
	} else {
		++odeg[fa];
		printf("%d %d\n", fa, u);
	}
}
