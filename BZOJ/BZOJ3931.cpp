#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define forto(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)

typedef long long LL;

const int kMaxn = 505, kMaxm = 1e5 + 5;
const LL kInf64 = 0x7f7f7f7f7f7f7f7f;

namespace dinic {
	struct Edge {
		int to;
		LL capt;
		int next;
	} E[kMaxm << 2];
	int tote = 1, back[kMaxn << 1], cur[kMaxn << 1];

	inline void AddEdge(int u, int v, LL c) {
		E[++tote] = (Edge){v, c, back[u]}, back[u] = tote;
		E[++tote] = (Edge){u, 0, back[v]}, back[v] = tote;
	}
	LL MaxFlow();
}

struct Edge {
	int to, cost, next;
} E[kMaxm << 1];

int n, m, tote;
int back[kMaxn], inq[kMaxn];
LL dis[kMaxn], lim[kMaxn];
std::queue<int> que;

inline void AddEdge(int u, int v, int c) { 
	E[++tote] = (Edge){v, c, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, c, back[v]}, back[v] = tote;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int u, v, c; m--; ) {
		scanf("%d%d%d", &u, &v, &c);
		AddEdge(u, v, c);
	}
	for (int i = 1; i <= n; i++) scanf("%lld", lim + i);	

	memset(dis, 0x7f, sizeof dis);
	dis[1] = 0;
	que.push(1), inq[1] = 1;
	for (int u; !que.empty(); que.pop()) {
		u = que.front();
		forto(u) {
			if (dis[v] > dis[u] + E[e].cost) {
				dis[v] = dis[u] + E[e].cost;
				if (!inq[v]) {
					que.push(v);
					inq[v] = 1;
				}
			}
		}
		inq[u] = 0;
	}

	lim[1] = kInf64;
	for (int i = 1; i < n; i++) {
		dinic::AddEdge(i, i + n, lim[i]);
		forto(i) {
			if (dis[v] == dis[i] + E[e].cost) {
				dinic::AddEdge(i + n, v, kInf64);
			}
		}
	}
	
	printf("%lld\n", dinic::MaxFlow());
	return 0;
}

namespace dinic {
	int D[kMaxn << 1];

	bool Build() {
		std::queue<int> que;
		memset(D, 0, sizeof D);
		for (D[1] = 1, que.push(1); !que.empty(); ) {
			int u = que.front(); que.pop();
			forto(u) {
				if (!D[v] && E[e].capt > 0) {
					D[v] = D[u] + 1;
					que.push(v);
				}
			}
		}
		return D[n];
	}
	LL Dinic(int u, LL flow) {
		if (u == n) return flow;
		LL rem = flow;
		for (int & e = cur[u], v = E[e].to; e && rem > 0;
				v = E[e = E[e].next].to) {
			if (D[v] == D[u] + 1 && E[e].capt > 0) {
				LL delta = Dinic(v, std::min(rem, E[e].capt));
				E[e].capt -= delta, E[e ^ 1].capt += delta;
				rem -= delta;
			}
		}
		return flow - rem;
	}
	LL MaxFlow() {
		LL sum = 0;
		while (Build()) {
			for (int i = 1; i <= n << 1; i++) cur[i] = back[i];
			sum += Dinic(1, kInf64);
		}
		return sum;
	}
}
