#include <algorithm>
// #include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>
// #include <cmath>
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
#define FORTO(e, v, u) for (int e = back[u], v = E[e].to; \
		e; v = E[e = E[e].next].to)

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

const int kMaxn = 2e5 + 5;

struct Edge { int to, cut, next; } E[kMaxn << 1];

typedef int IAr[kMaxn];

int n, m, s, cnte = 1, ebc, dfs_clock;
IAr back, dfn, low, conc, col, W, size;
LL val[kMaxn], ans, R[kMaxn], B[kMaxn];
Vi G[kMaxn];

inline void AddEdge(int u, int v) {
	E[++cnte] = {v, 0, back[u]}, back[u] = cnte;
	E[++cnte] = {u, 0, back[v]}, back[v] = cnte;
}
void Dfs(int u, int fa);
void Dfs2(int u, int fa);
void Tarjan(int u, int fa);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", W + i);
	for (int u, v; m--; ) {
		scanf("%d%d", &u, &v);
		AddEdge(u, v);
	} scanf("%d", &s);
	Tarjan(s, 0);
	for (int i = 1; i <= n; i++) {
		if (!conc[i] || col[i]) continue;
		++ebc; Dfs(i, 0);
	}
	for (int i = 1; i <= n; i++) {
	//	printf(" col[%d] = %d\n", i, col[i]);
		if (!conc[i]) continue;
		FORTO(e, v, i) {
			if (E[e].cut) {
				G[col[v]].pb(col[i]);
				G[col[i]].pb(col[v]);
			}
		}
	}
	for (int i = 1; i <= ebc; i++) {
	//	printf(" val[%d] = %lld\n", i, val[i]);
		std::sort(G[i].begin(), G[i].end());
		G[i].erase(std::unique(G[i].begin(), G[i].end()),
			G[i].end());
	}
	Dfs2(col[s], 0);
	printf("%lld\n", std::max(R[col[s]], B[col[s]]));
	return 0;
}

void Dfs2(int u, int fa) {
	LL vre = 0, vnb = -kInf64, sz0 = size[u];
	for (auto v : G[u]) {
		if (v == fa) continue;
		Dfs2(v, u);
		UMax(size[u], size[v]); vre += R[v];
	} 
	for (auto v : G[u]) {
		if (v == fa) continue;
		UMax(vnb, vre - R[v] + B[v] + val[u]);
	}
	if (sz0 == 1) UMax(vnb, val[u]);
	R[u] = size[u] > 1 ? vre + val[u] : 0;
	B[u] = vnb;
}

void Tarjan(int u, int fa) {
	conc[u] = 1, dfn[u] = low[u] = ++dfs_clock;
	FORTO(e, v, u) {
		if (v == fa) continue;
		if (!dfn[v]) {
			Tarjan(v, u);
			if (low[v] > dfn[u]) {
				E[e].cut = E[e ^ 1].cut = 1;
			} UMin(low[u], low[v]);
		} else UMin(low[u], dfn[v]);
	}
}

void Dfs(int u, int fa) {
	col[u] = ebc, val[ebc] += W[u], ++size[ebc];
	FORTO(e, v, u) {
		if (v == fa || E[e].cut || col[v]) continue;
		Dfs(v, u);
	}
}
