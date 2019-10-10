#pragma GCC optimize("2,Ofast,inline")
#include <algorithm>
// #include <cassert>
#include <cctype>
// #include <cmath>
#include <cstdio>
// #include <cstdlib>
#include <cstring>
// #include <ctime>
#include <map>
#include <queue>
#include <set>
#include <vector>

#define fir first
#define sec second
#define pb push_back
#define pch putchar
#define rg register
#define SZ(_) (int)_.size()
#define SORT(_) std::sort(_.begin(), _.end())
#define LB(_, __) std::lower_bound(_.begin(), _.end(), __)
#define UB(_, __) std::upper_bound(_.begin(), _.end(), __)
#define FORTO(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].nxt].to)
#define LSON Id(l, mid)
#define RSON Id(mid + 1, r)

typedef long long LL;
typedef double DB;
typedef std::pair<DB, DB> Pdd;
typedef std::pair<int, int> Pii;
typedef std::pair<LL, int> Pli;
typedef std::pair<int, LL> Pil;
typedef std::pair<LL, LL> Pll;
typedef std::vector<int> Vi;
typedef std::vector<LL> Vl;
typedef std::map<int, int> Mii;
typedef std::map<LL, int> Mli;
typedef std::map<int, LL> Mil;
typedef std::map<LL, LL> Mll;
typedef std::set<int> Si;
typedef std::set<LL> Sl;

const int kInf = 0x3f3f3f3f, kMod = 1e9 + 7;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;
// const double kPie = acos(-1), kEps = 1e-9;

template <typename T> inline
void UMin(T & x, const T & y) { if (x > y) x = y; }
template <typename T> inline
void UMax(T & x, const T & y) { if (x < y) x = y; }
inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

const int kMaxn = 1e5 + 5, kLg = 18;

typedef int IAr[kMaxn];

struct Edge { int to, w, nxt; } E[kMaxn << 1];
struct Pair { int u, v; LL d; };

int n, m, cnte, el, dfs_clock;
IAr U, V, W, dep, idfn, odfn, pos, back, fa, nd;
int lg2[kMaxn << 2], pw[kLg];
int st[kLg][kMaxn << 2];

namespace bit {
	LL T[kMaxn];
	void Add(int p, int d) { for (; p <= n + 1; p += p & -p) T[p] += d; }
	inline void Add(int l, int r, int d) { Add(l, d); Add(r + 1, -d); }
	LL Sum(int p) {
		LL res = 0; for (; p; p &= p - 1) res += T[p]; return res;
	}
}
namespace smt {
	void Build(int l, int r);
	void Modify(int l, int r, int ql, int qr);
	Pair Query(int l, int r, int ql, int qr);
}
inline int Id(int l, int r) { return l + r | l != r; }
inline LL Dep(int u) { return bit::Sum(idfn[u]); }
inline int Higher(int u, int v) {
	return dep[u] > dep[v] ? v : u;
}
inline int Lca(int u, int v) {
	u = pos[u], v = pos[v];
	if (u > v) std::swap(u, v);
	int k = lg2[v - u + 1];
	int l = Higher(st[k][u], st[k][v - pw[k] + 1]);
	return l;
}
inline LL Dist(const Pii & p) {
	return Dep(p.fir) + Dep(p.sec) - (Dep(Lca(p.fir, p.sec)) << 1);
}
inline void AddEdge(int u, int v, int c) {
	E[++cnte] = {v, c, back[u]}; back[u] = cnte;
	E[++cnte] = {u, c, back[v]}; back[v] = cnte;
}
void Dfs(int);
Pair Compose(const Pair & a, const Pair & b, int md = 1);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; ++i) {
		scanf("%d%d%d", U + i, V + i, W + i);
		AddEdge(U[i], V[i], W[i]);
	}
	dep[1] = 1; Dfs(1);
	lg2[0] = -1;
	for (int i = 1; i <= el; ++i) {
		lg2[i] = lg2[i >> 1] + 1;
	}
	for (int i = pw[0] = 1; i < kLg; ++i) pw[i] = pw[i - 1] << 1;
	for (int i = 1; i < kLg; ++i) {
		for (int j = 1; j + pw[i] - 1 <= el; ++j) {
			st[i][j] = Higher(st[i - 1][j], st[i - 1][j + pw[i - 1]]);
		}
	}
	smt::Build(1, n);
	for (int o, x, y, z; m--; ) {
		scanf("%d", &o);
		if (o == 1) {
			scanf("%d%d", &x, &y);
			if (fa[V[x]] != U[x]) std::swap(U[x], V[x]);
			bit::Add(idfn[V[x]], odfn[V[x]], y - W[x]);
			W[x] = y; smt::Modify(1, n, idfn[V[x]], odfn[V[x]]);
		}
		if (o == 2) {
			scanf("%d%d", &x, &y);
			printf("%lld\n", Compose(smt::Query(1, n, idfn[x], odfn[x]),
				smt::Query(1, n, idfn[y], odfn[y]), 0).d);
		}
		if (o == 3) {
			scanf("%d%d%d", &x, &y, &z);
			printf("%lld\n", Compose(smt::Query(1, n, idfn[x], odfn[x]),
				{y, z, 0}, 0).d);
		}
	}
	return 0;
}

Pair Compose(const Pair & a, const Pair & b, int md) {
	Pair res = {a.u, b.u, Dist({a.u, b.u})};
	LL d;
	if (b.u != b.v && (d = Dist({a.u, b.v})) > res.d)
		res = {a.u, b.v, d};
	if (a.u != a.v) {
		if ((d = Dist({a.v, b.u})) > res.d)
			res = {a.v, b.u, d};
		if (b.u != b.v && (d = Dist({a.v, b.v})) > res.d)
			res = {a.v, b.v, d};
	}
	if (md && a.d > res.d) res = a;
	if (md && b.d > res.d) res = b; 
/*	Pair res = {a.u, b.u, 0};
	if (Dist({a.u, b.v, 0}) > Dist(res))
		res = {a.u, b.v, 0};
	if (Dist({a.v, b.u,0 }) > Dist(res))
		res = {a.v, b.u,0};
	if (Dist({a.v, b.v,0}) > Dist(res))
		res = {a.v, b.v,0};
	if (md && Dist(a) > Dist(res)) res = a;
	if (md && Dist(b) > Dist(res)) res = b;
	res.d = Dist(res); */
	return res;
}

namespace smt {
	Pair T[kMaxn << 1];

	void Build(int l, int r) {
		int cur = Id(l, r);
		if (l == r) {
			T[cur] = {nd[l], nd[l], 0};
			return;
		} int mid = l + r >> 1;
		Build(l, mid); Build(mid + 1, r);
		T[cur] = Compose(T[LSON], T[RSON]);
	}
	void Modify(int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return;
		int mid = l + r >> 1;
		if (ql <= mid) Modify(l, mid, ql, qr);
		if (qr > mid) Modify(mid + 1, r, ql, qr);
		T[Id(l, r)] = Compose(T[LSON], T[RSON]);
	}
	Pair Query(int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return T[Id(l, r)];
		int mid = l + r >> 1;
		if (qr <= mid) return Query(l, mid, ql, qr);
		if (ql > mid) return Query(mid + 1, r, ql, qr);
		return Compose(Query(l, mid, ql, qr), Query(mid + 1, r, ql, qr));
	}
}

void Dfs(int u) {
	nd[idfn[u] = ++dfs_clock] = u, st[0][pos[u] = ++el] = u;
	FORTO(u) {
		if (v == fa[u]) continue;
		dep[v] = dep[u] + 1; fa[v] = u; Dfs(v); st[0][++el] = u;
		bit::Add(idfn[v], odfn[v], E[e].w);
	} odfn[u] = dfs_clock;
}
