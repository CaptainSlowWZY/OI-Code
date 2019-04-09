// Kruskal-rebuild-tree template
#include <cstdio>
#include <algorithm>

#define forto(_) for (int e = last[_], v = E[e].to; e; \
						v = E[e = E[e].next].to)

const int kMaxn = 30010, kLgN = 15;

struct Eset {
	int u, v, c;
	bool operator<(const Eset & e) const {
		return c < e.c;
	}
} G[kMaxn];
struct Edge {
	int to, next;
} E[kMaxn];

int n, m, k, tote;
int last[kMaxn], F[kMaxn][kLgN], L[kMaxn][kLgN];
int dep[kMaxn];

namespace uset {
	int fa[kMaxn << 1];
	void Init() {
		for (int i = 1; i <= (n << 1); i++) fa[i] = i;
	}
	int Find(int x) {
		return fa[x] == x ? x : fa[x] = Find(fa[x]);
	}
}
inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
}
void Dfs(int u);

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &G[i].u, &G[i].v, &G[i].c);
	}

	std::sort(G, G + m);
	uset::Init();
	int newn = n;
	for (int i = 0, cnt = 1, x, y; i < m; i++) {
		using namespace uset;
		if (Find(G[i].u) == Find(G[i].v)) continue;
		x = Find(G[i].u), y = Find(G[i].v);
		fa[x] = fa[y] = ++newn;
		L[x][0] = L[y][0] = G[i].c;
		AddEdge(newn, x), AddEdge(newn, y);
		if (++cnt == n) break;
	}
	Dfs(newn);

	for (int u, v, ans; k--; ) {
		scanf("%d%d", &u, &v);
		if (dep[u] < dep[v]) std::swap(u, v);
		ans = 0;
		for (int i = 0, del = dep[u] - dep[v]; (1 << i) <= del; i++) {
			if (del >> i & 1) {
				ans = std::max(ans, L[u][i]);
				u = F[u][i];
			}
		}
		if (u ^ v) {
			for (int i = kLgN - 1; i >= 0; i--) {
				if (F[u][i] ^ F[v][i]) {
					ans = std::max(ans, std::max(L[u][i], L[v][i]));
					u = F[u][i], v = F[v][i];
				}
			}
			ans = std::max(ans, std::max(L[u][0], L[v][0]));
		}
		printf("%d\n", ans);
	}
	return 0;
}

void Dfs(int u) {
	for (int i = 1; i < kLgN && F[u][i - 1]; i++) {
		F[u][i] = F[F[u][i - 1]][i - 1];
		L[u][i] = std::max(L[u][i - 1], L[F[u][i - 1]][i - 1]);
	}
	forto(u) {
		if (v == F[u][0]) continue;
		dep[v] = dep[u] + 1, F[v][0] = u;
		Dfs(v);
	}
}
