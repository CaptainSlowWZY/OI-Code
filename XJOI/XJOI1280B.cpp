#include <cstdio>
#include <iostream>
#include <vector>

#define pb push_back

const int kMaxn = 4e5 + 5, kMod = 998244353;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upa(int & a, int b) { a = Add(a, b); }
inline void Ups(int & a, int b) { a = Sub(a, b); }
inline void Upm(int & a, int b) { a = Mul(a, b); }

int n, ans;
int pool[kMaxn << 3], *pit = pool;
int *F[kMaxn], *G[kMaxn], *H[kMaxn];
int son[kMaxn], len[kMaxn];
std::vector<int> E[kMaxn];

template <typename T> inline
void UMax(T & x, const T & y) { if (x < y) x = y; }
inline void Ass(int u) {
	F[u] = pit, pit += len[u] + 1 << 1;
	H[u] = pit; pit += len[u] + 2;
	G[u] = pit, pit += len[u] + 2;
}
void Dfs1(int, int);
void Dfs2(int, int);

int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v); E[u].pb(v); E[v].pb(u);
	} Dfs1(1, 0); Ass(1); Dfs2(1, 0); printf("%d\n", ans);
	return 0;
}

void Dfs2(int u, int fa) {
	if (~son[u]) {
		F[son[u]] = F[u] + 1, G[son[u]] = G[u];
		H[son[u]] = H[u] - 1; Dfs2(son[u], u);
	} F[u][0] = 1;
	using namespace std;
	int *mxf = F[u], *mxh =H[u], *mxg = G[u];
	for (auto v : E[u]) if (v != fa && v != son[u]) {
		Ass(v); Dfs2(v, u);
		for (int i = 1; i <= len[v] + 1; ++i) {
			Upa(ans, Mul(H[u][i], F[v][i - 1]));
			Upa(ans, Mul(G[u][i], G[v][i]));
			Upa(ans, Mul(F[u][i], H[v][i + 1]));
			Upa(H[u][i], H[v][i + 1]);
			Upa(H[u][i], Mul(G[u][i], F[v][i - 1]));
			Upa(H[u][i], Mul(F[u][i], G[v][i]));
			Upa(G[u][i], Add(G[v][i], Mul(F[u][i], F[v][i - 1])));
			Upa(F[u][i], F[v][i - 1]);
			if (F[u] + i > mxf) mxf = F[u] + i;
			if (G[u] + i > mxg) mxg = G[u] + i;
			if (H[u] + i > mxh) mxh = H[u] + i;
		} Upa(H[u][0], H[v][1]);
	} Upa(ans, H[u][0]);
}

void Dfs1(int u, int fa) {
	son[u] = -1;
	for (auto v : E[u]) if (v != fa) {
		Dfs1(v, u); UMax(len[u], len[v] + 1);
		if (son[u] == -1 || len[son[u]] < len[v]) son[u] = v;
	}
}
