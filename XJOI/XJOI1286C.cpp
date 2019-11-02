#include <algorithm>
#include <cstdio>
#include <vector>

#define fi first
#define se second
#define pb push_back

typedef long long LL;
typedef std::pair<int, int> Pii;

const int kMaxn = 5005;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;

int n, w, sz[kMaxn];
LL ans, DP[kMaxn][kMaxn];
std::vector<Pii> G[kMaxn];

template <typename T> inline
void UMin(T & x, const T & y) { if (x > y) x = y; }
void Dfs(int u, int fa);

int main() {
	scanf("%d%d", &n, &w);
	for (int i = 1, x, y, z; i < n; ++i) {
		scanf("%d%d%d", &x, &y, &z);
		G[x].pb({y, z}); G[y].pb({x, z});
	} Dfs(1, 0); ans -= DP[1][w];
	printf("%lld\n", ans);
	return 0;
}

void Dfs(int u, int fa) {
	static LL nxt[kMaxn];
	sz[u] = 1;
	for (auto & e : G[u]) {
		int v = e.fi;
		if (v == fa) continue;
		Dfs(v, u); ans += (LL)e.se * sz[v] * (n - sz[v]);
		for (int i = 0; i <= sz[u] + sz[v]; ++i) nxt[i] = kInf64; 
		for (int i = 0; i <= sz[u]; ++i) {
			for (int j = 0, o, ow; j <= sz[v]; ++j) {
				ow = w - j, o = n - sz[v];
				UMin(nxt[i + j], DP[u][i] + DP[v][j] +
						((LL)j * (o - ow) + (LL)ow * (sz[v] - j)) * e.se);
			}
		} sz[u] += sz[v];
		for (int i = 0; i <= sz[u]; ++i) DP[u][i] = nxt[i];
	}
}
