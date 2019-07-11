#include <algorithm>
#include <cstdio>
#include <set>

#define fir first
#define sec second
#define forto(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)

const int kMaxn = 3e4 + 10, kMaxm = 1e5 + 10;

typedef int IAr[kMaxn];
typedef std::pair<int, int> Pii;
typedef std::set<Pii> ESet;

struct Edge {
	int to, tag, next;
} E[kMaxm << 1];
struct Oper {
	int t, u, v;
} O[40010];

int n, m, tote = 1, totr, toto;
int ans[kMaxm];
IAr back, vis;
ESet EE;

namespace hld {
	void Init();
	void Cover(int, int);
	int Dist(int, int);
}
inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, 0, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, 0, back[v]}, back[v] = tote;
}
void Dfs(int);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0, u, v; i < m; i++) {
		scanf("%d%d", &u, &v);
		if (u > v) std::swap(u, v);
		EE.insert(Pii(u, v));
	}
	for (int t; ; toto++) {
		scanf("%d", &t);
		if (t == -1) break;
		scanf("%d%d", &O[toto].u, &O[toto].v);
		if (!(O[toto].t = t)) {
			if (O[toto].u > O[toto].v) std::swap(O[toto].u, O[toto].v);
			EE.erase(Pii(O[toto].u, O[toto].v));
		}
	}

	for (ESet::iterator it = EE.begin(); it != EE.end(); ++it) {
		AddEdge(it->fir, it->sec);
	}
	Dfs(1);
	hld::Init();

	for (int i = 1; i <= n; i++) {
		forto(i) {
			if (E[e].tag) continue;
			hld::Cover(i, v);
		}
	}

	for (int i = toto - 1; i >= 0; i--) {
		if (O[i].t) ans[totr++] = hld::Dist(O[i].u, O[i].v);
		else hld::Cover(O[i].u, O[i].v);
	}
	for (int i = totr - 1; i >= 0; i--) printf("%d\n", ans[i]);
	return 0;
}

namespace smt {
	struct Node {
		int sum, tag;
	} T[kMaxn << 1];

	inline int Id(int l, int r) { return l + r | l != r; }
	void Build(int l, int r) {
		int cur = Id(l, r);
		T[cur].sum = r - l + 1;
		T[cur].tag = -1;
		if (l == r) return;
		int mid = l + r >> 1;
		Build(l, mid); Build(mid + 1, r);
	}
	void PushDown(int l, int m, int r) {
		int cur = Id(l, r);
		if (~T[cur].tag) {
			int ls = Id(l, m), rs = Id(m + 1, r);
			T[ls].sum = T[cur].tag * (m - l + 1);
			T[rs].sum = T[cur].tag * (r - m);
			T[ls].tag = T[rs].tag = T[cur].tag;
			T[cur].tag = -1;
		}
	}
	void Value(int l, int r, int ql, int qr, int val) {
		int cur = Id(l, r);
		if (ql <= l && r <= qr) {
			T[cur].sum = val * (r - l + 1);
			T[cur].tag = val;
			return;
		}
		int mid = l + r >> 1;
		PushDown(l, mid, r);
		if (ql <= mid) Value(l, mid, ql, qr, val);
		if (qr > mid) Value(mid + 1, r, ql, qr, val);
		T[cur].sum = T[Id(l, mid)].sum + T[Id(mid + 1, r)].sum;
	}
	int Query(int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return T[Id(l, r)].sum;
		int mid = l + r >> 1, res = 0;
		PushDown(l, mid, r);
		if (ql <= mid) res += Query(l, mid, ql, qr);
		if (qr > mid) res += Query(mid + 1, r, ql, qr);
		return res;
	}
}

namespace hld {
	IAr sz, fa, top, dfn, dep, son;

	void Cover(int u, int v) {
	//	printf(" cover %d <-> %d\n", u, v);
		for (; top[u] != top[v]; u = fa[top[u]]) {
			if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
		//	printf("  value [%d, %d] 0\n", dfn[top[u]], dfn[u]);
			smt::Value(1, n, dfn[top[u]], dfn[u], 0);
		}
		if (dep[u] < dep[v]) std::swap(u, v);
		int vl = smt::Query(1, n, dfn[v], dfn[v]);
	//	printf("  value [%d, %d] 0\n", dfn[v], dfn[u]);
		smt::Value(1, n, dfn[v], dfn[u], 0);
	//	printf("  value [%d, %d] %d\n", dfn[v], dfn[v], vl);
		if (vl) smt::Value(1, n, dfn[v], dfn[v], vl);
	}
	int Dist(int u, int v) {
		int res = 0;
		for (; top[u] != top[v]; u = fa[top[u]]) {
			if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
			res += smt::Query(1, n, dfn[top[u]], dfn[u]);
		}
		if (dep[u] < dep[v]) std::swap(u, v);
		return res + smt::Query(1, n, dfn[v], dfn[u]) - 
					smt::Query(1, n, dfn[v], dfn[v]);
	}
	void Dfs(int u) {
		sz[u] = 1, son[u] = -1;
		forto(u) {
			if (v == fa[u] || !E[e].tag) continue;
			fa[v] = u, dep[v] = dep[u] + 1;
		//	printf(" %d -> %d\n", u, v);
			Dfs(v);
			if (son[u] == -1 || sz[v] > sz[son[u]]) son[u] = v;
			sz[u] += sz[v];
		}
	}
	void Dfs(int u, int tp) {
		static int dfs_clock = 0;
		dfn[u] = ++dfs_clock, top[u] = tp;
	//	printf(" dfn %d=%d\n", u, dfn[u]);
		if (son[u] == -1) return;
		Dfs(son[u], tp);
		forto(u) {
			if (v == fa[u] || !E[e].tag || v == son[u]) continue;
			Dfs(v, v);
		}
	}
	void Init() {
		dep[1] = 1;
		Dfs(1);
		Dfs(1, 1);
		smt::Build(1, n);
	}
}

void Dfs(int u) {
	vis[u] = 1;
	forto(u) {
		if (vis[v]) continue;
		E[e].tag = E[e ^ 1].tag = 1;
		Dfs(v);
	}
}
