#include <algorithm>
#include <cstdio>
#include <vector>

#define fi first
#define se second
#define pb push_back
#define FORV(I, _) for (std::vector<int>::iterator I = _.begin(); I != _.end(); ++I)

const int kMaxn = 1e5 + 5;

typedef int Arr[kMaxn];
typedef std::pair<int, int> Pii;

int n, totw, q;
Arr mw, W, sz, son;
int ans[kMaxn * 3];
std::vector<int> G[kMaxn];
std::vector<Pii> Q[kMaxn];

void Dfs1(int u, int fa);
void Dfs2(int u, int fa, int f);

int main() {
#ifndef LOCAL
	freopen("data.in", "r", stdin);
	freopen("data.out", "w", stdout);
#endif
//	using fast_io::Read;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) { scanf("%d", W + i); mw[i] = W[i]; }
	std::sort(mw + 1, mw + (totw = n) + 1); totw = std::unique(mw + 1, mw + totw + 1) - mw - 1;
	for (int i = 1, x, y; i < n; ++i) { scanf("%d%d", &x, &y); G[x].pb(y); G[y].pb(x); }
	scanf("%d", &q);
	for (int i = 0, x, k; i < q; ++i) { scanf("%d%d", &x, &k); Q[x].pb(Pii(k, i)); }
	Dfs1(1, 0); Dfs2(1, 0, 1);
	for (int i = 0; i < q; ++i) printf("%d\n", ans[i]);
#ifndef LOCAL
	fclose(stdin); fclose(stdout);
#endif
	return 0;
}

inline int Index(int x) { return std::lower_bound(mw + 1, mw + totw + 1, x) - mw; }

namespace smt {
	int T[kMaxn << 1];

	inline int Id(int l, int r) { return l + r | l != r; }
#define LSON Id(l, mid)
#define RSON Id(mid + 1, r)
	void Modify(int l, int r, int p, int v) {
		if (l == r) return (void)(T[Id(l, r)] += v);
		int mid = l + r >> 1;
		if (p <= mid) Modify(l, mid, p, v); else Modify(mid + 1, r, p, v);
		T[Id(l, r)] = T[LSON] + T[RSON];
	}
	int Query(int l, int r, int k) {
		if (l == r) return l;
		int mid = l + r >> 1;
		if (T[LSON] >= k) return Query(l, mid, k);
		else return Query(mid + 1, r, k - T[LSON]);
	}
}

void Dfs1(int u, int fa) {
	sz[u] = 1, son[u] = -1;
	FORV(v, G[u]) if (*v != fa) {
		Dfs1(*v, u);
		if (son[u] == -1 || sz[*v] > sz[son[u]]) son[u] = *v;
	}
}

void Add(int u, int fa, int f) {
	smt::Modify(1, totw, Index(W[u]), f);
	FORV(v, G[u]) if (*v != fa) Add(*v, u, f);
}

void Dfs2(int u, int fa, int f) {
	FORV(v, G[u]) if (*v != fa && *v != son[u]) Dfs2(*v, u, 0);
	if (son[u] == -1) {
		for (std::vector<Pii>::iterator it = Q[u].begin(); it != Q[u].end(); ++it) ans[it->se] = W[u];
		if (f) smt::Modify(1, totw, Index(W[u]), 1);
		return;
	} Dfs2(son[u], u, 1);
	smt::Modify(1, totw, Index(W[u]), 1);
	FORV(v, G[u]) if (*v != fa && *v != son[u]) Add(*v, u, 1);
	for (std::vector<Pii>::iterator it = Q[u].begin(); it != Q[u].end(); ++it)
		ans[it->se] = mw[smt::Query(1, totw, it->fi)];
	if (!f) Add(u, fa, -1);
}
