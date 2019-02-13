// BZOJ 1060
// ZJOI 2007
#include <cstdio>
#include <algorithm>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

typedef long long LL;

const int MAXN = 5e5 + 5;

struct Edge {
	int to, cost, next;
} E[MAXN << 1];

int N, RT, tote, last[MAXN];
LL ans, UB, mxdep[MAXN];

inline void add_edge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, c, last[v]}, last[v] = tote;
}
LL dfs1(int u, int fa, LL dep);
void dfs2(int u, int fa, LL delta);

int main() {
	scanf("%d%d", &N, &RT);
	for (int i = 1, u, v, c; i < N; i++) {
		scanf("%d%d%d", &u, &v, &c);
		add_edge(u, v, c);
	}

	UB = dfs1(RT, 0, 0);
	dfs2(RT, 0, 0);

	printf("%lld\n", ans);
	return 0;
}

LL dfs1(int u, int fa, LL dep) {
	LL & mx = mxdep[u];
	mx = dep;
	forto(u) {
		if (v == fa) continue;
		mx = std::max(mx, dfs1(v, u, dep + E[e].cost));
	}
	return mx;
}

void dfs2(int u, int fa, LL delta) {
	forto(u) {
		if (v == fa) continue;
		ans += UB - mxdep[v] - delta;
		dfs2(v, u, UB - mxdep[v]);
	}
}
