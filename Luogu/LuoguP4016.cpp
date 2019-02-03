// Luogu P4016
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)
#define forback(_) for (int _ = T; _ ^ S; _ = pre[_])

const int MAXN = 210;
const int MAXM = 2000;
const int INF = 0x7f7f7f7f;

typedef int IntAr[MAXN];

struct Edge {
	int to, capt, cost, next;
} E[MAXM << 1];

int N, tote = 1, avrg, S, T;
IntAr A, last, dist, in_que, pre, pree;

inline void add_edge(int u, int v, int cp, int ct) {
	E[++tote] = (Edge){v, cp, ct, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, 0, -ct, last[v]}, last[v] = tote;
}
int mincf();

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", A + i);
		avrg += A[i];
	}
	
	avrg /= N, S = 0, T = N + 1;
	// Source is 0 & Terminal is N * 2 + 1
	// id(Xi) = i, it gives away
	// id(Yi) = i + N, it needs
	for (int i = 1; i <= N; i++) {
		if ((A[i] -= avrg) > 0) add_edge(S, i, A[i], 0);
		else add_edge(i, T, -A[i], 0);
		if (i > 1) /*add_edge(i, i - 1 + N, INF, 1), */add_edge(i, i - 1, INF, 1);
		else /*add_edge(i, N * 2, INF, 1), */add_edge(i, N, INF, 1);
		if (i < N) /*add_edge(i, i + 1 + N, INF, 1), */add_edge(i, i + 1, INF, 1);
		else /*add_edge(i, N + 1, INF, 1), */add_edge(i, 1, INF, 1);
	}

	printf("%d\n", mincf());
	return 0;
}

bool SPFA() {
	memset(pre, 0xff, sizeof pre);
	memset(dist, 0x7f, sizeof dist);
	std::queue<int> que;

	for (dist[S] = 0, in_que[S] = 1, que.push(S); !que.empty(); ) {
		int u = que.front(); que.pop();
		forto(u)
			if (E[e].capt > 0 && dist[v] > dist[u] + E[e].cost) {
				dist[v] = dist[u] + E[e].cost;
				pre[v] = u, pree[v] = e;
				if (!in_que[v]) in_que[v] = 1, que.push(v);
			}
		in_que[u] = 0;
	}

	return ~pre[T];
}

int mincf() {
	int sumc = 0;
	while (SPFA()) {
		int minf = INF;
		forback(u) minf = std::min(minf, E[pree[u]].capt);
		sumc += minf * dist[T];
		forback(u) E[pree[u]].capt -= minf, E[pree[u] ^ 1].capt += minf;
	}
	return sumc;
}
