#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int kMaxe = 5e5 + 10, kMaxn = 105, kMaxv = 10005, kInf = 0x3f3f3f3f;
const int DX[] = {-1, 0, 0, 1}, DY[] = {0, -1, 1, 0};

struct Edge {
	int to, capt, next;
} E[kMaxe << 1];

int n, m, tote = 1, S, T, A[kMaxn][kMaxn], last[kMaxv], cur[kMaxv], D[kMaxv];

inline void AddEdge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, 0, last[v]}, last[v] = tote;
}
int MaxFlow();

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) scanf("%d", &A[i][j]);

	T = (S = n * m) + 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			if (A[i][j] == 1) AddEdge(S, i * m + j, kInf);
			else if (A[i][j] == 2) {
				AddEdge(i * m + j, T, kInf);
				continue;
			}
			for (int k = 0, nx, ny; k < 4; k++) {
				nx = i + DX[k], ny = j + DY[k];
				if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
				if (A[i][j] != 1 || A[nx][ny] != 1) AddEdge(i * m + j, nx * m + ny, 1);
			}
		}
	printf("%d\n", MaxFlow());
	return 0;
}

bool Build() {
	std::queue<int> que;
	memset(D, 0, sizeof D);
	for (D[S] = 1, que.push(S); !que.empty(); ) {
		int u = que.front(); que.pop();
		forto(u)
			if (!D[v] && E[e].capt > 0) D[v] = D[u] + 1, que.push(v);
	}
	return D[T];
}

int Dinic(int u, int flow) {
	if (u == T) return flow;
	int rem = flow;
	for (int &e = cur[u], v = E[e].to; e && rem > 0; v = E[e = E[e].next].to)
		if (D[v] == D[u] + 1 && E[e].capt > 0) {
			int delta = Dinic(v, std::min(rem, E[e].capt));
			E[e].capt -= delta, E[e ^ 1].capt += delta, rem -= delta;
		}
	return flow - rem;
}

int MaxFlow() {
	int sumf = 0;
	while (Build()) {
		for (int i = 0; i <= T; i++) cur[i] = last[i];
		sumf += Dinic(S, kInf);
	}
	return sumf;
}
