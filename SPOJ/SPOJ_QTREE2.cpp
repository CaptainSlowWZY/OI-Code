// SPOJ QTREE II
#include <cstdio>
#include <cstring>
#include <algorithm>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int MAXV = 1e4 + 10;
const int Lg_N = 14;

struct Edge {
	int to, cost, next;
} E[MAXV << 1];

int N, tote, last[MAXV], dep[MAXV], F[MAXV][Lg_N + 1];
long long D[MAXV];

void solve();

int main() {
	int t;
	for (scanf("%d", &t); t--; ) solve();

	return 0;
}

void dfs(int u) {
	for (int i = 1; i <= Lg_N && F[u][i - 1]; i++) F[u][i] = F[F[u][i - 1]][i - 1];
	forto(u) {
		if (v == F[u][0]) continue;
		F[v][0] = u, dep[v] = dep[u] + 1, D[v] = D[u] + E[e].cost;
		dfs(v);
	}
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) std::swap(u, v);
	for (int i = 0, delta = dep[u] - dep[v]; (1 << i) <= delta; i++)
		if (delta >> i & 1) u = F[u][i];
	if (u == v) return u;
	for (int i = Lg_N; i >= 0; i--)
		if (F[u][i] != F[v][i]) u = F[u][i], v = F[v][i];
	return F[u][0];
}

inline long long dist(int u, int v) {
	return D[u] + D[v] - 2 * D[lca(u, v)];
}

int query(int u, int v, int k) {
	int l = lca(u, v);
	if (k <= dep[u] - dep[l] + 1) {
		--k;
		for (int i = 0; i <= Lg_N && (1 << i) <= k; i++)
			 if (k >> i & 1) u = F[u][i];
		return u;
	}
	else {
		k -= dep[u] - dep[l] + 1;
		k = dep[v] - dep[l] - k;
		for (int i = 0; i <= Lg_N && (1 << i) <= k; i++)
			if (k >> i & 1) v = F[v][i];
		return v;
	}
}

inline void add_edge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, c, last[v]}, last[v] = tote;
}

void solve() {
	tote = 0;
	memset(last, 0, sizeof last);
	memset(F, 0, sizeof F);

	scanf("%d", &N);
	for (int i = 1, u, v, c; i < N; i++) {
		scanf("%d%d%d", &u, &v, &c);
		add_edge(u, v, c);
	}
	
	dep[1] = 1;
	dfs(1);

	char O[8];
	scanf("%s", O);
	for (int x, y, z; O[1] != 'O'; scanf("%s", O)) {
		if (O[0] == 'D') {
			scanf("%d%d", &x, &y);
			printf("%lld\n", dist(x, y));
		}
		else {
			scanf("%d%d%d", &x, &y, &z);
			printf("%d\n", query(x, y, z));
		}
	}
}
