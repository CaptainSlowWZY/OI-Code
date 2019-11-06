#include <algorithm>
#include <cstdio>

const int kMaxn = 405, kMod = 998244353;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upa(int & a, int b) { a = Add(a, b); }

int n, k;
int F[kMaxn][kMaxn], pw[kMaxn];

int main() {
	scanf("%d%d", &n, &k);
	F[0][0] = 1;
	for (int i = 1, wi; i <= n; ++i) {
		scanf("%d", &wi);
		for (int j = F[i][0] = 1; j < k; ++j) F[i][j] = Mul(F[i][j - 1], i);
		for (int j = pw[0] = 1; j <= n; ++j) pw[j] = Mul(pw[j - 1], wi);
		for (int j = k; j <= n; ++j) {
			F[i][j] = F[i - 1][j];
			for (int t = 1; t <= j; ++t) Upa(F[i][j], Mul(Mul(F[i - 1][t - 1], F[i][j - t]), pw[std::min(j + 1, t + k) - std::max(t, k)]));
		}
	} printf("%d\n", F[n][n]); return 0;
}
