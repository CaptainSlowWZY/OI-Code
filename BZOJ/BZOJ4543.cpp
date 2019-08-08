#include <algorithm>
#include <cstdio>

#define FORTO(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)

typedef long long LL;

const int kMaxn = 1e5 + 10;

struct Edge {
	int to, next;
} E[kMaxn << 1];

int n, tote;
int back[kMaxn], len[kMaxn], son[kMaxn];
LL ans;
LL *F[kMaxn], *G[kMaxn], pool[kMaxn << 2], *pit = pool;

inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, back[v]}, back[v] = tote;
}
LL *New(int size) {
	LL *ptr = pit; pit += size << 1;
	return ptr;
}
void Dfs1(int u, int fa);
void Dfs2(int u, int fa);

int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		AddEdge(u, v);
	}
	Dfs1(1, 0);
	F[1] = New(len[1]), G[1] = New(len[1]);
	Dfs2(1, 0);
	printf("%lld\n", ans);
	return 0;
}

void Dfs1(int u, int fa) {
	son[u] = -1;
	FORTO(u) {
		if (v == fa) continue;
		Dfs1(v, u);
		if (son[u] == -1 || len[v] > len[son[u]]) son[u] = v;
	} len[u] = (~son[u] ? len[son[u]] : 0) + 1;
}

void Dfs2(int u, int fa) {
	if (~son[u]) {
		F[son[u]] = F[u] + 1, G[son[u]] = G[u] - 1;
		Dfs2(son[u], u);
	}
	F[u][0] = 1, ans += G[u][0];;
	FORTO(u) {
		if (v == fa || v == son[u]) continue;
		F[v] = New(len[v]), G[v] = New(len[v]); Dfs2(v, u);
		for (int i = 0; i < len[v]; i++) {
			ans += G[u][i + 1] * F[v][i];
			ans += G[v][i + 1] * F[u][i];
		}
		for (int i = 0; i < len[v]; i++) {
			G[u][i + 1] += F[u][i + 1] * F[v][i];
			G[u][i] += G[v][i + 1];
			F[u][i + 1] += F[v][i];
		}
	}
}
