// Codeforces 331 D3 - Escaping on Beaveractor
// The last problem put up by Wi Yiqi
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#define fir first
#define sec second
#define x first
#define y second
#ifdef DEBUG
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...)
#endif

const int kMaxn = 1e5 + 10, kLgN = 18, kInf = 0x3f3f3f3f;

typedef std::pair<int, int> Pii;
typedef long long LL;
typedef int IAr[kMaxn];

struct Arrow {
	Pii s, t;
	int id, tp, minx, maxx, miny, maxy;
	Arrow() {}
	Arrow(const Pii & s_, const Pii & t_) :
		s(s_), t(t_) {}

	int type() const {
		return s.y == t.y ? 1 + (s.x > t.x) : 3 + (s.y > t.y);
	}
	void output() const {
		debug(" (%d, %d) --> (%d, %d) id = %d\n",
				s.x, s.y, t.x, t.y, id);
	}
} A[kMaxn << 1], Q[kMaxn];

int n, b, q, totl, top;
int F[kMaxn][kLgN];
Pii G[kMaxn];
IAr vis, S, on_loop, up, to, lg2, start;
LL dep[kMaxn], D[kMaxn][kLgN], len[kMaxn], T[kMaxn];

void Climb(int & v, LL & t);
void Dfs(int u, int r);
Pii Move(const Arrow & a, const Arrow & b, int d);
void PreWork(int tp);

inline bool CmpX1(const Arrow & a1, const Arrow & a2) {
	return a1.maxx == a2.maxx ? a1.id < a2.id :
			a1.maxx > a2.maxx;
}
inline bool CmpX2(const Arrow & a1, const Arrow & a2) {
	return a1.minx == a2.minx ? a1.id < a2.id :
			a1.minx < a2.minx;
}
inline bool CmpY1(const Arrow & a1, const Arrow & a2) {
	return a1.maxy == a2.maxy ? a1.id < a2.id :
			a1.maxy > a2.maxy;
}
inline bool CmpY2(const Arrow & a1, const Arrow & a2) {
	return a1.miny == a2.miny ? a1.id < a2.id :
			a1.miny < a2.miny;
}
inline bool CmpId(const Arrow & a1, const Arrow & a2) {
	return a1.id < a2.id;
}
inline int DistToEdge(const Arrow & a) {
	return a.type() & 1 ? b - (a.type() < 3 ? a.t.x : a.t.y) :
					(a.type() < 3 ? a.t.x : a.t.y);
}
inline bool In(int x, int lb, int ub) {
	if (lb > ub) std::swap(lb, ub);
	return lb <= x && x <= ub;
}
inline int Manhattan(const Pii & p, const Pii & q) {
	return std::abs(p.x - q.x) + std::abs(p.y - q.y);
}
inline Pii Move(const Arrow & a, int d) {
	return a.s.y == a.t.y ? 
		(a.s.x < a.t.x ? Pii(a.t.x + d, a.t.y) :
			Pii(a.t.x - d, a.t.y)) :
		(a.s.y < a.t.y ? Pii(a.t.x, a.t.y + d) :
			Pii(a.t.x, a.t.y - d));
}
inline void Print(const Pii & p) { printf("%d %d\n", p.x, p.y); }
inline void Read(Pii & p) { scanf("%d%d", &p.x, &p.y); }

int main() {
	scanf("%d%d", &n, &b);
	for (int i = 0; i < n; i++) {
		Read(A[i].s), Read(A[i].t);
		A[i].id = i;
	}
	scanf("%d", &q);
	char IN[5];
	for (int i = n; i < n + q; i++) {
		Read(A[i].t);
		scanf("%s%lld", IN, T + (i - n));
		A[i].id = i, A[i].s = A[i].t;
		if (IN[0] == 'U') --A[i].s.y;
		if (IN[0] == 'D') ++A[i].s.y;
		if (IN[0] == 'R') --A[i].s.x;
		if (IN[0] == 'L') ++A[i].s.x;
	}

	for (int i = 0; i < n; i++) {
		A[i].minx = std::min(A[i].s.x, A[i].t.x);
		A[i].maxx = std::max(A[i].s.x, A[i].t.x);
		A[i].miny = std::min(A[i].s.y, A[i].t.y);
		A[i].maxy = std::max(A[i].s.y, A[i].t.y);
	}
	for (int i = n; i < n + q; i++) {
		A[i].minx = A[i].maxx = A[i].t.x;
		A[i].miny = A[i].maxy = A[i].t.y;
	}
	memset(to, 0xff, sizeof to);
	std::sort(A, A + n + q, CmpX1);	// sort by x(dec)
	PreWork(1);	// prepare for --> (x+)
	std::sort(A, A + n + q, CmpX2);	// sort by x(inc)
	PreWork(2);	// prepare for (x-) <--
	std::sort(A, A + n + q, CmpY1);	// sort by y(dec)
	PreWork(3);	// prepare for --> (y+)
	std::sort(A, A + n + q, CmpY2);	// sort by y(inc)
	PreWork(4);	// prepare for (y-) <--
#ifdef DEBUG
	for (int i = 0; i < n; i++) {
		printf(" %d --> %d, cost = %d\n",
				i, G[i].fir, G[i].sec);
	}
#endif
	for (int i = 0, r = 0; i < n; i++) {
		if (!vis[i]) Dfs(i, ++r);
	}
	memset(vis, 0, sizeof vis);
	memset(F, 0xff, sizeof F);
	on_loop[n] = ++totl;
	for (int i = 0, v; i < n; i++) {
		if (on_loop[i] || vis[i]) continue;
		for (top = 0, v = i; !on_loop[v]; v = G[v].fir) S[top++] = v;
		F[S[top - 1]][0] = v, dep[v] = 0;
		for (int fa = v, u = v; top; fa = v) {
			vis[v = S[--top]] = 1;
			up[v] = u;
			dep[v] = dep[fa] + (D[v][0] = G[v].sec);
			for (int j = 1; j < kLgN && ~F[v][j - 1]; j++) {
				F[v][j] = F[F[v][j - 1]][j - 1];
				D[v][j] = D[v][j - 1] + D[F[v][j - 1]][j - 1];
			}
			if (top) F[S[top - 1]][0] = v;
		}
	}
	lg2[0] = -1;
	for (int i = 1; i <= n; i++) lg2[i] = lg2[i >> 1] + 1;
	for (int i = 1; i <= totl; i++) {
		top = 0;
		for (int v = start[i]; !vis[v]; v = G[v].fir) {
			vis[v] = 1, S[top++] = v, up[v] = v;
			F[v][0] = G[v].fir, D[v][0] = G[v].sec;
			len[i] += G[v].sec;
		}
		for (int j = 1, lim = lg2[top]; j <= lim; j++) {
			for (int k = 0, u; k < top; k++) {
				u = S[k];
				F[u][j] = F[F[u][j - 1]][j - 1];
				D[u][j] = D[u][j - 1] + D[F[u][j - 1]][j - 1];
			}
		}
	}

	for (int i = 0, q0 = 0, n0 = 0; i < n + q; i++) {
		if (A[i].id >= n) {
			Q[q0] = A[i];
			Q[q0++].id -= n;
		} else {
			A[n0++] = A[i];
		}
	}
	std::sort(Q, Q + q, CmpId);
	std::sort(A, A + n, CmpId);
	A[18].output();
	for (int i = 0, v; i < q; i++) {
		LL dis;
		assert(~to[i]);
		debug(" to arrow %d\n", to[i]);
		A[to[i]].output();
		if ((v = to[i]) == kInf) {
			Print(Move(Q[i], std::min((LL)DistToEdge(Q[i]), T[i])));
			continue;
		} else dis = Manhattan(Q[i].t, A[v].t);
		debug("  dis = %lld, T[i] = %lld\n", dis, T[i]);
		if (dis < T[i]) {
			T[i] -= dis;
			debug("  dep[v] = %lld, up[v] = %d\n", dep[v], up[v]);
			if (T[i] >= dep[v]) {
				if (up[v] == n) {
					LL tmp = dep[v];
					Climb(v, tmp);
					debug("   after climb %lld, v = %d\n", dep[v] - 1, v);
					debug("   type_v %d\n", A[v].type());
					debug("   dist to edge = %d\n", DistToEdge(A[v]));
					Print(Move(A[v], DistToEdge(A[v]))); 
				} else {
					T[i] -= dep[v];
					v = up[v];
					T[i] %= len[on_loop[v]];
					Climb(v, T[i]);
				Print(Move(A[v], A[G[v].fir], T[i]));
				}
			} else {
				Climb(v, T[i]);
				if (G[v].fir != n) Print(Move(A[v], A[G[v].fir], T[i]));
				else Print(Move(A[v], T[i]));
			}
		} else {
			if (In(Q[i].t.x, A[v].s.x, A[v].t.x) &&
				In(Q[i].t.y, A[v].s.y, A[v].t.y)) {
				Q[i].s = Q[i].t;
				if (A[v].type() == 1) --Q[i].s.x;
				if (A[v].type() == 2) ++Q[i].s.x;
				if (A[v].type() == 3) --Q[i].s.y;
				if (A[v].type() == 4) ++Q[i].s.y;
			}
			Print(Move(Q[i], A[v], T[i]));
		}
	}

	return 0;
}

Pii Move(const Arrow & a, const Arrow & b, int d) {
	int d0 = a.type() < 3 ? std::abs(b.t.x - a.t.x) : 
			std::abs(b.t.y - a.t.y);
	debug(" d0 = %d, d = %d\n", d0, d);
	if (d <= d0) return Move(a, d);
	Pii corner = a.type() < 3 ? Pii(b.t.x, a.t.y) :
								Pii(a.t.x, b.t.y);
	Arrow c(corner, corner);
	if (b.type() == 1) --c.s.x;
	if (b.type() == 2) ++c.s.x;
	if (b.type() == 3) --c.s.y;
	if (b.type() == 4) ++c.s.y;
	return Move(c, d - d0);
}

namespace smt {
	int col[kMaxn << 2];
#define lson (rt << 1)
#define rson (rt << 1 | 1)
	void PushDown(int rt) {
		if (col[rt] == -1) return;
		col[lson] = col[rson] = col[rt];
		col[rt] = -1;
	}
	void _U(int rt, int l, int r, int ql, int qr, int v) {
		if (ql <= l && r <= qr) {
			col[rt] = v;
			return;
		}
		PushDown(rt);
		int mid = l + r >> 1;
		if (ql <= mid) _U(lson, l, mid, ql, qr, v);
		if (qr > mid) _U(rson, mid + 1, r, ql, qr, v);
	}
	int Query(int rt, int l, int r, int qp) {
		if (~col[rt]) return col[rt];
		int mid = l + r >> 1;
		if (qp <= mid) return Query(lson, l, mid, qp);
		return Query(rson, mid + 1, r, qp);
	}
#undef lson
#undef rson
	inline void Modify(int lb, int ub, int val) {
		if (lb > ub) std::swap(lb, ub);
		_U(1, 0, b, lb, ub, val);
	}
}

void Climb(int & v, LL & t) {
	for (int j = kLgN - 1; j >= 0 && t; j--) {
		if (~F[v][j] && F[v][j] != n && D[v][j] <= t) {
			t -= D[v][j];
			v = F[v][j];
		}
	}
}

void FindNext(const Arrow & a) {
	int t, v = smt::Query(1, 0, b, a.type() < 3 ? a.t.y : a.t.x);
	if (a.id >= n) {
		to[a.id - n] = v == kInf ? v : A[v].id;
	} else {
		t = v == kInf ? DistToEdge(a) : Manhattan(a.t, A[v].t);
		G[a.id] = Pii(v == kInf ? n : A[v].id, t);
	}
}

void PreWork(int tp) {
	smt::Modify(0, b, kInf);
	for (int i = 0; i < n + q; i++) {
		if (A[i].type() == tp) FindNext(A[i]);
		if (A[i].id < n) {
			if (tp < 3) smt::Modify(A[i].s.y, A[i].t.y, i);
			else smt::Modify(A[i].s.x, A[i].t.x, i);
		}
	}
}

void Dfs(int u, int r) {
	if (u == n) return;
	vis[u] = r, S[top++] = u;
	if (vis[G[u].fir] == vis[u]) {
		for (++totl; S[top - 1] != G[u].fir; ) on_loop[S[--top]] = totl;
		on_loop[S[--top]] = totl;
		start[totl] = u;
	} else if (!vis[G[u].fir]) Dfs(G[u].fir, r);
	if (top && S[top - 1] == u) --top;
}
