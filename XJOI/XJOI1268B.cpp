#include <algorithm>
#include <cstdio>
#include <vector>

#define fir first
#define sec second
#define pb push_back

typedef long long LL;

const int kMaxn = 1e5 + 5, kLg = 18, kMod = 1e9 + 7;

void Solve();

int main() {
	int T;
	scanf("%d", &T);
	while (T--) Solve();
	return 0;
}

struct Edge {
	int u, v, c;
	bool operator<(const Edge & e) const {
		return c < e.c;
	}
} E[kMaxn << 1];

int n, m;
LL X;
int fa[kMaxn], dep[kMaxn], used[kMaxn << 1];
int F[kMaxn][kLg], M[kMaxn][kLg];
std::vector<std::pair<int, int> > G[kMaxn];

void Dfs(int u) {
	for (int i = 1; i < kLg && F[u][i - 1]; ++i) {
		F[u][i] = F[F[u][i - 1]][i - 1];
		M[u][i] = std::max(M[u][i - 1],
				M[F[u][i - 1]][i - 1]);
	}
	for (auto & e : G[u]) {
		int v = e.fir;
		if (v == F[u][0]) continue;
		dep[v] = dep[u] + 1; F[v][0] = u;
		M[v][0] = e.sec; Dfs(v);
	}
}

inline void AddEdge(const Edge & e) {
	G[e.u].pb({e.v, e.c}); G[e.v].pb({e.u, e.c});
}

template <typename T> inline
void UMax(T & x, const T & y) {
	if (x < y) x = y;
}

int MaxW(int u, int v) {
	if (dep[u] > dep[v]) std::swap(u, v);
	int res = 0;
	for (int i = 0, d = dep[v] - dep[u];
			(1 << i) <= d; ++i)
		if (d >> i & 1) {
			UMax(res, M[v][i]); v = F[v][i];
		}
	if (v == u) return res;
	for (int i = kLg - 1; i >= 0; --i)
		if (F[u][i] != F[v][i]) {
			UMax(res, std::max(M[u][i], M[v][i]));
			u = F[u][i], v = F[v][i];
		}
	return std::max(res, std::max(M[u][0], M[v][0]));
}

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

inline int Find(int x) { return fa[x] == x ? x : (fa[x] = Find(fa[x])); }
inline void Merge(int x, int y) { fa[Find(x)] = Find(y); }

void Solve() {
	scanf("%d%d%lld", &n, &m, &X);
	for (int i = 0; i < m; ++i)
		scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].c);
	if (n == 1) return (void)(puts(X ? "0" : "2"));
	std::sort(E, E + m);
	for (int i = 1; i <= n; ++i) {
		fa[i] = i; G[i].clear();
		for (int j = 0; j < kLg; ++j)
			F[i][j] = M[i][j] = 0;
	}
	for (int i = 0; i < m; ++i) {
		used[i] = 0;
		if (Find(E[i].u) == Find(E[i].v)) continue;
		X -= E[i].c; Merge(E[i].u, E[i].v);
		used[i] = 1; AddEdge(E[i]);
	}
	if (X < 0) return (void)(puts("0"));
	if (X) {
	//	puts(" case 1");
		dep[1] = 1; Dfs(1);
		int cnt1 = 0, cnt2 = 0;
		for (int cost, i = 0; i < m; ++i) {
			if (used[i]) continue;
			cost = MaxW(E[i].u, E[i].v);
		//	printf(" (%d, %d) %d, cost %d\n",
		//			E[i].u, E[i].v, E[i].c, cost);
			if (!(X + cost - E[i].c)) ++cnt1;
			if (X + cost - E[i].c < 0) ++cnt2;
		}
	//	printf(" cnt1 = %d, cnt2 = %d\n", cnt1, cnt2);
		printf("%d\n", Sub(FPow(2, cnt1 + cnt2 + 1), FPow(2, cnt2 + 1)));
	} else {
		for (int i = 1; i <= n; ++i) fa[i] = i;
		int la = 0, cnt = 0; E[m].c = -1;
		for (int i = 1; i <= m; ++i) {
			if (E[i].c == E[la].c) continue;
			for (int j = la; j < i; ++j)
				if (Find(E[j].u) != Find(E[j].v)) ++cnt;
			for (int j = la; j < i; ++j)
				if (Find(E[j].u) != Find(E[j].v))
					Merge(E[j].u, E[j].v);
			la = i;
		} printf("%d\n", Sub(FPow(2, m), FPow(2, m - cnt + 1)));
	}
}
