// SPOJ QTREE
#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXV = 1e4 + 10;
const int INF = 0x3f3f3f3f;

typedef int IntAr[MAXV];

struct Edge {
	int to, cost, id, next;
} E[MAXV << 1];

int N, tote;
IntAr last;
char O[20];

namespace HLD {
	IntAr pos, fa, dep, sz, son, rk, top, he;
	int rank;

	namespace SMT {
		int QL, QR, NUM;

		void build(int rt, int l, int r);
		void _UPD(int rt, int l, int r);
		inline void update(int id, int x) {
			QR = id, NUM = x;
			_UPD(1, 1, N);
		}
	}

	int query(int u, int v);
	inline void update(int eid, int x) {
		SMT::update(pos[eid], x);
	}
	void dfs1(int u);
	void dfs2(int u, int tp, int pre);
	inline void init() {
		memset(son, 0xff, sizeof son);
		dep[1] = 1, rank = 0;
		dfs1(1);
		dfs2(1, 1, 0);
		SMT::build(1, 1, N);
	}
}

inline void add_edge(int u, int v, int c_, int id_) {
	E[++tote] = (Edge){v, c_, id_, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, c_, id_, last[v]}, last[v] = tote;
}

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d", &N);
		tote = 0;
		memset(last, 0, sizeof last);
		for (int i = 1, u, v, c; i < N; i++) {
			scanf("%d%d%d", &u, &v, &c);
			add_edge(u, v, c, i);
		}
		HLD::init();
		scanf("%s", O);
		for (int x, y; O[0] != 'D'; scanf("%s", O)) {
			scanf("%d%d", &x, &y);
			if (O[0] == 'C') HLD::update(x, y);
			else printf("%d\n", HLD::query(x, y));
		}
	}

	return 0;
}

#define lson rt << 1
#define rson rt << 1 | 1
#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

namespace HLD {
	namespace SMT {
		IntAr A;
		int T[MAXV << 2];

		void build(int rt, int l, int r) {
			if (r - l == 1) {
				T[rt] = A[r];
				return;
			}
			int mid = l + r >> 1;
			build(lson, l, mid), build(rson, mid, r);
			T[rt] = std::max(T[lson], T[rson]);
		}

		int _Q(int rt, int l, int r) {
			if (QL <= l && r <= QR) return T[rt];
			if (r < QL || l > QR || r - l == 1) return -INF;
			int mid = l + r >> 1;
			return std::max(_Q(lson, l, mid), _Q(rson, mid, r));
		}

		void _UPD(int rt, int l, int r) {
			if (r - l == 1) {
				T[rt] = NUM;
				return;
			}
			int mid = l + r >> 1;
			if (QR <= mid) _UPD(lson, l, mid);
			else _UPD(rson, mid, r);
			T[rt]= std::max(T[lson], T[rson]);
		}

		inline int query(int l, int r) {
			QL = l, QR = r;
			return _Q(1, 1, N);
		}
	}

	int query(int u, int v) {
		int ret = -INF;
//		printf(" query(%2d, %2d)\n", u, v);
		for (; top[u] ^ top[v]; u = fa[top[u]]) {
//			printf(" u: %2d, top[u]: %2d; v: %2d, top[v]: %2d\n", u, top[u], v, top[v]);
			if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
//			printf(" u (%2d) -> top[u] (%2d)\n", u, top[u]);
			ret = std::max(ret, SMT::query(std::max(1, rk[top[u]] - 1), rk[u]));
		}
		if (dep[u] < dep[v]) std::swap(u, v);
		return std::max(ret, SMT::query(rk[v], rk[u]));
	}

	void dfs1(int u) {
		sz[u] = 1;
		forto(u) {
			if (v == fa[u]) continue;
			dep[v] = dep[u] + 1, fa[v] = u;
			dfs1(v);
			sz[u] += sz[v];
			if (son[u] == -1 || sz[v] > sz[son[u]]) son[u] = v, he[u] = e;
		}
	}

	void dfs2(int u, int tp, int pre) {
		rk[u] = ++rank, top[u] = tp;
		if (pre) {
			using SMT::A;
			pos[E[pre].id] = rk[u];
			A[rk[u]] = E[pre].cost;
		}
		if (son[u] == -1) return;
		dfs2(son[u], tp, he[u]);
		forto(u) {
			if (v == son[u] || v == fa[u]) continue;
			dfs2(v, v, e);
		}
	}
}
