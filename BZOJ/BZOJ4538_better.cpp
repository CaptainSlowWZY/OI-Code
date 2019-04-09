// HNOI 2016
// solve in O(n log^2 n)
#include <cstdio>
#include <cstring>
#include <algorithm>

#define forto(_) for (int e = last[_], v = E[e].to; e; \
						v = E[e = E[e].next].to)

const int kMaxn = 1e5 + 10;

typedef int IAr[kMaxn];

struct Oper {
	int tp, u, v, t;
} O[kMaxn << 1];
struct Edge {
	int to, next;
} E[kMaxn << 1];

int n, m, tote, maxv, totq;
IAr last, ans;

namespace hld {
	IAr dep, son, fa, sz, top, dfn;

	void Dfs1(int u);
	void Dfs2(int u, int tp);
	inline void Init() {
		dep[1] = 1;
		Dfs1(1);
		Dfs2(1, 1);
	}
}
inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, last[v]}, last[v] = tote;
}
void Solve(int al, int ar, int ql, int qr);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		AddEdge(u, v);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d", &O[i].tp);
		switch (O[i].tp) {
			case 0 :
				scanf("%d%d%d", &O[i].u, &O[i].v, &O[i].t);
				maxv = std::max(maxv, O[i].t);
				break;
			case 1 :
				scanf("%d", &O[i].t);
				O[i] = O[O[i].t - 1];
				O[i].t = -O[i].t;
				break;
			case 2 :
				scanf("%d", &O[i].u);
				O[i].t = totq++;
		}
	}

	hld::Init();
	Solve(-1, maxv, 0, m);

	for (int i = 0; i < totq; i++) {
		printf("%d\n", ans[i] > 0 ? ans[i] : -1);
	}
	return 0;
}

namespace hld {
	void Dfs1(int u) {
		sz[u] = 1, son[u] = -1;
		forto(u) {
			if (v == fa[u]) continue;
			fa[v] = u, dep[v] = dep[u] + 1;
			Dfs1(v);
			sz[u] += sz[v];
			if (son[u] == -1 || sz[v] > sz[son[u]]) son[u] = v;
		}
	}
	void Dfs2(int u, int tp) {
		static int dfs_clock = 0;
		dfn[u] = ++dfs_clock, top[u] = tp;
		if (son[u] == -1) return;
		Dfs2(son[u], tp);
		forto(u) {
			if (v == fa[u] || v == son[u]) continue;
			Dfs2(v, v);
		}
	}
	// I need a data structre support iterval-modify & point-query
	// bit is best choise
	namespace bit {
		int T[kMaxn];
		
		void Add(int p, int d) {
			for (; p <= n; p += p & -p) T[p] += d;
		}
		inline void Add(int l, int r, int d) {
			Add(l, d), Add(r + 1, -d);
		}
		int Query(int p) {
			int ret = 0;
			for (; p > 0; p &= p - 1) ret += T[p];
			return ret;
		}
	}
	void Modify(int u, int v, int del) {
	//	printf(" %d --> %d, += %d\n", u, v, del);
		for (; top[u] ^ top[v]; u = fa[top[u]]) {
			if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
			bit::Add(dfn[top[u]], dfn[u], del);
		}
		if (dep[u] > dep[v]) std::swap(u, v);
		bit::Add(dfn[u], dfn[v], del);
	}
}

void Solve(int al, int ar, int ql, int qr) {
	if (ql >= qr) return;
	if (qr - ql == 1) {
		if (O[ql].tp == 2) ans[O[ql].t] = -1;
		return;
	}
/*	fprintf(stderr, " ans (%d, %d], produce [%d, %d)\n",
			al, ar, ql, qr);*/
	// Answer in (al, ar], producing operation in [ql, qr)
	if (ar - al <= 1) {
		for (int i = ql; i < qr; i++) {
			if (O[i].tp) ans[O[i].t] = ar;
		}
		return;
	}
	static int flag[kMaxn << 1];
	static Oper buf[kMaxn << 1];
	int mid = al + ar >> 1, cntp = 0, ptr = ql;

	for (int i = ql; i < qr; i++) {
		using namespace hld;
		flag[i] = 0;
		if (!O[i].tp) {
			if (std::abs(O[i].t) > mid) {
				Modify(O[i].u, O[i].v, O[i].t > 0 ? 1 : -1);
				O[i].t > 0 ? ++cntp : --cntp;
				flag[i] = 1;
			} else {
				buf[ptr++] = O[i];
			}
		} else {
			if (bit::Query(dfn[O[i].u]) == cntp) buf[ptr++] = O[i];
			else flag[i] = 1;
		}
	}
	int lb = ptr;
	for (int i = ql; i < qr; i++) {
		if (flag[i]) buf[ptr++] = O[i];
		if (!O[i].tp && std::abs(O[i].t) > mid) {
			hld::Modify(O[i].u, O[i].v, O[i].t < 0 ? 1 : -1);
		}
	}
	for (int i = ql; i < qr; i++) O[i] = buf[i];
	Solve(al, mid, ql, lb);
	Solve(mid, ar, lb, qr);
}
