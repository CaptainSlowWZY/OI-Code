// Luogu P4015
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)
#define forback(_) for (int _ = T; _ ^ S; _ = pre[_])

const int MAXV = 205;
const int MAXE = 10500;
const int INF = 0x7f7f7f7f;

typedef int IntAr[MAXV];

struct Edge {
	int to, capt, cost, next;
} E[MAXE << 1];

int M, N, S, T, A[105], B[105], C[105][105], tote = 1;
IntAr last, dist, in_que, pre, pree;

inline void add_edge(int u, int v, int cap, int cst) {
	E[++tote] = (Edge){v, cap, cst, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, 0, -cst, last[v]}, last[v] = tote;
}
int MCF();

int main() {
	scanf("%d%d", &M, &N);
	for (int i = 0; i < M; i++) scanf("%d", A + i);
	for (int i = 0; i < N; i++) scanf("%d", B + i);
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++) scanf("%d", &C[i][j]);

	T = (S = M + N) + 1;
	for (int i = 0; i < M; i++) add_edge(S, i, A[i], 0);
	for (int i = 0; i < N; i++) add_edge(M + i, T, B[i], 0);
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++) add_edge(i, M + j, INF, C[i][j]);
	printf("%d\n", MCF());

	tote = 1;
	memset(last, 0, sizeof last);
	for (int i = 0; i < M; i++) add_edge(S, i, A[i], 0);
	for (int i = 0; i < N; i++) add_edge(M + i, T, B[i], 0);
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++) add_edge(i, M + j, INF, -C[i][j]);
	printf("%d\n", -MCF());

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

int MCF() {
	int sumc = 0;
	while (SPFA()) {
		int minc = INF;
		forback(u) minc = std::min(minc, E[pree[u]].capt);
		sumc += minc * dist[T];
		forback(u) E[pree[u]].capt -= minc, E[pree[u] ^ 1].capt += minc;
	}
	return sumc;
}
