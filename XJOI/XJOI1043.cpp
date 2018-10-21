// XJOI 1043
#pragma GCC diagnostic error "-std=c++11"
#include <cstdio>
#include <vector>

int N, lson[150], rson[150];
std::vector<int> G[150];

void dfs(int u) {
	int lst = u;
	for (auto v : G[u]) {
		if (lst == u) lson[u] = v, lst = v;
		else rson[lst] = v, lst = v;
		dfs(v);
	}
}

int main() {
	scanf("%d", &N);
	for (int t, s, i = 1; i <= N; i++)
		for (scanf("%d", &t); t--; ) scanf("%d", &s), G[i].push_back(s);
	dfs(1);
	printf("%d\n", N);
	for (int i = 1; i <= N; i++) printf("%d %d\n", lson[i], rson[i]);
	return 0;
}

// AC!!!
