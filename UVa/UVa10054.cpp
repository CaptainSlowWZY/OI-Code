#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

typedef std::pair<int, int> Pii;

int N, G[55][55], dgr[55];
// std::vector<Pii> ans;

void solve();

int main() {
	int t;
	scanf("%d", &t);
	for (int cs = 1; cs <= t; cs++) {
		printf("Case #%d\n", cs);
		solve();
		if (cs != t) putchar('\n');
	}

	return 0;
}

void dfs(int u) {
	for (int v = 1; v <= 50; v++)
		if (G[u][v]) {
			--G[u][v], --G[v][u];
			dfs(v);
			printf("%d %d\n", v, u);
		}
}

void solve() {
	memset(G, 0, sizeof G);
	memset(dgr, 0, sizeof dgr);
//	ans.clear();

	scanf("%d", &N);
	for (int i = 0, u, v; i < N; i++) {
		scanf("%d%d", &u, &v);
		++G[u][v], ++G[v][u];
		++dgr[u], ++dgr[v];
	}

	std::vector<int> O;
	for (int i = 1; i <= 50; i++)
		if (dgr[i] & 1) O.push_back(i);
	if (O.empty()) {
		for (int i = 1; i <= 50; i++)
			if (dgr[i]) {
				dfs(i);
				break;
			}
//		for (auto p : ans) printf("%d %d\n", p.first, p.second);
	}
	else puts("some beads may be lost");
}
