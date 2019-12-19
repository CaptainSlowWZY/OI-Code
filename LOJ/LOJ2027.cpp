#include <algorithm>
#include <cstdio>
#include <vector>

#define fi first
#define se second

const int kMaxn = 18, kMod = 1e9 + 7;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upa(int & a, int b) { a = Add(a, b); }
inline void Ups(int & a, int b) { a = Sub(a, b); }
inline void Upm(int & a, int b) { a = Mul(a, b); }
int FPow(int bs, int ex = kMod - 2) { 
	int res = 1;
	for (; ex; Upm(bs, bs), ex >>= 1) if (ex & 1) Upm(res, bs);
	return res;
}

int n, n1;
std::vector<std::pair<int, int> > E[kMaxn];
int A[kMaxn][kMaxn];

int main() {
	scanf("%d", &n); n1 = n - 1;
	for (int i = 0, m; i < n1; ++i) {
		scanf("%d", &m);
		for (int u, v; m--; ) { scanf("%d%d", &u, &v); E[i].push_back({--u, --v}); }
	}
	int ans = 0;
	for (int s = (1 << n1) - 1, res, fail; s; --s) {
		for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) A[i][j] = 0;
		for (int i = 0; i < n1; ++i) if (s >> i & 1) for (auto & p : E[i]) {
			Ups(A[p.fi][p.se], 1), Ups(A[p.se][p.fi], 1); Upa(A[p.fi][p.fi], 1), Upa(A[p.se][p.se], 1);
		}
		for (int i = fail = 0; i < n1; ++i) {
			if (!A[i][i]) {
				fail = 1;
				for (int j = i; j < n1; ++j) if (A[j][i]) {
					for (int k = 0; k < n1; ++k) std::swap(A[i][k], A[j][k]);
					fail = 0; break;
				}
			}
			if (fail) break;
			for (int j = i + 1; j < n1; ++j) {
				int t = Mul(A[j][i], FPow(A[i][i]));
				for (int k = i; k < n1; ++k) Ups(A[j][k], Mul(A[i][k], t));
			}
		} res = 1;
		for (int i = 0; i < n1; ++i) Upm(res, A[i][i]);
		if (n1 - __builtin_popcount(s) & 1) Ups(ans, res); else Upa(ans, res);
	} printf("%d\n", ans);
	return 0;
}
