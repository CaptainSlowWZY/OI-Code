// Luogu P2756
#include <cstdio>
#include <cstring>
#include <queue>

const int MAXV = 105;
const int INF = 0x7f7f7f7f;

int N, M, S, T, G[MAXV][MAXV], cur[MAXV], D[MAXV];

int max_flow();

int main() {
	scanf("%d%d", &M, &N);
	T = (S = N + 1) + 1;
	for (int ui, vi; scanf("%d%d", &ui, &vi) == 2 && ~ui && ~vi; G[ui][vi] = 1);
	for (int i = 1; i <= M; i++) G[S][i] = 1;
	for (int i = M + 1; i <= N; i++) G[i][T] = 1; 

	printf("%d\n", max_flow());
	for (int i = 1; i <= M; i++)
		for (int j = M + 1; j <= N; j++)
			if (!G[i][j] && G[j][i]) printf("%d %d\n", i, j);

	return 0;
}

bool build() {
	std::queue<int> que;
	memset(D, 0, sizeof D);
	for (D[S] = 1, que.push(S); !que.empty(); ) {
		int u = que.front(); que.pop();
		for (int v = 1; v <= T; v++)
			if (!D[v] && G[u][v] > 0) {
				D[v] = D[u] + 1;
				que.push(v);
			}
	}
	return D[T];
}

int dinic(int u, int cap) {
	if (u == T) return cap;
	int rem = cap;
	for (int & v = cur[u]; v <= T && rem > 0; v++)
		if (D[v] == D[u] + 1 && G[u][v] > 0) {
			int delta = dinic(v, std::min(rem, G[u][v]));
			G[u][v] -= delta, G[v][u] += delta;
			rem -= delta;
		}
	return cap - rem;
}

int max_flow() {
	int sumf = 0;
	while (build()) {
		for (int i = 1; i <= T; i++) cur[i] = 1;
		sumf += dinic(S, INF);
	}
	return sumf;
}
