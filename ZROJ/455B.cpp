#include <algorithm>
#include <cstdio>

const int kMaxn = 505, kMaxk = 1005, kMod = 1e9 + 7;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upd(int & a, int b) { a = Add(a, b); }

int n, k;
int S[kMaxn], DP[2][kMaxn][kMaxk];

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; ++i) scanf("%d", S + i);
	std::sort(S, S + n);
	for (int i = n - 1; i; --i) S[i] -= S[i - 1];
	int (*prv)[kMaxk] = DP[0], (*nxt)[kMaxk] = DP[1];
	prv[0][0] = prv[1][0] = 1;
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j <= i + 1; ++j) {
			for (int c = 0; c <= k; ++c) nxt[j][c] = 0;
		}
		for (int j = 0; j <= i; ++j) {
			for (int c = 0; c <= k; ++c) {
				if (!prv[j][c] || c + j * S[i] > k) continue;
				Upd(nxt[j + 1][c + j * S[i]], prv[j][c]);
				if (j)
					Upd(nxt[j - 1][c + j * S[i]], Mul(j, prv[j][c]));
				Upd(nxt[j][c + j * S[i]], Mul(j + 1, prv[j][c]));
			}
		} std::swap(prv, nxt);
	}
	int ans = 0;
	for (int i = 0; i <= k; ++i)
		Upd(ans, prv[0][i]);
	printf("%d\n", ans);
	return 0;
}
