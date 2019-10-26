#include <algorithm>
#include <cstdio>
#include <vector>

#define pb push_back

typedef long long LL;

const int kMaxn = 1e5 + 5, kLg = 18;

int n;
int dep[kMaxn], F[kMaxn][kLg], sz[kMaxn];
LL ds[kMaxn], dsu[kMaxn];
std::vector<int> G[kMaxn];

void Dfs1(int);
void Dfs2(int);

int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		G[u].pb(v); G[v].pb(u);
	} dep[1] = 1; Dfs1(1); Dfs2(1);
	LL ans = ds[1];
	for (int u, i = 2; i <= n; ++i) {
		u = i;
		for (int j = kLg - 1; j >= 0; --j) {
			if (F[u][j] && 2 * dep[F[u][j]] - 2 > dep[i])
				u = F[u][j];
		} // u : the highest vertex going down
//		printf(" i = %d, u = %d\n", i, u);
		LL sum = ds[i] + sz[i];
		if (i != u) 
			sum += dsu[i] - (dsu[u] + LL(n - sz[u]) * (dep[i] - dep[u])) + sz[u] - sz[i];
		sum += ds[1] - (ds[u] + LL(dep[u] - 1) * sz[u]);
//		printf("    sum = %lld\n", sum);
		ans = std::min(ans, sum);
	} printf("%lld\n", ans);
	return 0;
}

void Dfs1(int u) {
	for (int i = 1; i < kLg && F[u][i - 1]; ++i)
		F[u][i] = F[F[u][i - 1]][i - 1];
	sz[u] = 1;
	for (auto v : G[u]) {
		if (v == F[u][0]) continue;
		dep[v] = dep[u] + 1, F[v][0] = u; Dfs1(v);
		sz[u] += sz[v], ds[u] += ds[v] + sz[v];
	}
}

void Dfs2(int u) {
	dsu[u] += n - sz[u];
	for (auto v : G[u]) {
		if (v == F[u][0]) continue;
		dsu[v] = dsu[u] + ds[u] - (ds[v] + sz[v]);
		Dfs2(v);
	}
}
