// Luogu P3381
#pragma GCC optimize(2)
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <queue>

#define fir first
#define sec second
#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)
#define forback(_) for (int _ = T; _ ^ S; _ = pre[_])

const int MAXN = 5005;
const int MAXM = 50010;
const int INF = 0x7f7f7f7f;

typedef std::pair<int, int> Pii;
typedef int IntAr[MAXN];

struct Edge {
	int to, capt, cost, next;
} E[MAXM << 1];

int N, M, S, T, tote = 1;
IntAr last, dist, pre, pree, h;

inline void add_edge(int u, int v, int w, int c) {
	E[++tote] = (Edge){v, w, c, last[u]}, last[u] = tote;
}
Pii max_flow();

int main() {
	scanf("%d%d%d%d", &N, &M, &S, &T);
	for (int ui, vi, wi, fi; M--; ) {
		scanf("%d%d%d%d", &ui, &vi, &wi, &fi);
		add_edge(ui, vi, wi, fi);
		add_edge(vi, ui, 0, -fi);
	}

	Pii ans = max_flow();
	printf("%d %d\n", ans.fir, ans.sec);
	return 0;
}

bool Dijkstra() {
	memset(pre, 0xff, sizeof pre);
	memset(dist, 0x7f, sizeof dist);
	std::priority_queue<Pii, std::vector<Pii>, std::greater<Pii> > hp;

	for (dist[S] = 0, hp.push(Pii(0, S)); !hp.empty(); ) {
		Pii now = hp.top(); hp.pop();
		if (now.fir > dist[now.sec]) continue;
		forto(now.sec)
			if (E[e].capt > 0 && dist[v] > now.fir + E[e].cost + h[now.sec] - h[v]) {
				dist[v] = now.fir + E[e].cost + h[now.sec] - h[v];
				pre[v] = now.sec, pree[v] = e;
				hp.push(Pii(dist[v], v));
			}
	}
	return ~pre[T];
}

Pii max_flow() {
	memset(h, 0, sizeof h);
	Pii ret(0, 0);

	while (Dijkstra()) {
		for (int i = 1; i <= N; i++) h[i] += dist[i];
		int minc = INF;
		forback(u) minc = std::min(minc, E[pree[u]].capt);
		ret.fir += minc, ret.sec += minc * h[T];
		forback(u) {
			E[pree[u]].capt -= minc;
			E[pree[u] ^ 1].capt += minc;
		}
	}
	return ret;
}
