// BZOJ 1036
// ZJOI 2008
#include <cstdio>
#include <cstring>
#include <algorithm>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int MAXN = 3e4 + 5, INF = 0x3f3f3f3f;

typedef int IntAr[MAXN];

struct Edge {
	int to, next;
} E[MAXN << 1];
struct Node {
	int sum, mx;
	Node(int s_ = 0, int m_ = -INF) : sum(s_), mx(m_) {}
	Node operator+(const Node & n) const {
		return Node(sum + n.sum, std::max(mx, n.mx));
	}
}; 

int N, Q, tote;
IntAr last, W;

namespace HLD {
	IntAr fa, dep, son, sz, top, rk;
	namespace SMT {
		Node T[MAXN << 1];
		int QL, QR, VAL;

		const Node & build(int l, int r);
		Node _Q(int l, int r);
		const Node & _UPD(int l, int r);
		inline Node query(int ql, int qr) {
			QL = ql, QR = qr;
			return _Q(1, N);
		}
		inline void update(int pos, int val) {
			QL = QR = pos, VAL = val;
			_UPD(1, N);
		}
	}

	void dfs1(int u);
	void dfs2(int u, int tp);
	inline void init() {
		memset(son, 0xff, sizeof son);
		dep[1] = 1;
		dfs1(1);
		dfs2(1, 1);
		SMT::build(1, N);
	}
	inline void modify(int u, int t) {
		SMT::update(rk[u], t);
	}
	Node query(int u, int v);
}

inline void add_edge(int u, int v) {
   E[++tote] = (Edge){v, last[u]}, last[u] = tote;	
   E[++tote] = (Edge){u, last[v]}, last[v] = tote;	
}

int main() {
	scanf("%d", &N);
	for (int i = 1, u, v; i < N; i++) {
		scanf("%d%d", &u, &v);
		add_edge(u, v);
	}
	for (int i = 1; i <= N; i++) scanf("%d", W + i);
	
	HLD::init();
	scanf("%d", &Q);
	char IN[10];
	for (int u, o; Q--; ) {
		scanf("%s%d%d", IN, &u, &o);
		if (IN[0] == 'C') HLD::modify(u, o);
		else printf("%d\n", IN[1] == 'M' ? HLD::query(u, o).mx : HLD::query(u, o).sum);
	}

	return 0;
}

namespace HLD {
	namespace SMT {
		inline int id(int l, int r) { return l + r | l != r; }
		const Node & build(int l, int r) {
			int cur = id(l, r);
			if (l == r) return T[cur];
			int mid = l + r >> 1;
			return T[cur] = build(l, mid) + build(mid + 1, r);
		}
		Node _Q(int l, int r) {
			if (QR < l || r < QL) return Node();
			int cur = id(l, r);
			if (QL <= l && r <= QR) return T[cur];
			int mid = l + r >> 1;
			return _Q(l, mid) + _Q(mid + 1, r);
		}
		const Node & _UPD(int l, int r) {
			int cur = id(l, r);
			if (QR < l || r < QL) return T[cur];
			if (l == r) return T[cur] = Node(VAL, VAL);
			int mid = l + r >> 1;
			return T[cur] = _UPD(l, mid) + _UPD(mid + 1, r);
		}
	}

	void dfs1(int u) {
		sz[u] = 1;
		forto(u) {
			if (v == fa[u]) continue;
			fa[v] = u, dep[v] = dep[u] + 1;
			dfs1(v);
			sz[u] += sz[v];
			if (son[u] == -1 || sz[son[u]] < sz[v]) son[u] = v;
		}
	}
	void dfs2(int u, int tp) {
		static int totrk = 0;
		rk[u] = ++totrk, top[u] = tp;
		SMT::T[SMT::id(rk[u], rk[u])] = Node(W[u], W[u]);
		if (son[u] == -1) return;
		dfs2(son[u], tp);
		forto(u) {
			if (v == fa[u] || v == son[u]) continue;
			dfs2(v, v);
		}
	}
	Node query(int u, int v) {
		Node ret;
		for (; top[u] ^ top[v]; u = fa[top[u]]) {
			if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
			ret = ret + SMT::query(rk[top[u]], rk[u]);
		}
		if (dep[u] < dep[v]) std::swap(u, v);
		return ret + SMT::query(rk[v], rk[u]);
	}
}
