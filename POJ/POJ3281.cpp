#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

#define forto(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)

const int kMaxv = 410, kMaxe = 2e4 + 10, kInf = 0x3f3f3f3f;

typedef int IAr[kMaxv];

struct Edge {
	int to, capt, next;
} E[kMaxe << 1];

int n, f, d, tote, src, trg;
IAr back, D, cur;

inline void AddEdge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, 0, back[v]}, back[v] = tote;
}
int MaxFlow();

int main() {
	while (~scanf("%d%d%d", &n, &f, &d)) {
		tote = 1;
		memset(back, 0, sizeof back);
		for (int i = 1, fi, di; i <= n; i++) {
			scanf("%d%d", &fi, &di);
			for (int j = 0, dish; j < fi; j++) {
				scanf("%d", &dish);
				AddEdge(n + i, n * 2 + d + dish, 1);
			}
			for (int j = 0, drink; j < di; j++) {
				scanf("%d", &drink);
				AddEdge(n * 2 + drink, i, 1);
			}
			AddEdge(i, n + i, 1);
		}
		trg = (src = n * 2 + d + f + 1) + 1;
		for (int i = 1; i <= f; i++) AddEdge(n * 2 + d + i, trg, 1);
		for (int i = 1; i <= d; i++) AddEdge(src, n * 2 + i, 1);

		printf("%d\n", MaxFlow());
	}
	return 0;
}


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
		for (int i = 1; i <= trg; i++) cur[i] = back[i];
		sum += Dinic(src, kInf);
	}
	return sum;
}
