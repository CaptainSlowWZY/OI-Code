// count
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

typedef long long LL;
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

const int kMaxn = 1e5 + 5;

typedef int IAr[kMaxn];

int n, m;
LL A[kMaxn];
Vi G[kMaxn];

namespace hld {
	bool Check();
	void Modify(int u, int w);
	void Init();
}

int main() {
/*	freopen("sample/count/count4.in", "r", stdin);
	freopen("ans.out", "w", stdout);*/
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%lld", A + i);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		G[u].pb(v), G[v].pb(u);
	}
	hld::Init();
	puts(hld::Check() ? "Yes" : "No");
	scanf("%d", &m);
	for (int x, w; m--; ) {
		scanf("%d%d", &x, &w);
		hld::Modify(x, w);
		puts(hld::Check() ? "Yes" : "No");
	}
	// fclose(stdin); fclose(stdout);
	return 0;
}

struct Matrix {
	LL a[2][2];
	LL *operator[](int r) { return a[r]; }
	Matrix operator*(const Matrix & m) const {
		using std::min;
		return {min(a[0][0] + m.a[0][0], a[0][1] + m.a[1][0]), 
			min(a[0][0] + m.a[0][1], a[0][1] + m.a[1][1]),
			min(a[1][0] + m.a[0][0], a[1][1] + m.a[1][0]),
			min(a[1][0] + m.a[0][1], a[1][1] + m.a[1][1])};
	}
} B[kMaxn];

const Matrix kI = {0, 0, kInf64, 0};

namespace smt {
	Matrix T[kMaxn << 1];
#define LSON Id(l, mid)
#define RSON Id(mid + 1, r)

	inline int Id(int l, int r) { return l + r | l != r; }
	void Build(int l, int r) {
		int cur = Id(l, r);
		if (l == r) return (void)(T[cur] = B[l]);
		int mid = l + r >> 1;
		Build(l, mid); Build(mid + 1, r);
		T[cur] = T[RSON] * T[LSON];
	}
	void Modify(int l, int r, int p, const Matrix & m) {
		int cur = Id(l, r);
		if (l == r) return (void)(T[cur] = B[l] = m);
		int mid = l + r >> 1;
		if (p <= mid) Modify(l, mid, p, m);
		else Modify(mid + 1, r, p, m);
		T[cur] = T[RSON] * T[LSON];
	}
	Matrix Query(int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return T[Id(l, r)];
		int mid = l + r >> 1;
		if (qr <= mid) return Query(l, mid, ql, qr);
		if (ql > mid) return Query(mid + 1, r, ql, qr);
		return Query(mid + 1, r, ql, qr) * Query(l, mid, ql, qr);
	}
}

namespace hld {
	IAr sz, son, fa, dep, dfn, top, btm;
	int dfs_clock;

	bool Check() { return (kI * smt::Query(1, n, dfn[1], dfn[btm[1]]))[0][0] >= 0; }
	void Modify(int u, int w) {
		Matrix a, b = B[dfn[u]], c;
		for (b[0][0] += w, A[u] += w; u; ) {
			a = kI * smt::Query(1, n, dfn[top[u]], dfn[btm[u]]);
			smt::Modify(1, n, dfn[u], b);
			c = kI * smt::Query(1, n, dfn[top[u]], dfn[btm[u]]);
			if (!(u = fa[top[u]])) break;
			b = B[dfn[u]];
			b[0][0] += c[0][0] - a[0][0];
		}
	}
	void Dfs(int u) {
		sz[u] = 1, son[u] = -1;
		for (auto v : G[u]) {
			if (v == fa[u]) continue;
			fa[v] = u, dep[v] = dep[u] + 1;
			Dfs(v); sz[u] += sz[v];
			if (son[u] == -1 || sz[son[u]] < sz[v])
				son[u] = v;
		}
	}
	void Dfs(int u, int tp) {
		dfn[u] = ++dfs_clock, top[u] = tp, btm[u] = u;
		if (son[u] == -1) return;
		Dfs(son[u], tp); btm[u] = btm[son[u]];
		for (auto v : G[u]) {
			if (v == fa[u] || v == son[u])
				continue;
			Dfs(v, v);
		}
	}
	LL Dp(int u) {
		LL f = A[u], sf = 0;
		for (auto v : G[u]) {
			if (v == fa[u]) continue;
			if (v == son[u]) sf = Dp(v);
			else f += Dp(v);
		}
		B[dfn[u]] = {f, kInf64, 0, 0};
		return std::min(0ll, sf + f);
	}
	void Init() {
		dep[1] = 1; Dfs(1); Dfs(1, 1); Dp(1);
		smt::Build(1, n);
	}
}