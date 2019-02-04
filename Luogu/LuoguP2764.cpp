// Luogu P2764
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

using std::cerr;
using std::endl;

const int MAXV = 310;
const int MAXM = 7000;
const int INF = 0x7f7f7f7f;

struct Edge {
	int to, capt, next;
} E[MAXM << 1];

int N, M, S, T, tote = 1, last[MAXV], cur[MAXV], D[MAXV], vis[MAXV], nxt[MAXV];

inline void add_edge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, 0, last[v]}, last[v] = tote;
}
int max_flow();

int main() {
	scanf("%d%d", &N, &M);
	T = (S = N * 2 + 1) + 1;
	for (int i = 0, u, v; i < M; i++) {
		scanf("%d%d", &u, &v);
		add_edge(u, v + N, 1);
	}
	for (int i = 1; i <= N; i++) {
		add_edge(S, i, 1);
		add_edge(i + N, T, 1);
	}

	int ans = N - max_flow();
	for (int i = 1; i <= N; i++) {
		if (vis[i]) continue;
		for (int u = i; ; u = nxt[u] - N) {
			vis[u] = 1;
			printf("%d ", u);
			if (!nxt[u]) break;
		}
		putchar('\n');
	}
	printf("%d\n", ans);
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
			if (!delta) continue;
			E[e].capt -= delta, E[e ^ 1].capt += delta, rem -= delta;
			nxt[u] = v;
		}
	return flow - rem;
}

int max_flow() {
	int sumf = 0;
	while (build()) {
		for (int i = 1; i <= T; i++) cur[i] = last[i];
		sumf += dinic(S, INF);
	}
	return sumf;
}
