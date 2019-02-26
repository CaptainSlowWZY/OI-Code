#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int MAXN = 405, INF = 0x3f3f3f3f;

struct Edge {
	int to, capt, next;
} E[MAXN * MAXN];

int N, S, T, tote, last[MAXN], cur[MAXN], D[MAXN];

inline void add_edge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, 0, last[v]}, last[v] = tote;
}
int max_flow();

int main() {
	int cs;
	for (scanf("%d", &cs); cs--; ) {
		scanf("%d", &N);
		T = (S = N * 2) + 1, tote = 1;
		memset(last, 0, sizeof last);

		for (int i = 0; i < N; i++) {
			for (int j = 0, aij; j < N; j++) {
				scanf("%d", &aij);
				if (aij) add_edge(i, j + N, 1);
			}
			add_edge(S, i, 1);
			add_edge(i + N, T, 1);
		}

		if (max_flow() == N) puts("Yes");
		else puts("No");
	}
	return 0;
}

bool build() {
	std::queue<int> que;
	memset(D, 0, sizeof D);
	for (D[S] = 1, que.push(S); !que.empty(); ) {
		int u = que.front(); que.pop();
		forto(u)
			if (!D[v] && E[e].capt > 0) D[v] = D[u] + 1, que.push(v);
	}
	return D[T];
}

int dinic(int u, int flow) {
	if (u == T) return flow;
	int rem = flow;
	for (int &e = cur[u], v = E[e].to; e && rem > 0; v = E[e = E[e].next].to)
		if (D[v] == D[u] + 1 && E[e].capt > 0) {
			int delta = dinic(v, std::min(rem, E[e].capt));
			E[e].capt -= delta, E[e ^ 1].capt += delta, rem -= delta;
		}
	return flow - rem;
}

int max_flow() {
	int sumf = 0;
	while (build()) {
		for (int i = 0; i <= T; i++) cur[i] = last[i];
		sumf += dinic(S, INF);
	}
	return sumf;
}
