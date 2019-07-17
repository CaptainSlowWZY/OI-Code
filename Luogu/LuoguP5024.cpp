#include <algorithm>
#include <cstdio>

#define forto(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)

using std::max;

const int kMaxn = 1e5 + 10, kInf = 0x3f3f3f3f;

typedef int IAr[kMaxn];
typedef long long LL;

const LL kInf64 = 0x3f3f3f3f3f3f3f3f;

struct Edge {
	int to, next;
} E[kMaxn << 1];

int n, m, tote;
LL F[kMaxn][2];
IAr V, back;

namespace hld {
	void Init();
	void Modify(int u, int val);
	LL Result();
}
inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, back[v]}, back[v] = tote;
}

int main() {
	scanf("%d%d%*s", &n, &m);
	LL sumv = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", V + i);
		F[i][1] = V[i];
		sumv += V[i];
	}
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		AddEdge(u, v);
	}

	hld::Init();
	
	for (int a, x, b, y; m--; ) {	
		scanf("%d%d%d%d", &a, &x, &b, &y);
		if (!(x + y)) {
			int f = 0;
			forto(a) {
				if (v == b) {
					puts("-1"); f = 1; break;
				}
			}
			if (f) continue;
		}
		int va0 = V[a], vb0 = V[b],
			va = x ? -kInf : kInf, vb = y ? -kInf : kInf;
		using namespace hld;
		Modify(a, va); Modify(b, vb);
		LL res = Result() - (x ? 0 : kInf - va0) - (y ? 0 : kInf - vb0);
		printf("%lld\n", sumv - res);
		Modify(a, va0); Modify(b, vb0);
	}

	return 0;
}

struct Matrix {
	LL a[2][2];
#define ar(_) LL _ = 0
	Matrix(ar(a00), ar(a01), ar(a10), ar(a11)) {
		a[0][0] = a00, a[0][1] = a01, a[1][0] = a10, a[1][1] = a11;
	}
#undef ar
	LL *operator[](int x) { return a[x]; }
	Matrix operator*(const Matrix & m) const {
		Matrix res;
		res[0][0] = max(a[0][0] + m.a[0][0], a[0][1] + m.a[1][0]);
		res[0][1] = max(a[0][0] + m.a[0][1], a[0][1] + m.a[1][1]);
		res[1][0] = max(a[1][0] + m.a[0][0], a[1][1] + m.a[1][0]);
		res[1][1] = max(a[1][0] + m.a[0][1], a[1][1] + m.a[1][1]);
		return res;
	}
} A[kMaxn];

namespace smt {
	Matrix T[kMaxn << 1];

	inline int Id(int l, int r) {
		return l + r | l != r;
	}
	const Matrix & Build(int l, int r) {
		int cur = Id(l, r);
		if (l == r) return T[cur] = A[l];
		int mid = l + r >> 1;
		return T[cur] = Build(l, mid) * Build(mid + 1, r);
	}
	void Modify(int l, int r, int p, const Matrix & m) {
		int cur = Id(l, r);
		if (l == r) return (void)(T[cur] = A[l] = m);
		int mid = l + r >> 1;
		if (p <= mid) Modify(l, mid, p, m);
		else Modify(mid + 1, r, p, m);
		T[cur] = T[Id(l, mid)] * T[Id(mid + 1, r)];
	}
	Matrix Query(int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return T[Id(l, r)];
		int mid = l + r >> 1;	
		if (qr <= mid) return Query(l, mid, ql, qr);
		if (ql > mid) return Query(mid + 1, r, ql, qr);
		return Query(l, mid, ql, qr) * Query(mid + 1, r, ql, qr);
	}
}

namespace hld {
	IAr dfn, sz, son, fa, top, btm, dep;

	LL Result() {
		Matrix m = smt::Query(1, n, dfn[top[1]], dfn[btm[1]]);
		return max(m[0][0], m[1][0]);
	}
	void Modify(int u, int val) {
		Matrix m = A[dfn[u]], a, b;
		m[1][0] += val - V[u], V[u] = val;
		while (u) {
			a = smt::Query(1, n, dfn[top[u]], dfn[btm[u]]);
			smt::Modify(1, n, dfn[u], m);
			b = smt::Query(1, n, dfn[top[u]], dfn[btm[u]]);
			if (!(u = fa[top[u]])) return;
			m = A[dfn[u]];
			m[0][0] = m[0][1] = m[0][0] 
				- max(a[0][0], a[1][0]) + max(b[0][0], b[1][0]);
			m[1][0] += b[0][0] - a[0][0];
		}
	}
	void Dfs(int u) {
		sz[u] = 1, son[u] = -1;
		forto(u) {
			if (v == fa[u]) continue;
			dep[v] = dep[u] + 1, fa[v] = u;
			Dfs(v);
			if (son[u] == -1 || sz[v] > sz[son[u]]) son[u] = v;
			sz[u] += sz[v];
		}
	}
	void Dfs(int u, int tp) {
		static int dfs_clock = 0;
		dfn[u] = ++dfs_clock, top[u] = tp, btm[u] = u;
		if (son[u] == -1) return;
		Dfs(son[u], tp); btm[u] = btm[son[u]];
		forto(u) {
			if (v == fa[u] || v == son[u]) continue;
			Dfs(v, v);
		}
	}
	void Dp(int u) {
		LL g0 = 0, g1 = V[u];
		forto(u) {
			if (v == fa[u]) continue;
			Dp(v);
			F[u][0] += max(F[v][0], F[v][1]), F[u][1] += F[v][0];
			if (v != son[u]) {
				g0 += max(F[v][0], F[v][1]), g1 += F[v][0];
			}
		}
		A[dfn[u]] = Matrix(g0, g0, g1, -kInf64);
	}
	void Init() {
		dep[1] = 1;
		Dfs(1); Dfs(1, 1); Dp(1);
		smt::Build(1, n);
	}
}
