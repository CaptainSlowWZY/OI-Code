#include <algorithm>
#include <cstdio>
#include <cstring>

#define FORTO(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)

const int kMaxn = 1e4 + 5, kMaxm = 5e4 + 5, kLg = 14, kInf = 0x3f3f3f3f;

struct Road {
	int u, v, c;
	bool operator<(const Road & r) const {
		return c > r.c;
	}
} R[kMaxm];
struct Edge {
	int to, cost, next;
} E[kMaxn << 1];

int n, m, q, cnte;
int back[kMaxn], dep[kMaxn], F[kMaxn][kLg], M[kMaxn][kLg];

namespace un {
	int fa[kMaxn];
	void Prework();
	int Find(int);
}
inline void AddEdge(const Road & r) {
	E[++cnte] = (Edge){r.v, r.c, back[r.u]}, back[r.u] = cnte;
	E[++cnte] = (Edge){r.u, r.c, back[r.v]}, back[r.v] = cnte;
}
void Dfs(int);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
		scanf("%d%d%d", &R[i].u, &R[i].v, &R[i].c);
	std::sort(R, R + m);
	un::Prework();
	for (int i = 0, u, v, cnt = 0; i < m; i++) {
		using namespace un;
		u = Find(R[i].u), v = Find(R[i].v);
		if (u == v) continue;
		fa[u] = v; AddEdge(R[i]);
		if (++cnt == n - 1) break;
	}
	memset(M, 0x3f, sizeof M); Dfs(1);
	scanf("%d", &q);
	for (int u, v, res; q--; ) {
		scanf("%d%d", &u, &v);
		if (un::Find(u) != un::Find(v)) {
			puts("-1"); continue;
		}
		if (dep[u] < dep[v]) std::swap(u, v);
		res = kInf;
		for (int i = 0, d = dep[u] - dep[v];
				(1 << i) <= d; i++)
			if (d >> i & 1) {
				res = std::min(res, M[u][i]);
				u = F[u][i];
			}
		if (u == v) { printf("%d\n", res); continue; }
		for (int i = kLg - 1; i >= 0; i--)
			if (F[u][i] != F[v][i]) {
				res = std::min(res, std::min(M[u][i], M[v][i]));
				u = F[u][i], v = F[v][i];
			}
		res = std::min(res, std::min(M[u][0], M[v][0]));
		printf("%d\n", res);
	} return 0;
}

void Dfs(int u) {
	for (int i = 1; i < kLg && F[u][i - 1]; i++) {
		F[u][i] = F[F[u][i - 1]][i - 1];
		M[u][i] = std::min(M[u][i - 1],
				M[F[u][i - 1]][i - 1]);
	}
	FORTO(u) {
		if (v == F[u][0]) continue;
		F[v][0] = u, M[v][0] = E[e].cost;
		dep[v] = dep[u] + 1; Dfs(v); 
	}
}

namespace un {
	void Prework() {
		for (int i = 1; i <= n; i++) fa[i] = i;
	}
	int Find(int x) {
		return fa[x] == x ? x : fa[x] = Find(fa[x]);
	}
}
