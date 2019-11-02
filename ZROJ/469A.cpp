#include <cstdio>

const int kMaxn = 1e5 + 5, kMod = 998244353;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }

int n, dfsc, A[kMaxn], B[kMaxn], C[kMaxn][2], pw[kMaxn];

void Dfs1(int u) { if (!u) return;
	A[u] = ++dfsc; Dfs1(C[u][0]); Dfs1(C[u][1]);
}
void Dfs2(int u) { if (!u) return;
	Dfs2(C[u][0]); Dfs2(C[u][1]); B[u] = ++dfsc;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d%d", C[i], C[i] + 1);
	Dfs1(1); dfsc = 0; Dfs2(1);
	for (int i = pw[0] = 1; i <= n; ++i)
		pw[i] = Mul(pw[i - 1], 2);
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (A[i] <= B[i]) {
			ans = Add(ans, pw[n - A[i]]);
			ans = Sub(ans, pw[n - B[i]]);
		}
	} printf("%d\n", ans);
	return 0;
}
