#include <cstdio>
#include <vector>

#define pb push_back

const int kMaxn = 1e5 + 5;

int n, m, cnte, cntv;
int vis[kMaxn];
std::vector<int> G[kMaxn];

void Dfs(int u);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0, u, v; i < m; ++i) {
		scanf("%d%d", &u, &v);
		G[u].pb(v); G[v].pb(u);
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (vis[i]) continue;
		cnte = cntv = 0; Dfs(i);
		ans += cnte / 2 - cntv + 1;
	} printf("%d\n", ans);
}

void Dfs(int u) {
	vis[u] = 1;
	++cntv, cnte += G[u].size();
	for (auto v : G[u]) {
		if (vis[v]) continue;
		Dfs(v);
	}
}
