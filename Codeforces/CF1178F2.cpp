#include <algorithm>
#include <cstdio>
#include <vector>
#include <cassert>

#define pb push_back

const int kMaxn = 505, kMaxm = 1e6 + 10, kLg = 11, MOD = 998244353;

int n, m;
int C[kMaxm];
int low[kLg][kMaxn << 1], DP[kMaxn << 1][kMaxn << 1];
int pw[kLg], Lg[kMaxn << 1];
std::vector<int> pos[kMaxn];

int Low(int l, int r) {
	int p = Lg[r - l + 1];
	return std::min(low[p][l], low[p][r - pw[p] + 1]);
}
inline void Add(int & x, long long y) {
	(x += y) >= MOD ? x -= MOD : 0;
}
inline void Mul(int & x, long long y) {
	x = x * y % MOD;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d", C + i);

	m = std::unique(C + 1, C + m + 1) - C - 1;
	if (m > 2 * n) { puts("0"); return 0; }
	for (int i = 1; i <= m; i++) {
		low[0][i] = C[i], pos[C[i]].pb(i);
		DP[i + 1][i] = DP[i][i - 1] = 1;
	}
	for (int i = 1; i <= n; i++)
		DP[pos[i][0]][*pos[i].rbegin()] = 1;

	for (int i = pw[0] = 1; i < kLg; i++) pw[i] = pw[i - 1] << 1;
	Lg[0] = -1;
	for (int i = 1; i <= m; i++) Lg[i] = Lg[i >> 1] + 1;
	for (int i = 1; i < kLg; i++) {
		for (int j = 1; j + pw[i] - 1 <= m; j++) {
			low[i][j] = std::min(low[i - 1][j],
					low[i - 1][j + pw[i - 1]]);
		}
	}

	for (int i = 2; i <= m; i++) {
		for (int l = 1, r = i, c, s1, s2, lc, rc; r <= m; l++, r++) {
			c = Low(l, r), s1 = s2 = 0;
			if ((lc = *pos[c].begin()) < l ||
				(rc = *pos[c].rbegin()) > r) continue;
			for (int j = l; j <= lc; j++)
				Add(s1, 1ll * DP[l][j - 1] * DP[j][lc - 1] % MOD);
			for (int j = rc; j <= r; j++)
				Add(s2, 1ll * DP[rc + 1][j] * DP[j + 1][r] % MOD);
			DP[l][r] = 1ll * s1 * s2 % MOD;
			for (int j = 1; j < pos[c].size(); j++)
				Mul(DP[l][r], DP[pos[c][j - 1] + 1][pos[c][j] - 1]);
		}
	}
	printf("%d\n", DP[1][m]);
	return 0;
}
