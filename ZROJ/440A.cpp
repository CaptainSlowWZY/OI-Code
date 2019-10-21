#include <cstdio>
#include <vector>

#define pb push_back

int n;
std::vector<int> G[300010];

void Dfs(int, int);

int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		G[u].pb(v); G[v].pb(u);
	} puts("Yes");
	Dfs(1, 0); putchar('\n');
	return 0;
}

void Dfs(int u, int fa) {
	printf("%d ", u);
	for (auto v : G[u]) {
		if (v == fa) continue;
		for (auto x : G[v]) {
			if (x == v || x == u) continue;
			Dfs(x, v);
		} printf("%d ", v);
	}
}
