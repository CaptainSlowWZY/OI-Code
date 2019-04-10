// NOI 2018
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define forto(_) for (int e = last[_], v = E[e].to; e; \
						v = E[e = E[e].next].to)
#define fir first
#define sec second

const int kMaxm = 4e5 + 10, kLgN = 19, kInf = 0x7f7f7f7f;

typedef int IAr[kMaxm];
typedef std::pair<int, int> Pii;

struct Road {
	int u, v, a;
	bool operator<(const Road & r) const {
		return a > r.a;
	}
} R[kMaxm];
struct Edge {
	int to, cost, next;
} E[kMaxm << 1];

int n, m, tote, q, k, s, dfs_clock;
int F[kMaxm][kLgN];
IAr last, idfn, odfn, dist, alt, refl;

namespace uset {
	int fa[kMaxm];

	void Init() {
		for (int i = 1; i <= (n << 1); i++) fa[i] = i;
	}
	int Find(int x) {
		return fa[x] == x ? x : fa[x] = Find(fa[x]);
	}
}
namespace smt {
	int Build(int l, int r);
	int Query(int l, int r, int ql, int qr);
}
inline void ClearGraph() {
	tote = dfs_clock = 0;
	memset(last, 0, sizeof last);
}
inline void AddEdge(int u, int v, int c = 0) {
	E[++tote] = (Edge){v, c, last[u]}, last[u] = tote;
}
void Dfs(int u);
void Dijkstra();

int main() {
	int t;
	scanf("%d", &t);
	for (; t--; ) {
		ClearGraph();

		scanf("%d%d", &n, &m);
		for (int i = 0, l; i < m; i++) {
			scanf("%d%d%d%d", &R[i].u, &R[i].v, &l, &R[i].a);
			AddEdge(R[i].u, R[i].v, l), AddEdge(R[i].v, R[i].u, l);
		}

		Dijkstra();
	/*	for (int i = 1; i <= n; i++) {
			printf(" dist from 1 to %d is %d\n",
					i, dist[i]);
		}*/
		ClearGraph();
		std::sort(R, R + m);
		uset::Init();
		int newn = n;
		for (int i = 1; i <= n; i++) alt[i] = kInf;
		for (int i = 0, x, y; i < m; i++) {
			using namespace uset;
			if (Find(R[i].u) == Find(R[i].v)) continue;
			x = Find(R[i].u), y = Find(R[i].v);
			alt[fa[x] = fa[y] = ++newn] = R[i].a;
			AddEdge(newn, x), AddEdge(newn, y);
		}
		memset(F, 0, sizeof F);
		Dfs(newn);
	/*	printf(" newn = %d\n", newn);
		for (int i = 1; i <= newn; i++) {
			printf("  %d: idfn %d, odfn %d\n",
					i, idfn[i], odfn[i]);
		}*/
		smt::Build(1, newn);

		scanf("%d%d%d", &q, &k, &s);
		for (int v, p, tp, lastans = 0; q--; ) {
			scanf("%d%d", &v, &p);
			v = (v + 1ll * k * lastans - 1) % n + 1;
			p = (p + 1ll * k * lastans) % (s + 1);
			tp = v;
			for (int i = kLgN - 1; i >= 0; i--) {
				if (alt[F[tp][i]] > p) tp = F[tp][i];
			}
			printf("%d\n", 
					lastans = smt::Query(1, newn, idfn[tp], odfn[tp]));
		}
	}
	return 0;
}

namespace smt {
	int T[kMaxm << 1];

	inline int Id(int l, int r) { return l + r | l != r; }
	int Build(int l, int r) {
		int rt = Id(l, r);
		if (l == r) return T[rt] = dist[refl[l]];
		int mid = l + r >> 1;
		return T[rt] = std::min(Build(l, mid), Build(mid + 1, r));
	}
	int Query(int l, int r, int ql, int qr) {
		if (qr < l || r < ql) return kInf;
		int rt = Id(l, r);
		if (ql <= l && r <= qr) return T[rt];
		int mid = l + r >> 1;
		return std::min(Query(l, mid, ql, qr), Query(mid + 1, r, ql, qr));
	}
}

void Dijkstra() {
	std::priority_queue<Pii, std::vector<Pii>, std::greater<Pii> > hp;

	memset(dist, 0x7f, sizeof dist);
	dist[1] = 0, hp.push(Pii(0, 1));
	while (!hp.empty()) {
		for (; !hp.empty() &&
				dist[hp.top().sec] < hp.top().fir; hp.pop());
		if (hp.empty()) break;
		Pii cur = hp.top(); hp.pop();
		forto(cur.sec) {
			if (cur.fir + E[e].cost < dist[v]) {
				dist[v] = cur.fir + E[e].cost;
				hp.push(Pii(dist[v], v));
			}
		}
	}
}

void Dfs(int u) {
	refl[idfn[u] = ++dfs_clock] = u;
	for (int i = 1; i < kLgN && F[u][i - 1]; i++) {
		F[u][i] = F[F[u][i - 1]][i - 1];
	}
	forto(u) {
		if (v == F[u][0]) continue;
		F[v][0] = u;
		Dfs(v);
	}
	odfn[u] = dfs_clock;
}
