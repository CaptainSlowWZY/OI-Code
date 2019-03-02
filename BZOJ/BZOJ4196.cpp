#include <cstdio>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int kMaxn = 1e5 + 10;

typedef int IntArr[kMaxn];

struct Edge {
	int to, next;
} E[kMaxn << 1];

int n, q, tote, last[kMaxn];
char O[20];

namespace hld {
	IntArr fa, dep, sz, son, top, dfn;

	void Dfs1(int u);
	void Dfs2(int u, int tp);
	inline void Init() {
		fa[0] = -1, dep[0] = 1;
		Dfs1(0);
		Dfs2(0, 0);
	}
	int Install(int sw);
	int Uninstall(int sw);
}
inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
}

int main() {
	scanf("%d", &n);
	for (int i = 1, ni; i < n; i++) {
		scanf("%d", &ni);
		AddEdge(ni, i);
	}

	hld::Init();
	scanf("%d", &q);
	for (int x; q--; ) {
		scanf("%s%d", O, &x);
		printf("%d\n", O[0] == 'i' ? hld::Install(x) : hld::Uninstall(x));
	}
	return 0;
}

namespace hld {
	namespace smt {
		struct Node {
			int val, tag;
		} T[kMaxn << 1];
		int ql, qr, sign;

		inline int Id(int l, int r) { return l + r | l != r; }
		void PushDown(int l, int r) {
			int cur = Id(l, r);
			if (T[cur].tag) {
				int mid = l + r >> 1, lson = Id(l, mid), rson = Id(mid + 1, r);
				T[lson].val = T[cur].tag > 0 ? mid - l + 1 : 0;
				T[rson].val = T[cur].tag > 0 ? r - mid : 0;
				T[lson].tag = T[cur].tag, T[rson].tag = T[cur].tag;
				T[cur].tag = 0;
			}
		}
		int _Q(int l, int r) {
			if (ql > r || qr < l) return 0;
			if (ql <= l && r <= qr) return T[Id(l, r)].val;
			int mid = l + r >> 1;
			PushDown(l, r);
			return _Q(l, mid) + _Q(mid + 1, r);
		}
		int _U(int l, int r) {
			int cur = Id(l, r);
			if (ql > r || qr < l) return T[cur].val;
			if (ql <= l && r <= qr) {
				T[cur].tag = sign;
				return T[cur].val = sign > 0 ? r - l + 1 : 0;
			}
			int mid = l + r >> 1;
			PushDown(l, r);
			return T[cur].val = _U(l, mid) + _U(mid + 1, r);
		}
		inline int Query(int ql_, int qr_) {
			ql = ql_, qr = qr_;
			return _Q(1, n);
		}
		inline void Update(int ql_, int qr_, int sign_) {
			ql = ql_, qr = qr_, sign = sign_;
			_U(1, n);
		}
	}
	void Dfs1(int u) {
		sz[u] = 1, son[u] = -1;
		forto(u) {
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
			if (v == son[u]) continue;
			Dfs2(v, v);
		}
	}
	int Install(int sw) {
		if (smt::Query(dfn[sw], dfn[sw])) return 0;
		int ret = 0;
		for (; ~sw; sw = fa[top[sw]]) {
			ret += dep[sw] - dep[top[sw]] + 1 - smt::Query(dfn[top[sw]], dfn[sw]);
			smt::Update(dfn[top[sw]], dfn[sw], 1);
		}
		return ret;
	}
	int Uninstall(int sw) {
		if (!smt::Query(dfn[sw], dfn[sw])) return 0;
		int ret = smt::Query(dfn[sw], dfn[sw] + sz[sw] - 1);
		smt::Update(dfn[sw], dfn[sw] + sz[sw] - 1, -1);
		return ret;
	}
}
