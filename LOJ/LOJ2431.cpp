#include <algorithm>
#include <cstdio>
#include <vector>

#define pb push_back

typedef long long LL;

const int kMaxn = 5010;

int n;
int cnt[kMaxn];
LL mg[3][kMaxn];
std::vector<int> G[kMaxn];

void Dfs(int, int, int);

int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		G[u].pb(v), G[v].pb(u);
	} LL ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 3; j++)
			std::fill(mg[j], mg[j] + kMaxn, 0ll);
		for (auto v : G[i]) {
			std::fill(cnt, cnt + n, 0);
			Dfs(v, i, 1);
			for (int i = 1; i <= n; i++) {
				if (!cnt[i]) break;	
				mg[2][i] += 1ll * mg[1][i] * cnt[i];
				mg[1][i] += 1ll * mg[0][i] * cnt[i];
				mg[0][i] += cnt[i];
			}
		}
		for (int i = 1; i <= n; i++) ans += mg[2][i];
	}
	printf("%lld\n", ans);
	return 0;
}

void Dfs(int u, int fa, int dep) {
	++cnt[dep];
	for (auto v : G[u]) {
		if (v == fa) continue;
		Dfs(v, u, dep + 1);
	}
}
