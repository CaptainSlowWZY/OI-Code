// Luogu P3376
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int MAXN = 1e4 + 10;
const int MAXM = 1e5 + 10;
const int INF = 0x7f7f7f7f; 

struct Edge {
	int to, capt, next;
} E[MAXM << 1];

int N, M, S, T, tote = 1, last[MAXN], D[MAXN], cur[MAXN];

inline void add_edge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, 0, last[v]}, last[v] = tote;
}
int max_flow();

int main() {
	scanf("%d%d%d%d", &N, &M, &S, &T);
	for (int i = 0, ui, vi, ci; i < M; i++) {
		scanf("%d%d%d", &ui, &vi, &ci);
		add_edge(ui, vi, ci);
	}

	printf("%d\n", max_flow());

	return 0;
}

bool build() {
	std::queue<int> que;
	memset(D, 0, sizeof D);
	for (D[S] = 1, que.push(S); !que.empty(); ) {
		int u = que.front(); que.pop();
		forto(u) 
			if (!D[v] && E[e].capt > 0) {
				D[v] = D[u] + 1;
				que.push(v);
			}
	}
	return D[T];
}

int dinic(int u, int cap) {
	if (u == T) return cap;
	int rem = cap;
	for (int & e = cur[u]; e; e = E[e].next) {
		int v = E[e].to;
		if (D[v] == D[u] + 1 && E[e].capt > 0) {
			int delta = dinic(v, std::min(rem, E[e].capt));
			E[e].capt -= delta, E[e ^ 1].capt += delta;
			if (!(rem -= delta)) break;
		}
	}
	return cap - rem;
}

int max_flow() {
	int tmp, ret = 0;
	while (build()) {
		for (int i = 1; i <= N; i++) cur[i] = last[i];
		ret += dinic(S, INF);
	}
	return ret;
}
