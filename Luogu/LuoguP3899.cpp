#include <algorithm>
#include <cstdio>
#include <vector>
#include <cassert>

#define fir first
#define sec second
#define pb push_back

typedef long long LL;
typedef std::pair<int, int> Pii;

const int kMaxn = 3e5 + 10;

int n, q;
int len[kMaxn], sz[kMaxn], son[kMaxn], dep[kMaxn];
int len2[kMaxn], son2[kMaxn];
LL *sum[kMaxn], pool[kMaxn], *pit = pool, ans[kMaxn];
std::vector<int> G[kMaxn];
std::vector<Pii> Q[kMaxn];

LL *New(int hsz) {
	LL *ptr = pit; pit += hsz;
	return ptr;
}
void Dfs1(int u, int fa);
void Dfs2(int u, int fa);

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		G[u].pb(v), G[v].pb(u);
	}
	for (int i = 0, u, k; i < q; i++) {
		scanf("%d%d", &u, &k);
		Q[u].pb(Pii(k, i));
	} dep[1] = 1; Dfs1(1, 0);
	sum[1] = New(len[1]); Dfs2(1, 0);
	for (int i = 0; i < q; i++) printf("%lld\n", ans[i]);
	return 0;
}

void Dfs1(int u, int fa) {
	sz[u] = 1, son[u] = -1;
	for (auto v : G[u]) {
		if (v == fa) continue;
		dep[v] = dep[u] + 1; Dfs1(v, u); sz[u] += sz[v];
		if (son[u] == -1 || len[v] > len[son[u]]) son[u] = v;
	} len[u] = (~son[u] ? len[son[u]] : 0) + 1;
}

void Dfs2(int u, int fa) {
	sum[u][0] = sz[u] - 1;
	if (~son[u]) {
		sum[son[u]] = sum[u] + 1;
		Dfs2(son[u], u);
		sum[u][0] += sum[u][1];
	}
	for (auto v : G[u]) {
		if (v == fa || v == son[u]) continue;
		sum[v] = New(len[v]); Dfs2(v, u);
		for (int i = 0; i < len[v]; i++)
			sum[u][i + 1] += sum[v][i];
		sum[u][0] += sum[v][0];
	}
	for (const auto & p : Q[u]) {
		ans[p.sec] = 1ll * (sz[u] - 1) * std::min(dep[u] - 1, p.fir) +
			sum[u][1] - (p.fir + 1 >= len[u] ? 0 : sum[u][p.fir + 1]);
	}
}
