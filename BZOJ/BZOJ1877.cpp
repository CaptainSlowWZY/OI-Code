// BZOJ 1877
// SDOI 2009
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define fir first
#define sec second
#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)
#define forback(_) for (int _ = T; _ != S; _ = pre[_])

typedef std::pair<int, int> Pii;

const int MAXE = 3e4 + 5, MAXV = 405, INF = 0x3f3f3f3f;

struct Edge {
	int to, capt, cost, next;
} E[MAXE << 1];

int N, M, S, T, tote = 1, last[MAXV], pre[MAXV], pree[MAXV], dist[MAXV], in_que[MAXV];

inline void add_edge(int u, int v, int cap, int cst) {
	E[++tote] = (Edge){v, cap, cst, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, 0, -cst, last[v]}, last[v] = tote;
}
Pii MCF();

int main() {
	scanf("%d%d", &N, &M);
	S = 1, T = N * 2;
	for (int i = 0, u, v, c; i < M; i++) {
		scanf("%d%d%d", &u, &v, &c);
		add_edge(u, v + N, 1, c);
	}
	for (int i = 2; i < N; i++) add_edge(i + N, i, 1, 0);

	Pii ans = MCF();
	printf("%d %d\n", ans.fir, ans.sec);
	return 0;
}

bool SPFA() {
	memset(pre, 0xff, sizeof pre);
	memset(dist, 0x7f, sizeof dist);
	std::queue<int> que;
	for (dist[S] = 0, que.push(S), in_que[S] = 1; !que.empty(); ) {
		int u = que.front(); que.pop();
		forto(u)
			if (E[e].capt > 0 && dist[v] > dist[u] + E[e].cost) {
				dist[v] = dist[u] + E[e].cost;
				pre[v] = u, pree[v] = e;
				if (!in_que[v]) que.push(v), in_que[v] = 1;
			}
		in_que[u] = 0;
	}
	return ~pre[T];
}

Pii MCF() {
	Pii ret(0, 0);
	while (SPFA()) {
		int minf = INF;
		forback(u) minf = std::min(minf, E[pree[u]].capt);
		ret.fir += minf, ret.sec += minf * dist[T];
		forback(u) E[pree[u]].capt -= minf, E[pree[u] ^ 1].capt += minf;
	}
	return ret;
}
