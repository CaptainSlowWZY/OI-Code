// robot
#include <algorithm>
#include <cassert>
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

const int kMaxn = 2e5 + 5, kMaxm = kMaxn << 1;

typedef int IAr[kMaxm];

int n, m, top, findcr, nos;
Vi G[kMaxm], DT[kMaxm], T[kMaxm], cir, gt;
IAr crw, vis, S, in, ideg, sz, onlp;

int Dfs(int u);
void Dfs(int u, int fa);
void SCir(int u, int fa);

int main() {
	scanf("%d", &n);
	m = n << 1;
	for (int i = 0, xi, yi; i < m; i++) {
		scanf("%d%d", &xi, &yi);
		G[xi].pb(n + yi); G[n + yi].pb(xi);
	}
	int ans = 1;
	memset(crw, 0xff, sizeof crw);	// crw - circle way
	for (int i = 1; i <= m; i++) {
		if (vis[i]) continue;
		cir.clear(), gt.clear(), top = 0;
		SCir(i, findcr = nos = 0);
		// printf(" findcr = %d, nos = %d\n", findcr, nos);
		if (!findcr || nos) { puts("0"); return 0; }
		for (auto u : cir) Dfs(u, 0);
		// printf(" i = %d\n", i);
		// direction 1
		// assert(SZ(cir) > 1);
		for (int j = 1; j < SZ(cir); j++)
			in[crw[cir[j]] = cir[j - 1]] = cir[j];
		//	cir[j] -> cir[j - 1]
		in[crw[cir[0]] = *cir.rbegin()] = cir[0];
		for (auto u : gt) {
			if (SZ(DT[u])) {
				std::sort(DT[u].begin(), DT[u].end());
				auto lim = UB(DT[u], in[u]);
				for (auto it = DT[u].begin(); it != lim; ++it) {
					T[u].pb(*it); ++ideg[*it];
				}
			}
			if (~crw[u] && crw[u] < in[u]) {
				T[u].pb(crw[u]); ++ideg[crw[u]];
			}
		}
		int frac1 = 1;
		for (auto u : gt) {
			if (ideg[u]) continue;
			// printf("  subtree %d\n", u);
			frac1 = Mul(frac1, Dfs(u));
		}
		// direction 2
		for (int j = 1; j < SZ(cir); j++)
			in[crw[cir[j - 1]] = cir[j]] = cir[j - 1];
		in[crw[*cir.rbegin()] = cir[0]] = *cir.rbegin();
		for (auto u : gt) { ideg[u] = 0; T[u].clear(); }
		for (auto u : gt) {
			if (SZ(DT[u])) {
				auto lim = UB(DT[u], in[u]); 
				for (auto it = DT[u].begin(); it != lim; ++it) {
					T[u].pb(*it); ++ideg[*it];
				}
			}
			if (~crw[u] && crw[u] < in[u]) {
				T[u].pb(crw[u]); ++ideg[crw[u]];
			}
		}
		int frac2 = 1;
		for (auto u : gt) {
			if (ideg[u]) continue;
			frac2 = Mul(frac2, Dfs(u));
		}
		ans = Mul(ans, Add(FPow(frac1), FPow(frac2)));
	}
	printf("%d\n", ans);
	return 0;
}

int Dfs(int u) {
	sz[u] = 1;
	int res = 1;
	for (auto v : T[u]) {
		res = Mul(res, Dfs(v));
		sz[u] += sz[v];
	} return Mul(res, sz[u]);
}

void Dfs(int u, int fa) {
	// printf(" Dfs side trees %d, fa %d\n", u, fa);
	vis[u] = 1; gt.pb(u);
	for (auto v : G[u]) {
		if (v == fa || onlp[v]) continue;
		DT[u].pb(v); in[v] = u; Dfs(v, u);
	}
}

void SCir(int u, int fa) {
	// printf(" Search for Loop at %d, fa %d\n", u, fa);
	vis[u] = 1, S[top++] = u;
	for (auto v : G[u]) {
		if (v == fa) continue;
		if (vis[v] && !onlp[v]) {	// find it!
			// printf(" u = %d, v = %d\n", u, v);
			if (findcr) { nos = 1; return; }
			while (top > 0 && S[top - 1] != v) {
				onlp[S[top - 1]] = 1; cir.pb(S[--top]);
			} onlp[v] = 1, cir.pb(v); if (top > 0) --top;
			findcr = 1;
			return;
		}
		if (!vis[v]) SCir(v, u);
		// if (findcr) return;
	} if (top > 0 && S[top - 1] == u) --top;
}