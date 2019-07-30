#include <algorithm>
#include <cstdio>

#define forto(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)

const int kMaxn = 1e5 + 10;

typedef int IAr[kMaxn];

struct Edge {
	int to, next;
} E[kMaxn << 1];

int n, m, tote;
IAr back, buf;

namespace smt {
	int Query(int l, int r, int ql, int qr);
}
namespace hld {
	int dfs_clock;
	IAr dep, sz, son, fa, top, dfn;
	inline int Query(int x) {
		return smt::Query(1, n, dfn[x], dfn[x] + sz[x] - 1);
	}
	int Query(int x, int y);
	void Init();
}
namespace lct {
	void Access(int);
}
inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, back[v]}, back[v] = tote;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		AddEdge(u, v);
	}

	hld::Init();
	for (int tp, x, y; m--; ) {
		scanf("%d%d", &tp, &x);
		if (tp == 1) {
			lct::Access(x);
		} else if (tp == 2) {
			scanf("%d", &y);
			printf("%d\n", hld::Query(x, y));
		} else printf("%d\n", hld::Query(x));
	}

	return 0;
}

namespace smt {
	struct Node {
		int max, tag;
	} T[kMaxn << 1];

	inline int Id(int l, int r) { return l + r | l != r; }
	void Build(int l, int r) {
		int cur = Id(l, r);
		T[cur].tag = 0;
		if (l == r) return (void)(T[cur].max = buf[l]);
		int mid = l + r >> 1;
		Build(l, mid); Build(mid + 1, r);
		T[cur].max = std::max(T[Id(l, mid)].max, T[Id(mid + 1, r)].max);
	}
	void PushDown(int l, int m, int r) {
		int u = Id(l, r);
		if (!T[u].tag) return;
		int ls = Id(l, m), rs = Id(m + 1, r);
		T[ls].max += T[u].tag, T[ls].tag += T[u].tag;
		T[rs].max += T[u].tag, T[rs].tag += T[u].tag;
		T[u].tag = 0;
	}
	void Modify(int l, int r, int ql, int qr, int del) {
		int cur = Id(l, r);
		if (ql <= l && r <= qr) {
			T[cur].max += del, T[cur].tag += del;
			return;
		}
		int mid = l + r >> 1;
		PushDown(l, mid, r);
		if (ql <= mid) Modify(l, mid, ql, qr, del);
		if (qr > mid) Modify(mid + 1, r, ql, qr, del);
		T[cur].max = std::max(T[Id(l, mid)].max, T[Id(mid + 1, r)].max);
	}
	int Query(int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return T[Id(l, r)].max;
		int mid = l + r >> 1, res = 0;
		PushDown(l, mid, r);
		if (ql <= mid) res = Query(l, mid, ql, qr);
		if (qr > mid) res = std::max(res, Query(mid + 1, r, ql, qr));
		return res;
	}
}

namespace lct {
	struct Node {
		int fa, ch[2];
	} T[kMaxn];

#define fa(_) (T[_].fa)
#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])

	inline bool IsRoot(int u) {
		return lson(fa(u)) != u && rson(fa(u)) != u;
	}
	inline int Relat(int u) { return rson(fa(u)) == u; }
	void Rotate(int u) {
		int prf = fa(u), ff = fa(prf), r = Relat(u);
		if (!IsRoot(prf)) T[ff].ch[Relat(prf)] = u;
		if (T[u].ch[r ^ 1]) fa(T[u].ch[r ^ 1]) = prf;
		T[prf].ch[r] = T[u].ch[r ^ 1], T[u].ch[r ^ 1] = prf;
		fa(prf) = u, fa(u) = ff;
	}
	void Splay(int u) {
		while (!IsRoot(u)) {
			if (IsRoot(fa(u))) Rotate(u);
			else if (Relat(u) == Relat(fa(u))) {
				Rotate(fa(u)), Rotate(u);
			} else {
				Rotate(u), Rotate(u);
			}
		}
	}
	int FindRoot(int u) {
		while (lson(u)) u = lson(u);
		return u;
	}
	void Access(int u) {
		for (int t, v = 0; u; u = fa(v = u)) {
			Splay(u);
			using namespace hld;
			if (rson(u)) {
				t = FindRoot(rson(u));
				smt::Modify(1, n, dfn[t], dfn[t] + sz[t] - 1, 1);
			}
			if (rson(u) = v) {
				t = FindRoot(rson(u));
				smt::Modify(1, n, dfn[t], dfn[t] + sz[t] - 1, -1);
			}
		}
	}
}

namespace hld {
	int Lca(int x, int y) {
		while (top[x] != top[y]) {
			if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
			x = fa[top[x]];
		}
		return dep[x] < dep[y] ? x : y;
	}
	int Query(int x, int y) {
		using smt::Query;
		int l = dfn[Lca(x, y)];
		return Query(1, n, dfn[x], dfn[x]) + Query(1, n, dfn[y], dfn[y]) -
			Query(1, n, l, l) * 2 + 1;
	}
	void Dfs(int u) {
		sz[u] = 1, son[u] = -1;
		forto(u) {
			if (v == fa[u]) continue;
			fa[v] = u, dep[v] = dep[u] + 1;
			Dfs(v);
			if (son[u] == -1 || sz[v] > sz[son[u]]) son[u] = v;
			sz[u] += sz[v];
		}
	}
	void Dfs(int u, int tp) {
		buf[dfn[u] = ++dfs_clock] = dep[u], top[u] = tp;
		if (son[u] == -1) return;
		Dfs(son[u], tp);
		forto(u) {
			if (v == fa[u] || v == son[u]) continue;
			Dfs(v, v);
		}
	}
	void Init() {
		dep[1] = 1;
		Dfs(1);
		Dfs(1, 1);
		smt::Build(1, n);
		for (int i = 1; i <= n; i++)
			lct::T[i].fa = fa[i];
	}
}
