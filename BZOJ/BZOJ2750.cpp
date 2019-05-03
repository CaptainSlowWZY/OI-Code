// HAOI 2012 Road
#include <cstdio>
#include <cstring>
#include <queue>

#define forto(_, __) for (int e = _.back[__], v = _.E[e].to; e; \
		v = _.E[e = _.E[e].next].to)

const int kMaxn = 1510, kMaxm = 5010, MOD = 1e9 + 7;

typedef int IAr[kMaxn];

struct Graph {
	struct Edge {
		int to, cost, next, id;
	} E[kMaxm];
	IAr back;
	int tote;

	void adde(int u, int v, int c, int id) {
		E[++tote] = (Edge){v, c, back[u], id}, back[u] = tote;
	}
	void clear() {
		tote = 0;
		memset(back, 0, sizeof back);
	}
} G, SG;

int n, m;
IAr ideg, odeg, dis, que, cnt1, cnt2, inq;
long long ans[kMaxm];

void Spfa(int u);

int main() {
	scanf("%d%d", &n, &m);
	for (int u, v, w, i = 0; i < m; i++) {
		scanf("%d%d%d", &u, &v, &w);
		G.adde(u, v, w, i);
	}

	for (int i = 1; i <= n; i++) {
		Spfa(i);
		SG.clear();
		memset(ideg, 0, sizeof ideg);
		memset(odeg, 0, sizeof odeg);
		memset(cnt1, 0, sizeof cnt1);
		memset(cnt2, 0, sizeof cnt2);
		cnt1[i] = 1;
		for (int j = 1; j <= n; j++) {
			forto(G, j) {
				if (dis[v] == dis[j] + G.E[e].cost) {
					SG.adde(j, v, 0, G.E[e].id);
					++ideg[v];
				}
			}
		}
		int hd = 0, tl = 0;
		for (int j = 1; j <= n; j++) {
			if (!ideg[j]) {
				que[tl++] = j;
			}
		}
		for (int u; hd < tl; ) {
			u = que[hd++];
			forto(SG, u) {
				(cnt1[v] += cnt1[u]) %= MOD;
				if (!(--ideg[v])) {
					que[tl++] = v;
				}
			}
		}
		for (int u, j = tl - 1; j >= 0; j--) {
			++cnt2[u = que[j]];
			forto(SG, u) (cnt2[u] += cnt2[v]) %= MOD;
		}

		for (int j = 1; j <= n; j++) {
			forto(SG, j) {
				(ans[SG.E[e].id] += 1ll * cnt1[j] * cnt2[v] % MOD) %= MOD;
			}
		}
	}

	for (int i = 0; i < m; i++) printf("%lld\n", ans[i]);
	return 0;
}

void Spfa(int s) {
	memset(dis, 0x7f, sizeof dis);
	std::queue<int> que;

	que.push(s), dis[s] = 0, inq[s] = 1;
	for (int u; !que.empty(); que.pop()) {
		u = que.front(); 
		forto(G, u) {
			if (dis[v] > dis[u] + G.E[e].cost) {
				dis[v] = dis[u] + G.E[e].cost;
				if (!inq[v]) { que.push(v); inq[v] = 1; }
			}
		}
		inq[u] = 0;
	}
}
