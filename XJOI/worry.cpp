// worry
#include <cstdio>
#include <cstring>
#include <algorithm>
const int MAXN = 1e5 + 10;
const int Lg_N = 18;
const int INF = 0x7f7f7f7f;

typedef int IntAr[MAXN];

struct Edge {
	int to, id, next;
} E[MAXN << 1];
struct Path {
	int u, v, cost;
	bool operator<(const Path & p) const {
		return cost < p.cost;
	}
} P[MAXN];

int N, M, tote = 1, F[MAXN][Lg_N], totl;
IntAr efa, dep, ans, last, col, link;

namespace FastIO {
	template <typename T>
		void read(T & x) {
			x = 0; register char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
}
namespace USet {
	int fa[MAXN];

	void init() { for (int i = 1; i <= N; i++) fa[i] = i; }
	int find(int x) { return fa[x] == x ? x : (fa[x] = find(fa[x])); }
	void merge(int x, int y) {
		x = find(x), y = find(y);
		if (x != y) fa[x] = y;
	}
}
inline void add_edge(int u, int v, int id_) {
	E[++tote].to = v, E[tote].id = id_, E[tote].next = last[u], last[u] = tote;
	E[++tote].to = u, E[tote].id = id_, E[tote].next = last[v], last[v] = tote;
}
inline void upd_min(int & x, int y) { x = std::min(x, y); }
void dfs(int u);
int lca(int u, int v);

int main() {
#ifndef ONLINE_JUDGE
	freopen("worry.in", "r", stdin);
	freopen("worry.out", "w", stdout);
#endif
	using FastIO::read;
	read(N), read(M);
	for (int i = 1, ai, bi; i < N; i++) {
		read(ai), read(bi);
		add_edge(ai, bi, i);
	}
	for (int i = 0; i < M; i++) read(P[i].u), read(P[i].v), read(P[i].cost);
	USet::init();
	std::sort(P, P + M);
	dep[1] = 1;
	dfs(1);
	memset(ans, 0x7f, sizeof ans);
	for (int i = 0; i < M; i++) {
		using USet::find;
		int u0 = P[i].u, v0 = P[i].v, l = lca(u0, v0);
		for (totl = 0; find(u0) != find(l); u0 = E[efa[u0]].to) upd_min(ans[E[efa[u0]].id], P[i].cost), link[totl++] = u0;
		for (; find(v0) != find(l); v0 = E[efa[v0]].to) upd_min(ans[E[efa[v0]].id], P[i].cost), link[totl++] = v0;
		for (int j = 0; j < totl; j++) efa[link[j]] = efa[l], USet::merge(link[j], l);
	}
	for (int i = 1; i < N; i++) printf("%d\n", ans[i] == INF ? -1 : ans[i]);
#ifndef ONLINE_JUDGE
	fclose(stdin); fclose(stdout);
#endif
	return 0;
}

void dfs(int u) {
	for (int i = 1; i < Lg_N && F[u][i - 1]; i++) F[u][i] = F[F[u][i - 1]][i - 1];
	for (int v, e = last[u]; e; e = E[e].next) {
		if ((v = E[e].to) == F[u][0]) continue;	   
		efa[v] = e ^ 1, dep[v] = dep[u] + 1, F[v][0] = u;
		dfs(v);
	}
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) std::swap(u, v);
	for (int i = Lg_N - 1; i >= 0; i--)
		if (dep[F[u][i]] >= dep[v]) u = F[u][i];
	if (u == v) return u;
	for (int i = Lg_N - 1; i >= 0; i--)
		if (F[u][i] != F[v][i]) u = F[u][i], v = F[v][i];
	return F[u][0];
}