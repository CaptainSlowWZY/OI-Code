#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int MAXV = 10005, MAXE = 4e5, INF = 0x3f3f3f3f, DX[] = {-1, 1, 0, 0}, DY[] = {0, 0, -1, 1};

struct Edge {
	int to, capt, next;
} E[MAXE << 1];

int N, M, S, T, tote = 1, last[MAXV], D[MAXV], cur[MAXV];

inline void add_edge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, 0, last[v]}, last[v] = tote;
}
int Dinic();

int main() {
	scanf("%d%d", &N, &M);
	T = (S = N * M) + 1;
	int sum = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0, Aij; j < M; j++) {
			scanf("%d", &Aij);
			sum += Aij;
			if (i + j & 1) {
				add_edge(S, i * M + j, Aij);
				for (int k = 0; k < 4; k++) {
					int nx = i + DX[k], ny = j + DY[k];
					if (nx >= 0 && nx < N && ny >=0 && ny < M)
						add_edge(i * M + j, nx * M + ny, INF);
				}
			}
			else add_edge(i * M + j, T, Aij);
		}

	printf("%d\n", sum - Dinic());
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

int dfs(int u, int cap) {
	if (u == T) return cap;
	int rem = cap;
	for (int & e = cur[u], v = E[e].to; e; v = E[e = E[e].next].to)
		if (E[e].capt > 0 && D[v] == D[u] + 1) {
			int del = dfs(v, std::min(E[e].capt, rem));
			E[e].capt -= del, E[e ^ 1].capt += del;
			if (!(rem -= del)) break;
		}
	return cap - rem;
}

int Dinic() {
	int sumf = 0;
	while (build()) {
		for (int i = 0; i <= T; i++) cur[i] = last[i];
		sumf += dfs(S, INF);
	}
	return sumf;
}
