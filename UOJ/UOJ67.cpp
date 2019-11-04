#include <cstdio>
#include <vector>

#define SZ(_) (int)_.size()
#define pb push_back

const int kMaxn = 1e5 + 5;

typedef int Arr[kMaxn];

int n, m, dfsc;
Arr deg, dfn, low, fa, isc;
std::vector<int> G[kMaxn], ans;

template <typename T> inline
void UMin(T & x, const T & y) { if (x > y) x = y; }
inline int Find(int x) {
	return fa[x] == x ? x : (fa[x] = Find(fa[x]));
}
inline void AddEdge(int u, int v) {
	G[u].pb(v); G[v].pb(u); ++deg[u], ++deg[v];
	fa[Find(u)] = Find(v);
}
void Dfs(int, int);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) fa[i] = i;
	for (int i = 0, u, v; i < m; ++i) {
		scanf("%d%d", &u, &v); AddEdge(u, v);
	}
	int cnt = 0;
	for (int i = 1; i <= n; ++i) cnt += Find(i) == i;
	if (cnt > 1) {
		for (int i = 1; i <= n; ++i)
			if (!deg[i]) { printf("1\n%d\n", i); break; }
		return 0;
	} Dfs(1, 0);
	for (int i = 1; i <= n; ++i) {
		if (isc[i]) continue;
		if (m - deg[i] == n - 2) ans.pb(i);
	} printf("%d\n", SZ(ans));
	for (int i = 0; i < SZ(ans); ++i) printf("%d ", ans[i]);
	puts(""); return 0;
}

void Dfs(int u, int fa) {
	int son = 0; dfn[u] = low[u] = ++dfsc;
	for (int i = 0, v; i < SZ(G[u]); ++i) {
		if ((v = G[u][i]) == fa) continue;
		if (!dfn[v]) {
			Dfs(v, u); UMin(low[u], low[v]);
			if (low[v] >= dfn[u]) {
				if (u > 1) isc[u] = 1; else ++son;
			}
		} else UMin(low[u], dfn[v]);
	} if (u == 1 && son > 1) isc[u] = 1;
}
