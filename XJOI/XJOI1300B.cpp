#include <algorithm>
#include <cstdio>
#include <vector>

#define pb push_back
#define FORV(I, _) for (std::vector<int>::iterator I = _.begin(); I != _.end(); ++I)

const int kMaxn = 1005, kMod = 998244353;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upa(int & a, int b) { a = Add(a, b); }
inline void Ups(int & a, int b) { a = Sub(a, b); }
inline void Upm(int & a, int b) { a = Mul(a, b); }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

int n;
int sz[kMaxn], F[kMaxn][kMaxn][3];
std::vector<int> G[kMaxn];

void Dfs(int, int);

int main() {
#ifndef ACLY
	freopen("paint.in", "r", stdin);
	freopen("paint.out", "w", stdout);
#endif
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v); G[u].pb(v); G[v].pb(u);
	} Dfs(1, 0);
	int ans = 0;
	for (int s, i = 1; i <= n; ++i) {
		for (int j = s = 0; j < 3; ++j) Upa(s, F[1][i][j]);
		Upa(ans, Mul(FPow(i), s));
	} Upm(ans, n); Upm(ans, Sub(kMod, 1));
	printf("%d\n", ans);
#ifndef ACLY
	fclose(stdin); fclose(stdout); 
#endif
	return 0;
}

void Dfs(int u, int fa) {
	static int nxt[kMaxn][3];
	sz[u] = F[u][0][0] = 1, F[u][1][2] = Sub(kMod, 1);
	FORV(v, G[u]) if (*v != fa) {
		Dfs(*v, u);
		for (int i = 0; i <= sz[u] + sz[*v]; ++i) for (int j = 0; j < 3; ++j) nxt[i][j] = 0;
		for (int i = 0; i <= sz[u]; ++i) for (int j = 0; j <= sz[*v]; ++j)
			for (int a = 0; a < 3; ++a) for (int b = 0; b < 3; ++b)
				Upa(nxt[i + j + (!a && b == 2) + (!b && a == 2)][a + (!a && b == 2)], Mul(F[u][i][a], F[*v][j][b]));
		sz[u] += sz[*v];
		for (int i = 0; i <= sz[u]; ++i) for (int j = 0; j < 3; ++j) F[u][i][j] = nxt[i][j];
	}
}
