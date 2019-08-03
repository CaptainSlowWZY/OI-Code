#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

#define pb push_back

typedef std::vector<int> vec;

const int kMaxn = 65, kMaxk = 35, kMaxv = 1005, kInf = 0x3f3f3f3f, kMaxm = 245;

int n, m, v, k;
int cost[kMaxn][kMaxk], pay[kMaxn], DP[kMaxv][kMaxk], vis[kMaxn];
// std::vector<vec> way[kMaxn];
vec need[kMaxm];
int id[kMaxm];
int buf[2][kMaxk];

template <typename T> inline
void UMin(T & x, const T & y) {
	if (x > y) x = y;
}
template <typename T> inline
void UMax(T & x, const T & y) {
	if (x < y) x = y;
}
void Dfs(int);

int main() {
	scanf("%d%d%d%d", &n, &m, &v, &k);
	for (int i = 1; i <= n; i++) scanf("%d%d", cost[i], pay + i);
	for (int i = 0, sz; i < m; i++) {
		scanf("%d%d", id + i, &sz);
		for (int o; sz--; ) {
			scanf("%d", &o); need[i].pb(o);
		}
	}
/*	for (int i = 1; i <= n; i++) {
		if (!vis[i]) Dfs(i);
	}*/
	int *prv = buf[0], *nxt = buf[1];
	for (int i = 1; i <= n; i++) {
		std::fill(cost[i] + 1, cost[i] + k + 1, kInf);
	}
	for (int i = 1; i <= k; i++) {
		for (int j = 0; j < m; j++) {
			std::fill(prv, prv + k + 1, kInf);
			prv[0] = 0;
			for (auto u : need[j]) {
				std::fill(nxt, nxt + k + 1, kInf);
				for (int l = 0; l < i; l++) {
					for (int o = 0; o <= l; o++) {
						UMin(nxt[l], prv[l - o] + cost[u][o]);
					}
				} std::swap(prv, nxt);
			}
			UMin(cost[id[j]][i], prv[i - 1]);
		}
	}

	memset(DP, 0x80, sizeof DP);
	DP[0][0] = 0;
	for (int l = 1; l <= n; l++) {
		for (int c = 0; c <= k; c++) {
			if (cost[l][c] == kInf) continue;
		//	printf(" cost[%d][%d] = %d\n", l, c, cost[l][c]);
			for (int i = cost[l][c]; i <= v; i++) {
				for (int j = c; j <= k; j++)
					UMax(DP[i][j], DP[i - cost[l][c]][j - c] +
							pay[l] - cost[l][c]);
			}
		}
	}
	int ans = 0;
	for (int i = 0; i <= v; i++) {
		for (int j = 0; j <= k; j++)
			UMax(ans, DP[i][j]);
	} printf("%d\n", ans);
	return 0;
}
/*
void Dfs(int u) {
	vis[u] = 1;
	int *dp = cost[u];
	std::fill(dp + 1, dp + k + 1, kInf);
	static int buf[2][kMaxk];
	int *prv = buf[0], *nxt = buf[1];
	for (auto & w : way[u]) {
	//	printf("  %d way !\n", u);
		std::fill(prv, prv + k + 1, kInf);
		prv[0] = 0;
		for (auto & v : w) {
			if (!vis[v]) Dfs(v);
		//	printf("    merge %d\n", v);
			std::fill(nxt, nxt + k + 1, kInf);
			for (int i = k; i >= 0; i--) {
				for (int j = 0; j <= i; j++) {
					UMin(nxt[i], cost[v][j] + prv[i - j]);
				}
			}
			std::swap(prv, nxt);
		}
		for (int i = 0; i < k; i++) UMin(dp[i + 1], prv[i]);
	}
}*/
