#include <cstdio>
#include <vector>

#define pb push_back
#define FORV(v, G) for (std::vector<int>::iterator v = G.begin(); v != G.end(); ++v)

typedef long long LL;

const int kMaxn = 18;

int n, m, cnta;
int A[kMaxn], G[kMaxn][kMaxn];
LL DP[kMaxn][kMaxn];
std::vector<int> T[kMaxn];

void Dfs(int, int);

int main() {
	scanf("%d%d", &n, &m);
	for (int u, v; m--; ) { scanf("%d%d", &u, &v); --u, --v; G[u][v] = G[v][u] = 1; }
	for (int i = 1, u, v; i < n; ++i) { scanf("%d%d", &u, &v); T[--u].pb(--v); T[v].pb(u); }
	LL ans = 0;
	for (int s = (1 << n) - 1; ~s; --s) {
		for (int i = cnta = 0; i < n; ++i) if (s >> i & 1) A[cnta++] = i;
		Dfs(0, -1);
		LL t = 0;
		for (int i = 0; i < cnta; ++i) t += DP[0][i];
		ans += n - __builtin_popcount(s) & 1 ? -t : t;
	} printf("%lld\n", ans);
	return 0;
}

void Dfs(int u, int fa) {
	for (int i = 0; i < cnta; ++i) DP[u][i] = 1;
	FORV(v, T[u]) if (*v != fa) {
		Dfs(*v, u);
		for (int i = 0, x; i < cnta; ++i) {
			x = A[i];
			LL tmp = 0;
			for (int j = 0, y; j < cnta; ++j) if (G[x][y = A[j]]) tmp += DP[*v][j];
			DP[u][i] *= tmp;
		}
	}
}
