#include <cstdio>
#include <vector>

#define pb push_back

const int kMaxn = 1e6 + 10;

int n;
int son[kMaxn], len[kMaxn], ans[kMaxn];
int *D[kMaxn], pool[kMaxn], *pit = pool;

std::vector<int> G[kMaxn];

int *New(int size) {
	int *ptr = pit; pit += size; return ptr;
}
void Dfs1(int u, int fa);
void Dfs2(int u, int fa);

int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		G[u].pb(v), G[v].pb(u);
	} Dfs1(1, 0); D[1] = New(len[1]); Dfs2(1, 0);
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}

void Dfs1(int u, int fa) {
	son[u] = -1;
	for (auto v : G[u]) {
		if (v == fa) continue;
		Dfs1(v, u);
		if (son[u] == -1 || len[v] > len[son[u]]) son[u] = v;
	} len[u] = (~son[u] ? len[son[u]] : 0) + 1;
}

void Dfs2(int u, int fa) {
	D[u][ans[u] = 0] = 1;
	if (~son[u]) {
		D[son[u]] = D[u] + 1;
		Dfs2(son[u], u);
		if (D[u][ans[son[u]] + 1] > D[u][ans[u]])
			ans[u] = ans[son[u]] + 1;
	}
	for (auto v : G[u]) {
		if (v == fa || v == son[u]) continue;
		D[v] = New(len[v]); Dfs2(v, u);
		for (int i = 0; i < len[v]; i++) {
			if ((D[u][i + 1] += D[v][i]) > D[u][ans[u]] ||
				D[u][i + 1] == D[u][ans[u]] && i + 1 < ans[u])
				ans[u] = i + 1;
		}
	}
}
