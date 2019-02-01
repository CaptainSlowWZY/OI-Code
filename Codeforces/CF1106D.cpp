#include <bits/stdc++.h>
const int MAXN = 1e5 + 10;
std::vector<int> G[MAXN];
int	N, M, tot, vis[MAXN], ans[MAXN];
std::priority_queue<int, std::vector<int>, std::greater<int> > hp;
void dfs(int);
int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0, ui, vi; i < M; i++) {
		scanf("%d%d", &ui, &vi);
		G[ui].push_back(vi), G[vi].push_back(ui);
	}

	for (int i = 1; i <= N; i++) std::sort(G[i].begin(), G[i].end());
	for (hp.push(1), vis[1] = 1; !hp.empty(); ) {
		int u = hp.top(); hp.pop();
		ans[tot++] = u;
		for (auto v : G[u]) 
			if (!vis[v]) {
				vis[v] = 1;
				hp.push(v);
			}
	}

	for (int i = 0; i < N; i++) printf("%d ", ans[i]);
	putchar('\n');
	return 0;
}

