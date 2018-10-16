// portal
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int MAXN = 1e6 + 10;
struct Edge {
	int to, cost, next;
} E[MAXN << 1];

int last[MAXN], N, tote;
LL mxlk[MAXN], DP[MAXN];

namespace FastIO {
	template <typename T>
	void read(T & x) {
		x = 0; register char ch = getchar();
		for (; ch < '0' || ch > '9'; ch = getchar());
		for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
	}
}
inline void add_edge(int u, int v, int c) {
	E[++tote].to = v, E[tote].cost = c, E[tote].next = last[u], last[u] = tote;
	E[++tote].to = u, E[tote].cost = c, E[tote].next = last[v], last[v] = tote;
}
void dfs(int u, int fa);

int main() {
	using FastIO::read;
	read(N);
	LL ans = 0;
	for (int i = 1, ui, vi, wi; i < N; i++) {
		read(ui), read(vi), read(wi);
		add_edge(ui, vi, wi);
		ans += wi;
	}
	dfs(1, 0);
	printf("%lld\n", (ans << 1) - DP[1]);
	return 0;
}

void dfs(int u, int fa) {
	for (int e = last[u], v; e; e = E[e].next)
		if ((v = E[e].to) != fa) {
			dfs(v, u);
			mxlk[u] = std::max(mxlk[u], mxlk[v] + E[e].cost);
			DP[u] += std::max(DP[v], mxlk[v] + E[e].cost);
		}
}

// AC!!!
