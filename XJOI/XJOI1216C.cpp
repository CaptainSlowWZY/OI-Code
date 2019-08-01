#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

#define fir first
#define sec second
#define FORTO(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)

typedef std::pair<int, int> Pii;

const int kMaxn = 2e5 + 10, kMaxm = 1e6 + 10, kInf = 0x3f3f3f3f;

struct Edge {
	int to, c, next;
} E[kMaxm];

int n, m, tote, scc, dfs_clock, top;
int back[kMaxn], S[kMaxn], col[kMaxn];
int dis[kMaxn], dfn[kMaxn], low[kMaxn], ins[kMaxn];
std::vector<Pii> G[kMaxn];
std::priority_queue<Pii, std::vector<Pii>, std::greater<Pii> > hap;

inline void AddEdge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, back[u]}, back[u] = tote;
}
template <typename T> inline
void UMin(T & x, const T & y) {
	if (x > y) x = y;
}
void Dfs(int u, int fa);

int main() {
	scanf("%d%d", &n, &m);
	for (int u, v, c; m--; ) {
		scanf("%d%d%d", &u, &v, &c);
		AddEdge(u, v, c);
	}

	Dfs(1, 0);

	for (int i = 1; i <= n; i++) {
	//	printf(" %d belong to %d\n", i, col[i]);
		FORTO(i) {
			if (col[i] == col[v]) continue;
			G[col[i]].push_back({col[v], E[e].c});
		}
	}
	std::fill(dis + 1, dis + scc + 1, kInf);
	dis[col[1]] = 0, hap.push({0, col[1]});
	for (Pii cur; !hap.empty(); ) {
		cur = hap.top(), hap.pop();
		int u = cur.sec;
		if (dis[u] < cur.fir) continue;
		for (const auto & e : G[u]) {
			if (dis[e.fir] > dis[u] + e.sec) {
				dis[e.fir] = dis[u] + e.sec;
				hap.push({dis[e.fir], e.fir});
			}
		}
	}
	printf("%d\n", dis[col[n]]);
	return 0;
}

void Dfs(int u, int fa) {
	dfn[u] = low[u] = ++dfs_clock;
	ins[u] = 1, S[top++] = u;
	FORTO(u) {
		if (v == fa) continue;
		if (!dfn[v]) {
			Dfs(v, u);
			UMin(low[u], low[v]);
		} else if (ins[v]) {
			UMin(low[u], dfn[v]);
		}
	}
	if (dfn[u] == low[u]) {
		col[u] = ++scc, ins[u] = 0;
		for (; S[top - 1] != u; ) {
			col[S[--top]] = scc;
			ins[S[top]] = 0;
		}
		--top;
	}
}
