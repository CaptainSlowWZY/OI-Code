#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define forto(_) for (int e = back[_], v = E[e].to; e; v = E[e = E[e].next].to)
#define forback(_) for (int _ = trg; _ ^ src; _ = prvu[_])

const int kMaxn = 2005, kMaxe = kMaxn << 4, kInf = 0x7f7f7f7f;

typedef int IAr[kMaxn << 1];
typedef long long LL;

struct Edge {
	int to, capt, cost, next;
} E[kMaxe << 1];

int n, src, trg, per, slowc, fastc, slowt, fastt, tote = 1, need[kMaxn];
IAr back, inq, prvu, prve;
LL dist[kMaxn << 1];

LL Mcf();
inline void AddEdge(int u, int v, int cap, int cst) {
	E[++tote] = (Edge){v, cap, cst, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, 0, -cst, back[v]}, back[v] = tote;
}

int main() {
	scanf("%d", &n);
	src = 0, trg = n * 2 + 1;
	for (int i = 1, ri; i <= n; i++) {
		scanf("%d", &ri);
		AddEdge(src, i + n, ri, 0);
		AddEdge(i, trg, ri, 0);
	}
	scanf("%d%d%d%d%d", &per, &fastt, &fastc, &slowt, &slowc); 	
	
	for (int i = 1; i <= n; i++) {
		AddEdge(src, i, kInf, per);
		if (i + fastt <= n) AddEdge(i + n, i + fastt, kInf, fastc);
		if (i + slowt <= n) AddEdge(i + n, i + slowt, kInf, slowc);
		if (i < n) AddEdge(i + n, i + 1 + n, kInf, 0);
	}

	printf("%lld\n", Mcf());
	return 0;
}

std::queue<int> que;

bool Spfa() {
	memset(prvu, 0xff, sizeof prvu);
	memset(dist, 0x7f, sizeof dist);
	dist[src] = 0, que.push(src), inq[src] = 1;
	for (int u; !que.empty(); que.pop()) {
		u = que.front();
		forto(u) {
			if (E[e].capt > 0 && dist[v] > dist[u] + E[e].cost) {
				dist[v] = dist[u] + E[e].cost;
				prvu[v] = u, prve[v] = e;
				if (!inq[v]) { que.push(v), inq[v] = 1; }
			}
		}
		inq[u] = 0;
	}
	return ~prvu[trg];
}

LL Mcf() {
	LL tot = 0;
	while (Spfa()) {
		int flow = kInf;
		forback(u) flow = std::min(flow, E[prve[u]].capt);
		tot += 1ll * flow * dist[trg];
		forback(u) E[prve[u]].capt -= flow, E[prve[u] ^ 1].capt += flow;
	}
	return tot;
}