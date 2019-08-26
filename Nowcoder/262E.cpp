#include <algorithm>
#include <cstdio>

#define FORTO(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)

const int kMaxn = 2e5 + 5, kMod = 1e4 + 7;

struct Edge { int to, next; } E[kMaxn << 1];

int n, ide;
int maxw, ans;
int back[kMaxn], W[kMaxn];

void Dfs(int u, int fa, int sfa);
inline void AddEdge(int u, int v) {
	E[++ide] = {v, back[u]}, back[u] = ide;
	E[++ide] = {u, back[v]}, back[v] = ide;
}

int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		AddEdge(u, v);
	}
	for (int i = 1; i <= n; i++) scanf("%d", W + i);

	Dfs(1, 0, 0);
	(ans <<= 1) %= kMod;
	printf("%d %d\n", maxw, ans);
	return 0;
}

void Dfs(int u, int fa, int sfa) {
	if (sfa) {
		maxw = std::max(maxw, W[u] * W[sfa]);
		(ans += W[u] * W[sfa] % kMod) %= kMod;
	}
	int max1 = -1, max2 = -1, tot = 0;
	FORTO(u) {
		if (v == fa) continue;
		Dfs(v, u, fa);
		if (W[v] > max1) {
			max2 = max1, max1 = W[v];
		} else if (W[v] > max2) max2 = W[v];
		(ans += tot * W[v] % kMod) %= kMod;
		(tot += W[v]) %= kMod;
	}
	if (~max1 && ~max2) {
		maxw = std::max(maxw, max1 * max2);
	}
}
