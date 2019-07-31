#include <algorithm>
#include <cstdio>
#include <vector>

const int kMaxn = 5e4 + 10;

int n, flag;
int vis[kMaxn], dis[kMaxn];
std::vector<int> G[kMaxn], V;

void Dfs(int, int);

int main() {
	scanf("%d", &n);
	
	for (int i = n, cnt; i > 1; i--) {
		cnt = 1;
		for (int j = 2; j * j <= i; j++) {
			if (i % j) continue;
			cnt += j;
			if (j * j != i) cnt += i / j;
		}
		if (cnt < i) {
			G[i].push_back(cnt); G[cnt].push_back(i);
		}
	}

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (vis[i]) continue;
		V.clear(), flag = 1;
		Dfs(i, 0);
		int k = i;
		for (auto v : V) {
			if (dis[v] > dis[k]) k = v;
		}
		dis[k] = 0, flag = 0;
		Dfs(k, 0);
		for (auto v : V)
			ans = std::max(ans, dis[v]);
	}
	printf("%d\n", ans);
	return 0;
}

void Dfs(int u, int fa) {
	vis[u] = 1;
	if (flag) V.push_back(u);
	for (auto v : G[u]) {
		if (v == fa) continue;
		dis[v] = dis[u] + 1;
		Dfs(v, u);
	}
}
