// Luogu P2763
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int MAXV = 1100;
const int MAXE = 20010;
const int INF = 0x7fffffff;

struct Edge {
	int to, capt, next;
} E[MAXE << 1];

int N, M, K, S, T, tote = 1, D[MAXV], last[MAXV], cur[MAXV];

inline void add_edge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, 0, last[v]}, last[v] = tote;
}
bool max_flow();

int main() {
	scanf("%d%d", &K, &N);
	T = (S = K + N) + 1;
	for (int i = 0, num; i < K; i++) {
		scanf("%d", &num);
		add_edge(S, i, num);
		M += num;
	}
	for (int i = 0, pi; i < N; i++) {
		scanf("%d", &pi);
		for (int j = 0, srt; j < pi; j++) {
			scanf("%d", &srt);
			add_edge(srt - 1, K + i, 1);
		}	
		add_edge(K + i, T, 1);
	}

	if (max_flow()) {
		for (int i = 0; i < K; i++) {
			printf("%d:", i + 1);
			forto(i)
				if (!E[e].capt && E[e ^ 1].capt) printf(" %d", v - K + 1);
			putchar('\n');
		}
	}
	else puts("No Solution!");
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

bool max_flow() {
	int sumf = 0;
	while (build()) {
		for (int i = 0; i <= T; i++) cur[i] = last[i];
		sumf += dinic(S, INF);
	}
	return sumf == M;
}
