#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

#define forto(_) for (int e = back[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int kMaxn = 105, kV = 40010, kInf = 0x3f3f3f3f;
const int kDx[4] = {0, -1, 1, 0}, kDy[4] = {-1, 0, 0, 1};

typedef int IMtr[kMaxn][kMaxn];

struct Edge {
	int to, capt, next;
} E[kV << 3];

int n, m, tote = 1, src, trg;
int back[kV];
IMtr A, S, SA, SS;

inline void AddEdge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, 0, back[v]}, back[v] = tote;
}
int MaxFlow();

int main() {
	scanf("%d%d", &n, &m);
	int sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", A[i] + j);
			sum += A[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", S[i] + j);
			sum += S[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", SA[i] + j);
			sum += SA[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", SS[i] + j);
			sum += SS[i][j];
		}
	}

	int nm = n * m;
	trg = (src = 3 * nm) + 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0, cur; j < m; j++) {
			AddEdge(src, cur = i * m + j, A[i][j]);
			AddEdge(cur, trg, S[i][j]);
			AddEdge(src, nm + cur, SA[i][j]);
			AddEdge(2 * nm + cur, trg, SS[i][j]);
			for (int k = 0, x, y; k < 4; k++) {
				x = i + kDx[k], y = j + kDy[k];
				if (x >= 0 && x < n && y >= 0 && y < m) {
					AddEdge(nm + cur, x * m + y, kInf);
					AddEdge(x * m + y, nm * 2 + cur, kInf);
				}
			}
			AddEdge(nm + cur, cur, kInf);
			AddEdge(cur, nm * 2 + cur, kInf);
		}
	}

	printf("%d\n", sum - MaxFlow());
	return 0;
}

int D[kV], cur[kV];

bool Build() {
	std::queue<int> que;
	memset(D, 0, sizeof D);
	que.push(src), D[src] = 1;
	for (int u; !que.empty(); ) {
		u = que.front(), que.pop();
		forto(u) {
			if (E[e].capt <= 0 || D[v]) continue;
			D[v] = D[u] + 1;
			que.push(v);
		}
	}
	return D[trg];
}

int Dinic(int u, int flow) {
	if (u == trg) return flow;
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
		for (int i = 0; i <= trg; i++) cur[i] = back[i];
		sum += Dinic(src, kInf);
	}
	return sum;
}
