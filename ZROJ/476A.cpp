#include <algorithm>
#include <cstdio>
#include <vector>

#define pb push_back

int n;
std::vector<int> G[100005];

int Dfs(int);

int main() {
	scanf("%d", &n);
	for (int fa, i = 2; i <= n; ++i) {
		scanf("%d", &fa); G[fa].pb(i);
	} puts(Dfs(1) ? "Y" : "D");
	return 0;
}

int Dfs(int u) {
	if (G[u].empty()) return 1;
	int res = 0;
	for (std::vector<int>::iterator it = G[u].begin(); it != G[u].end(); ++it) res += Dfs(*it);
	return std::max(res - 1, 0);
}
