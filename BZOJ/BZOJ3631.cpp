#include <cstdio>
#include <algorithm>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int kMaxn = 3e5 + 10;

typedef int IntArr[kMaxn];

struct Edge {
	int to, next;
} E[kMaxn << 1];

int n, tote;
IntArr last, A, ans;

namespace hld {
	IntArr fa, dep, sz, son, top, dfn;

	void Dfs1(int u);
	void Dfs2(int u, int tp);
	inline void Init() {
		dep[1] = 1;
		Dfs1(1);
		Dfs2(1, 1);
	}
	void Add(int u, int v);
}
inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, last[v]}, last[v] = tote;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", A + i);
	for (int i = 1, x, y; i < n; i++) {
		scanf("%d%d", &x, &y);
		AddEdge(x, y);
	}

	hld::Init();
	for (int i = 1; i < n; i++) hld::Add(A[i - 1], A[i]);
	for (int i = 1; i <= n; i++) ans[i] += ans[i - 1];
	for (int i = 1; i < n; i++) --ans[hld::dfn[A[i]]];
	for (int i = 1; i <= n; i++) printf("%d\n", ans[hld::dfn[i]]);
	return 0;
}

namespace hld {
	void Dfs1(int u) {
		sz[u] = 1, son[u] = -1;
		forto(u) {
			if (v == fa[u]) continue;
			fa[v] = u, dep[v] = dep[u] + 1;
			Dfs1(v);
			sz[u] += sz[v];
			if (son[u] == -1 || sz[v] > sz[son[u]]) son[u] = v;
		}
	}
	void Dfs2(int u, int tp) {
		static int dfs_clock = 0;
		dfn[u] = ++dfs_clock, top[u] = tp;
		if (son[u] == -1) return;
		Dfs2(son[u], tp);
		forto(u) {
			if (v == son[u] || v == fa[u]) continue;
			Dfs2(v, v);
		}
	}
	void Add(int u, int v) {
		for (; top[u] != top[v]; u = fa[top[u]]) {
			if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
			++ans[dfn[top[u]]], --ans[dfn[u] + 1];
		}
		if (dep[u] > dep[v]) std::swap(u, v);
		++ans[dfn[u]], --ans[dfn[v] + 1];
	}
}
