#include <algorithm>
#include <cstdio>
#include <cstring>

const int kMaxn = 55, kInf = 0x3f3f3f3f;

int n, a, b, totw;
int W[kMaxn], mp[kMaxn], F[kMaxn][kMaxn][kMaxn][kMaxn], G[kMaxn][kMaxn];

template <typename T>
inline void UMin(T & x, T y) { if (y < x) x = y; }

int main() {
	scanf("%d%d%d", &n, &a, &b);
	for (int i = 1; i <= n; ++i) { scanf("%d", W + i); mp[i] = W[i]; }
	std::sort(mp + 1, mp + (totw = n) + 1); totw = std::unique(mp + 1, mp + totw + 1) - mp - 1;
	for (int i = 1; i <= n; ++i) W[i] = std::lower_bound(mp + 1, mp + totw + 1, W[i]) - mp;
	memset(F, 0x3f, sizeof F); memset(G, 0x3f, sizeof G); 
	for (int i = 1; i <= n; ++i) {
		F[i][i][1][totw] = G[i][i] = a, F[i][i][W[i]][W[i]] = G[i + 1][i] = 0;
	}
	for (int s = 2; s <= n; ++s) {
		for (int r, l = 1; (r = l + s - 1) <= n; ++l) {
			for (int k = l; k <= r; ++k) {
				for (int mx = 1; mx <= totw; ++mx) {
					for (int mn = 1; mn <= mx; ++mn) {
						if (F[l][k][mx][mn] == kInf) continue;
						if (k < r) UMin(F[l][r][std::max(mx, W[r])][std::min(mn, W[r])], F[l][k][mx][mn] + G[k + 1][r - 1]);
						int t = mp[mx] - mp[mn];
						UMin(G[l][r], F[l][k][mx][mn] + a + b * t * t + G[k + 1][r]);
					}
				}
			}
/*			for (int i = 1; i <= totw; ++i) for (int j = 1; j <= i; ++j) if (F[l][r][i][j] != kInf)
				printf(" dp[%d, %d][mx = %d][mn = %d] = %d\n", l, r, mp[i], mp[j], F[l][r][i][j]); */
		}
	} printf("%d\n", G[1][n]);
	return 0;
}
