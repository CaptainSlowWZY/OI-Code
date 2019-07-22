#include <algorithm>
#include <cstdio>

const int kMaxn = 505, kLg = 10, MOD = 998244353;

int n;
int low[kLg][kMaxn], DP[kMaxn][kMaxn], pw[kLg], Lg[kMaxn], pos[kMaxn];

int Low(int l, int r) {
	int p = Lg[r - l + 1];
	return std::min(low[p][l], low[p][r - pw[p] + 1]);
}
inline void Add(int & x, long long y) {
	(x += y) >= MOD ? x -= MOD : 0;
}

int main() {
	scanf("%d%*d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", low[0] + i);
		DP[i][i] = DP[i + 1][i] = DP[i][i - 1] = 1;
		pos[low[0][i]] = i;
	}

	for (int i = pw[0] = 1; i < kLg; i++) pw[i] = pw[i - 1] << 1;
	Lg[0] = -1;
	for (int i = 1; i <= n; i++) Lg[i] = Lg[i >> 1] + 1;
	for (int i = 1; i < kLg; i++) {
		for (int j = 1; j + pw[i] - 1 <= n; j++) {
			low[i][j] = std::min(low[i - 1][j],
					low[i - 1][j + pw[i - 1]]);
		}
	}
	for (int i = 2; i <= n; i++) {
		for (int l = 1, r = i, c, s1, s2, p; r <= n; l++, r++) {
			p = pos[c = Low(l, r)], s1 = s2 = 0;
			for (int j = l; j <= p; j++)
				Add(s1, 1ll * DP[l][j - 1] * DP[j][p - 1] % MOD);
			for (int j = p; j <= r; j++)
				Add(s2, 1ll * DP[p + 1][j] * DP[j + 1][r] % MOD);
			DP[l][r] = 1ll * s1 * s2 % MOD;
		}
	}
	printf("%d\n", DP[1][n]);
	return 0;
}
