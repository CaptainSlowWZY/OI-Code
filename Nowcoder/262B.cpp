#include <algorithm>
#include <cstdio>
#include <queue>

#define fir first
#define sec second
#define FORTO(gg, uu, vv, ee) for (int ee = gg.back[uu], \
		vv = gg.E[ee].to; ee; vv = gg.E[ee = gg.E[ee].next].to)

typedef std::pair<int, int> Pii;

const int kMaxn = 1e4 + 4, kMaxm = 2e5 + 5, kInf = 0x3f3f3f3f;

struct Edge { int to, next; };
struct Graph {
	Edge E[kMaxm];
	int cnte, back[kMaxn];
	void add_edge(int u, int v) {
		E[++cnte] = {v, back[u]}, back[u] = cnte;
	}
} G, R;
	
int n, m, s, t;
int valid[kMaxn], vis[kMaxn], dis[kMaxn], inq[kMaxn];
// std::priority_queue<Pii> hap;
std::queue<int> que;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0, x, y; i < m; i++) {
		scanf("%d%d", &x, &y);
		G.add_edge(x, y);
		R.add_edge(y, x);
	} scanf("%d%d", &s, &t);
	
	vis[t] = 1, que.push(t);
	while (!que.empty()) {
		FORTO(R, que.front(), v, e) {
			if (!vis[v]) { que.push(v); vis[v] = 1; }
		} que.pop();
	}	
	for (int i = 1; i <= n; i++) {
		valid[i] = vis[i];
		FORTO(G, i, v, e) valid[i] &= vis[v];
	}
	if (!valid[s]) { puts("-1"); return 0; }
	std::fill(dis, dis + n + 1, kInf);
/*	dis[s] = 0; hap.push({0, s});
	while (!hap.empty()) {
		Pii p = hap.top(); hap.pop();
		if (p.fir > dis[p.sec]) continue;
		FORTO(G, p.sec, v, e) {	
			if (!valid[v]) continue;
			if (p.fir + 1 < dis[v]) {
				dis[v] = p.fir + 1;
				hap.push({dis[v], v});
			}
		}
	}*/
	dis[s] = 0, inq[s] = 1, que.push(s);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		FORTO(G, u, v, e) {
			if (!valid[v]) continue;
			if (dis[u] + 1 < dis[v]) {
				dis[v] = dis[u] + 1;
				if (!inq[v]) { que.push(v); inq[v] = 1; }
			}
		} inq[u] = 0;
	}
	printf("%d\n", dis[t]);
	return 0;
}
