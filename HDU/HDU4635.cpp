#include <cstdio>
#include <cstring>
#include <algorithm>

#define forto(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)

const int kMaxn = 1e5 + 10;

typedef int IAr[kMaxn];

struct Edge {
	int to, next;
} E[kMaxn];

int t, n, m, tote, top, dfs_clock, cntscc;
IAr back, dfn, low, S, tag, ideg, odeg, sz, ins;

inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, back[u]}, back[u] = tote;
}
inline long long Sum(long long n) {
	return n * (n - 1);
}
void Tarjan(int u);

int main() {
	int t;
	scanf("%d", &t);
	for (int cs = 1; cs <= t; cs++) {
		scanf("%d%d", &n, &m);

		tote = 0;
		memset(back, 0, sizeof back);

		for (int u, v, i = 0; i < m; i++) {
			scanf("%d%d", &u, &v);
			AddEdge(u, v);
		}
		printf("Case %d: ", cs);

		memset(dfn, 0, sizeof dfn);
		dfs_clock = top = cntscc = 0;
		for (int i = 1; i <= n; i++) {
			if (!dfn[i]) Tarjan(i);
		}
		if (cntscc == 1) {
			puts("-1");
			continue;
		}
		for (int i = 1; i <= cntscc; i++) {
			odeg[i] = ideg[i] = 0;
		}
		for (int i = 1; i <= n; i++) {
			forto(i) {
				if (tag[v] != tag[i]) {
					++odeg[tag[i]], ++ideg[tag[v]];
				}
			}
		}
		long long ans = 0;
		for (int i = 1; i <= cntscc; i++) {
			if (!ideg[i] || !odeg[i]) {
				ans = std::max(1ll * (n - sz[i]) * sz[i] + 
								Sum(n - sz[i]) + Sum(sz[i]), ans);
			}
		}
		printf("%lld\n", ans - m);
	}

	return 0;
}

void Tarjan(int u) {
	S[top++] = u, ins[u] = 1;
	dfn[u] = low[u] = ++dfs_clock;
	forto(u) {
		if (!dfn[v]) {
			Tarjan(v);
			low[u] = std::min(low[u], low[v]);
		} else if (ins[v]) low[u] = std::min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		for (sz[++cntscc] = 0; top && S[top - 1] != u; ) {
			ins[S[top - 1]] = 0;
			tag[S[--top]] = cntscc;
			++sz[cntscc];
		}
		tag[u] = cntscc;
		--top, ins[u] = 0;
		++sz[cntscc];
	}
}
