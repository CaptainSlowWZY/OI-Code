// XJOI 1049
#pragma GCC diagnostic error "-std=c++11"
#include <cstdio>
#include <vector>
#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#define pb push_back
const int ARSIZE = 10000;

int N, dep[ARSIZE], fa[ARSIZE];
std::vector<int> G[ARSIZE];

inline void add_edge(int u, int v) { G[u].pb(v), G[v].pb(u); }
void dfs(int u, int fa);
void dfs(int u);

int main() {
	scanf("%d%*d", &N);
	for (int i = 1, x, y; i < N; i++) {
		scanf("%d%d", &x, &y);
		add_edge(x, y);
	}
	dep[1] = 1, dfs(1, 0);
	int s = -1;
	for (int i = 1; i <= N; i++)
		if (s == -1 || dep[i] > dep[s]) s = i;
	dep[s] = 1, dfs(s);
	s = -1;
	for (int i = 1; i <= N; i++)
		if (s == -1 || dep[i] > dep[s]) s = i;
	if (dep[s] & 1) {
		for (int i = dep[s] / 2; i--; s = fa[s]);
		printf("%d\n", s);
	}
	else {
		for (int i = dep[s] / 2 - 1; i--; s = fa[s]);
		int a = s < fa[s] ? s : fa[s], b = s > fa[s] ? s : fa[s];
		printf("%d %d\n", a, b);
	}
	return 0;
}

void dfs(int u, int fa) {
	for (int v : G[u]) {
		if (v == fa) continue;
		dep[v] = dep[u] + 1;
		dfs(v, u);
	}
}

void dfs(int u) {
	for (int v : G[u]) {
		if (v == fa[u]) continue;
		fa[v] = u, dep[v] = dep[u] + 1;
		dfs(v);
	}
}

// AC!!!
