// HAOI 2015
#include <cstdio>
#include <algorithm>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

typedef long long LL;

const int kMaxn = 2010;

struct Edge {
	int to, cost, next;
} E[kMaxn << 1];

int n, k, tote, last[kMaxn], sz[kMaxn];
LL DP[kMaxn][kMaxn];

inline void AddEdge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, c, last[v]}, last[v] = tote;
}
template <typename T>
inline void Umax(T & x, T y) {
	x < y ? x = y : 0;
}
void Dfs(int u, int fa);

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1, u, v, dis; i < n; i++) {
		scanf("%d%d%d", &u, &v, &dis);
		AddEdge(u, v, dis);
	}

	Dfs(1, 0);

	printf("%lld\n", DP[1][k]);
	return 0;
}

void Dfs(int u, int fa) {
	sz[u] = 1;
	static LL buf[kMaxn];
	forto(u) {
		if (v == fa) continue;
		Dfs(v, u);
		for (int i = 0; i <= sz[u]; i++) buf[i] = DP[u][i];
		for (int i = std::min(k, sz[u]); i >= 0; i--) {
			for (int j = std::min(sz[v], k); j >= 0; j--) {
				Umax(DP[u][i + j], DP[v][j] + buf[i] +
					E[e].cost * (j * LL(k - j) + LL(sz[v] - j) * (n - k - sz[v] + j)));
			}
		}
		sz[u] += sz[v];
	}
}
