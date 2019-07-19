#include <cstdio>
#include <vector>
#include <queue>

#define pb push_back

const int kMaxn = 1e5 + 10;

int n, m;
int deg[kMaxn], flag[kMaxn], ans[kMaxn];
std::vector<int> G[kMaxn], R[kMaxn];
std::queue<int> que;

void Dfs(int);
int Find();

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		G[u].pb(v), G[v].pb(u);
		++deg[u], ++deg[v];
	}
	for (int i = 0, u, v; i < m; i++) {
		scanf("%d%d", &u, &v);
		R[u].pb(v), ++deg[v], flag[u] = 1;
	}

	for (int i = 1; i <= n; i++) {
		if (deg[i] == 1) que.push(i);
	}
	int rt;
	if ((rt = Find()) == -1) {
		for (int i = 0; i < n; i++) puts("0");
		return 0;
	}

	Dfs(rt);
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);

	return 0;
}

void Dfs(int u) {
	flag[u] = ans[u] = 1;
	for (auto v : G[u]) {
		if (flag[v]) continue;
		Dfs(v);
	}
}

int Find() {
	int cnt = 0;
	for (int u; !que.empty(); ) {
		u = que.front(), que.pop(), ++cnt;
		if (!deg[u]) return u;
		for (auto v : G[u]) {
			if (--deg[v] == 1) que.push(v);
		}
		for (auto v : R[u]) {
			if (--deg[v] == 1) que.push(v);
		}
	}
	if (cnt < n) return -1;
}
