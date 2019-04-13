// path
#include <cstdio>
#include <algorithm>

const int kMaxn = 1e5 + 10, kLgN = 18;

typedef int IAr[kMaxn];

namespace solver1 {
	void Solve();
}
namespace solver2 {
	void Solve();
}
int Lca(int u, int v);
void Dfs(int u);

struct Edge { int to, next; } E[kMaxn << 1];
struct Path { int u, v, c; } P[kMaxn];

int n, m, tote, totp;
int F[kMaxn][kLgN];
IAr back, backp, nextp, dep, DP, sson;

inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, back[v]}, back[v] = tote;
}
inline void PushBack(int l, const Path & p) {
	P[++totp] = p, nextp[totp] = backp[l], backp[l] = totp;
}

int main() {
	scanf("%d", &n);
	int is_link = 1;
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		if (u > v) std::swap(u, v);
		AddEdge(u, v);
		is_link &= u + 1 == v;
	}

	dep[1] = 1;
	Dfs(1);

	scanf("%d", &m);

	for (int i = 0, u, v, l, c; i < m; i++) {
		scanf("%d%d%d", &u, &v, &c);
		if (dep[u] > dep[v]) std::swap(u, v);
		l = Lca(u, v);
		PushBack(l, (Path){u, v, c});
	}

	if (is_link) solver2::Solve();
	else solver1::Solve();

	return 0;
}

int Lca(int u, int v) {
	if (dep[u] < dep[v]) std::swap(u, v);
	for (int i = 0, del = dep[u] - dep[v]; (1 << i) <= del; i++) {
		if (del >> i & 1) u = F[u][i];
	}
	if (u == v) return u;
	for (int i = kLgN - 1; i >= 0; i--) {
		if (F[u][i] ^ F[v][i]) {
			u = F[u][i], v = F[v][i];
		}
	}
	return F[u][0];
}

#define forto(_) for (int e = back[_], v = E[e].to; e; \
			v = E[e = E[e].next].to)

void Dfs(int u) {
	for (int i = 1; i < kLgN && F[u][i - 1]; i++) {
		F[u][i] = F[F[u][i - 1]][i - 1];
	}
	forto(u) {
		if (v == F[u][0]) continue;
		F[v][0] = u, dep[v] = dep[u] + 1;
		Dfs(v);
	}
}

#define cross(_) for (int p = backp[_]; p; p = nextp[p])

namespace solver2 {
	void Solve() {
		for (int i = n - 1; i > 0; i--) {
			DP[i] = DP[i + 1];
			cross(i) DP[i] = std::max(DP[i], DP[P[p].v + 1] + P[p].c);
		}
		printf("%d\n", DP[1]);
	}
}

#define fa(_) (F[_][0])

namespace solver1 {
	int Dfs(int u) {
		forto(u) {
			if (v == fa(u)) continue;
			sson[u] += Dfs(v);
		}
		cross(u) {
			Path & e = P[p];
			int sum = sson[e.v];
			for (int & v = e.v; dep[v] > dep[e.u]; v = fa(v)) {
				sum += sson[fa(v)] - DP[v];
			}
			if (e.v ^ e.u) {
				sum += sson[e.u];
				for (int & u0 = e.u, & v0 = e.v; fa(u0) ^ fa(v0); 
						u0 = fa(u0), v0 = fa(v0)) {
					sum += sson[fa(u0)] - DP[u0] + sson[fa(v0)] - DP[v0];
				}
				sum += sson[u] - DP[e.u] - DP[e.v];
			}
			DP[u] = std::max(DP[u], sum + e.c);
		}
		return DP[u] = std::max(DP[u], sson[u]);
	}
	void Solve() {
		printf("%d\n", Dfs(1));
	}
}
