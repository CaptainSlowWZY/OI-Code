#include <cstdio>
#include <vector>

#define pb push_back
#define SZ(_) (int)_.size()
#define FORV(I, _) for (std::vector<int>::iterator I = _.begin(); I != _.end(); ++I)

const int kMaxn = 20, kU = 1 << 18, kMod = 998244353;

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

int n, q, x, U;
int F[kMaxn], A[kMaxn], B[kMaxn], mt[kU];
std::vector<int> G[kMaxn];

void Dfs(int, int, int);
void Calc(int, int);

int main() {
	scanf("%d%d%d", &n, &q, &x); U = 1 << n, --x;
	for (int i = 1, x, y; i < n; ++i) { scanf("%d%d", &x, &y); G[--x].pb(--y); G[y].pb(x); }
	for (int m = 1; m < U; ++m) for (int i = 0; i < n; ++i) if (m >> i & 1) {
		Dfs(i, -1, m); F[i] = 0; Calc(i, -1); mt[m] = __builtin_popcount(m) & 1 ? F[x] : Sub(kMod, F[x]); break;
	}
	for (int i = 0; i < n; ++i) for (int j = 0; j < U; ++j) if (j >> i & 1) Upa(mt[j], mt[j ^ 1 << i]);
	for (int k, m; q--; ) {
		scanf("%d", &k); m = 0;
		for (int u; k--; ) { scanf("%d", &u); m |= 1 << u - 1; }
		printf("%d\n", mt[m]);
	} return 0;
}

void Dfs(int u, int fa, int m) {
	A[u] = B[u] = 0;
	FORV(v, G[u]) if (*v != fa) { Dfs(*v, u, m); Upa(A[u], A[*v]); Upa(B[u], B[*v]); }
	if (m >> u & 1) A[u] = B[u] = 0; else { A[u] = FPow(Sub(SZ(G[u]), A[u])); B[u] = Mul(Add(SZ(G[u]), B[u]), A[u]); }
}

void Calc(int u, int fa) {
	FORV(v, G[u]) if (*v != fa) { F[*v] = Add(Mul(F[u], A[*v]), B[*v]); Calc(*v, u); }
}
