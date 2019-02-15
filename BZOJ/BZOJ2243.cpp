// BZOJ 2243
// SDOI 2011
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)
#ifdef DEBUG
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif

const int MAXN = 1e5 + 5, INF = 0x3f3f3f3f;

typedef int IntAr[MAXN];

struct Edge {
	int to, next;
} E[MAXN << 1];
struct Node {
	int totc, lcol, rcol, tag;
	Node(int tc_ = 0, int lc_ = -1, int rc_ = -1, int tg_ = -1) : totc(tc_), lcol(lc_), rcol(rc_), tag(tg_) {}
	Node operator+(const Node & n) const {
		return ~lcol && ~n.rcol ? Node(totc + n.totc - int(rcol == n.lcol), lcol, n.rcol) :
								(~lcol ? *this : n);
	}
	Node reverse() const {
		return Node(totc, rcol, lcol, tag);
	}
	void out() const {
		debug("    totc = %d, (L%d, R%d), tag?%d\n", totc, lcol, rcol, tag);
	}
};

int N, Q, tote;
IntAr last, col;

namespace HLD {
	IntAr fa, dep, son, sz, top, rk;
	namespace SMT {
		Node T[MAXN << 1];
		void build(int l, int r);
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
	void modify(int u, int v, int c);
	int query(int u, int v);
}

inline void add_edge(int u, int v) {
   E[++tote] = (Edge){v, last[u]}, last[u] = tote;	
   E[++tote] = (Edge){u, last[v]}, last[v] = tote;	
}

int main() {
	scanf("%d%d", &N, &Q);
	for (int i = 1; i <= N; i++) scanf("%d", col + i);
	for (int i = 1, u, v; i < N; i++) {
		scanf("%d%d", &u, &v);
		add_edge(u, v);
	}
	
	HLD::init();
	char IN[10];
	for (int u, v, c; Q--; ) {
		scanf("%s%d%d", IN, &u, &v);
		if (IN[0] == 'C') {
			scanf("%d", &c);
			HLD::modify(u, v, c);
		}
		else printf("%d\n", HLD::query(u, v));
	}

	return 0;
}

namespace HLD {
	namespace SMT {
		int QL, QR, COLOR;

		inline int id(int l, int r) { return l + r | l != r; }
		void push_up(int l, int r) {
			int mid = l + r >> 1;
			T[id(l, r)] = T[id(l, mid)] + T[id(mid + 1, r)];
		}
		void build(int l, int r) {
			if (l == r) return;
			int mid = l + r >> 1;
			build(l, mid), build(mid + 1, r);
			push_up(l, r);
		}
		void push_down(int l, int r) {
			int cur = id(l, r);
			if (~T[cur].tag) {
				int mid = l + r >> 1;
				T[id(l, mid)] = Node(1, T[cur].tag, T[cur].tag, T[cur].tag);
				T[id(mid + 1, r)] = Node(1, T[cur].tag, T[cur].tag, T[cur].tag);
				T[cur].tag = -1;
			}
		}
		Node _Q(int l, int r) {
			int cur = id(l, r);
			if (QL <= l && r <= QR) return T[cur];
			int mid = l + r >> 1;
			push_down(l, r);
			if (QL <= mid && QR > mid) {
				return _Q(l, mid) + _Q(mid + 1, r);
			}
			else if (QL <= mid) return _Q(l, mid);
			return _Q(mid + 1, r);
		}
		inline Node query(int ql, int qr) {
			QL = ql, QR = qr;
			return _Q(1, N);
		}
		void _UPD(int l, int r) {
			if (QL <= l && r <= QR) {
				T[id(l, r)] = Node(1, COLOR, COLOR, COLOR);
				return;
			}
			int mid = l + r >> 1;
			push_down(l, r);
			if (QL <= mid) _UPD(l, mid);
			if (QR > mid) _UPD(mid + 1, r);
			push_up(l, r);
		}
		inline void update(int ul, int ur, int uc) {
			QL = ul, QR = ur, COLOR = uc;
			_UPD(1, N);
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
		SMT::T[SMT::id(rk[u], rk[u])] = Node(1, col[u], col[u]);
		if (son[u] == -1) return;
		dfs2(son[u], tp);
		forto(u) {
			if (v == fa[u] || v == son[u]) continue;
			dfs2(v, v);
		}
	}
	void modify(int u, int v, int col) {
		for (; top[u] ^ top[v]; u = fa[top[u]]) {
			if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
			SMT::update(rk[top[u]], rk[u], col);
		}
		if (dep[u] < dep[v]) std::swap(u, v);
		SMT::update(rk[v], rk[u], col);
	}
	int query(int u, int v) {
		Node ahead, back;
		debug("===== Query =====\n  u %d v %d\n", u, v);
		for (; top[u] ^ top[v]; ) {
			if (dep[top[u]] > dep[top[v]]) {
				debug("  u %d climb -> top[u] %d\n  Ret\n", u, top[u]);
				SMT::query(rk[top[u]], rk[u]).out();
				ahead = SMT::query(rk[top[u]], rk[u]) + ahead;
				u = fa[top[u]];
			}
			else {
				debug("  v %d climb -> top[v] %d\n  Ret\n", v, top[v]);
				SMT::query(rk[top[v]], rk[v]).out();
				back = SMT::query(rk[top[v]], rk[v]) + back;
				v = fa[top[v]];
			}
		}
		if (dep[u] > dep[v]) {
			debug("  u %d climb -> top[u] %d\n  Ret\n", u, top[u]);
			SMT::query(rk[v], rk[u]).out();
			ahead = SMT::query(rk[v], rk[u]) + ahead;
		}
		else {
			debug("  v %d climb -> top[v] %d\n  Ret\n", v, top[v]);
			SMT::query(rk[u], rk[v]).out();
			back = SMT::query(rk[u], rk[v]) + back;
		}
		debug(" Ahead_reverse%c", '\n');
		ahead.reverse().out();
		debug(" back%c", '\n');
		back.out();
		Node tmp = (ahead.reverse() + back);
		// assert(~tmp.lcol && ~tmp.rcol);
		debug("===== End Q =====%c", '\n');
		return tmp.totc;
	}
}
