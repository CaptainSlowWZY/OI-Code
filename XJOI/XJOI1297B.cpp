#include <cassert>
#include <cstdio>
#include <map>
#include <vector>

#define pb push_back
#define SZ(_) (int)_.size()

typedef std::vector<int> Vi;

const int kMaxn = 75, kMod = 1e9 + 7;

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

int n, m, S[kMaxn], G[kMaxn][kMaxn][kMaxn];

inline void Add(int k, int u, int v, int d) { Upa(G[k][u][v], d); }

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", S + i);
		Add(0, i - 1, i, 1);
	} Add(0, n, n + 1, 1);
	for (int i = 1; i <= m; ++i) {
		for (int j = n; ~j; --j) {
			for (int k = j + 1; k <= n + 1; ++k) {
				Add(i, j, k, G[i - 1][j][k]);
				for (int t = j + 1; t < k; ++t) if (S[t] ^ S[k]) Add(i, j, k, Mul(G[i - 1][j][t], G[i][t][k]));
			}
		}
	} printf("%d\n", G[m][0][n + 1]); return 0;
}
