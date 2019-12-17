#include <algorithm>
#include <cstdio>

const int kMaxn = 105, kMod = 1e9 + 7;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upa(int & a, int b) { a = Add(a, b); }
inline void Upm(int & a, int b) { a = Mul(a, b); }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; Upm(bs, bs), ex >>= 1) if (ex & 1) Upm(res, bs);
	return res;
}

int n, m, k;
int U[kMaxn], R[kMaxn], F[2][kMaxn], C[kMaxn][kMaxn];

int Calc(int r, int u);

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < m; ++i) scanf("%d", U + i);
	for (int i = 0; i < m; ++i) scanf("%d", R + i);
	for (int i = C[0][0] = 1; i <= n; ++i) for (int j = C[i][0] = 1; j <= i; ++j) C[i][j] = Add(C[i - 1][j - 1], C[i - 1][j]);
	int *prv = F[0], *nxt = F[1];
	prv[n - 1] = 1;
	for (int i = 0; i < m; ++i) {
		int way = Calc(R[i], U[i]);
//		printf(" way = %d\n", way);
		for (int j = k; j < n; ++j) {
			nxt[j] = 0;
			for (int t = j; t < n; ++t) if (R[i] - 1 - t + j >= 0)
				Upa(nxt[j], Mul(prv[t], Mul(C[t][j], C[n - 1 - t][R[i] - 1 - t + j])));
			Upm(nxt[j], way);
		} std::swap(nxt, prv);
	} printf("%d\n", prv[k]);
	return 0;
}

int Calc(int r, int u) {
	int res = 0;
	for (int y, f1, f2, i = 1; i <= n + 1; ++i) {
		y = 0, f1 = f2 = 1;
		for (int j = 1; j <= i; ++j) Upa(y, Mul(FPow(j, n - r), FPow(Sub(i, j), r - 1)));
		for (int j = 1; j <= n + 1; ++j) if (j != i) { Upm(f1, Sub(u, j)), Upm(f2, Sub(i, j)); }
		Upa(res, Mul(y, Mul(f1, FPow(f2))));
	} return res;
}
