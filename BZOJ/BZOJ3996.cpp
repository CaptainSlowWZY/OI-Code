#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

#define forto(_) for (int e = back[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int kMaxn = 505, kInf = 0x3f3f3f3f;

struct Edge {
	int to, capt, next;
} E[kMaxn * kMaxn << 3];

int n, tote = 1, S, T;
int B[kMaxn][kMaxn], C[kMaxn], back[kMaxn * kMaxn];

inline void AddEdge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, 0, back[v]}, back[v] = tote;
}
int MaxFlow();

int main() {
	scanf("%d", &n);
	int sumb = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", B[i] + j);
			sumb += B[i][j];
		}
	}
	for (int i = 0; i < n; i++) scanf("%d", C + i);

	S = n * n + n + 1, T = S + 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0, cur; j < n; j++) {
			AddEdge(S, cur = i * n + j, B[i][j]);
			AddEdge(cur, n * n + i, kInf);
			AddEdge(cur, n * n + j, kInf);
		}
		AddEdge(n * n + i, T, C[i]);
	}

	printf("%d\n", sumb - MaxFlow());
	return 0;
}

int D[kMaxn * kMaxn], cur[kMaxn * kMaxn];

bool Build() {
	std::queue<int> que;
	memset(D, 0, sizeof D);
	que.push(S), D[S] = 1;
	for (int u; !que.empty(); ) {
		u = que.front(), que.pop();
		forto(u) {
			if (E[e].capt <= 0 || D[v]) continue;
			D[v] = D[u] + 1;
			que.push(v);
		}
	}
	return D[T];
}

int Dinic(int u, int flow) {
	if (u == T) return flow;
	int rem = flow, delta;
	for (int & e = cur[u], v = E[e].to; e && rem;
		   v = E[e = E[e].next].to)	{
		if (E[e].capt <= 0 || D[v] != D[u] + 1) continue;
		delta = Dinic(v, std::min(rem, E[e].capt));
		E[e].capt -= delta, E[e ^ 1].capt += delta;
		rem -= delta;
	}
	return flow - rem;
}

int MaxFlow() {
	int sum = 0;
	while (Build()) {
		for (int i = 0; i <= T; i++) cur[i] = back[i];
		sum += Dinic(S, kInf);
	}
	return sum;
}
