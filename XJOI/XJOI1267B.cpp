#include <algorithm>
#include <cstdio>
#include <vector>

#define fir first
#define sec second
#define pb push_back

const int kMaxn = 2e5 + 5, kInf = 0x3f3f3f3f;

typedef long long LL;
typedef std::pair<LL, LL> Pll;
typedef std::vector<int> Vi;
typedef int IAr[kMaxn];

int n, m, q, top;
IAr A, id, fa, sz, vis;
Pll S[kMaxn];
Vi G[kMaxn];
std::vector<Pll> L;
std::vector<double> P;

inline bool CmpA(int a, int b) {
	return A[a] > A[b];
}
inline int Find(int x) {
	return fa[x] == x ? x : (fa[x] = Find(fa[x]));
}
inline void Merge(int x, int y) {
	x = Find(x), y = Find(y);
	if (x == y) return;
	fa[x] = y, sz[y] += sz[x];
}
inline double Inter(const Pll & a, const Pll & b) {
	return (double)(b.sec - a.sec) / (a.fir - b.fir);
}

int main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", A + i); id[i - 1] = i; 
		fa[i] = i, sz[i] = 1;
	}
	for (int i = 0, u, v; i < m; ++i) {
		scanf("%d%d", &u, &v);
		G[u].pb(v); G[v].pb(u);
	}
	std::sort(id, id + n, CmpA);
	int la = 0;
	A[id[n] = n + 1] = kInf, vis[id[0]] = 1;
	for (int i = 1, u; i <= n; ++i) {
		if (A[u = id[i]] != A[id[la]]) {
		//	printf(" i = %d\n", i);
			for (int j = la, nj; j < i; ++j) {
				nj = sz[Find(u = id[j])];
			//	printf("  %d %dx + %lld and %dx + %d\n",
			//			u, nj, 1ll * nj * A[u], 1, A[u]);
				L.pb({nj, 1ll * nj * A[u]});
				L.pb({1, A[u]});
			} la = i;
		}
		for (auto v : G[u = id[i]]) {
			if (vis[v]) Merge(u, v);
		} vis[u] = 1;
	} std::sort(L.begin(), L.end());
	L.erase(std::unique(L.begin(), L.end()), L.end());
	for (auto & l : L) {
		if (top && S[top - 1].fir == l.fir &&
			S[top - 1].sec >= l.sec) continue;
	//	printf(" insert %lldx + %lld\n", l.fir, l.sec);
		while (top && S[top - 1].fir == l.fir &&
			S[top - 1].sec < l.sec) --top;
		while (top > 1 && Inter(S[top - 1], l) <=
			Inter(S[top - 1], S[top - 2])) --top;
		S[top++] = l;
	}
//	for (int i = 0; i < top; ++i) printf(" %lldx + %lld\n", S[i].fir, S[i].sec);
	P.pb(-1e12);
	for (int i = 1; i < top; ++i)
		P.pb(Inter(S[i - 1], S[i]));
	P.pb(1e12);
	for (int k, b; q--; ) {
		scanf("%d", &b);
		k = std::lower_bound(P.begin(), P.end(),
			b) - P.begin() - 1;
		printf("%lld\n", b * S[k].fir + S[k].sec);
	} return 0;
}
