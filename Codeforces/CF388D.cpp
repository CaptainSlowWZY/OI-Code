// Codeforces 388 D
// #Round 228 (Div. 1)
#include <cstdio>
typedef long long LL;
const int MOD = 1e9 + 7;

int DP[32][32][2], N;

inline void add(int & x, int d) { (x += d) %= MOD; }

int main() {
	scanf("%d", &N);
	DP[31][0][1] = 1;
	for (int i = 31; i > 0; i--)
		for (int j = 0; j < 31; j++) {
			add(DP[i - 1][j][0], (1LL << j) * DP[i][j][0] % MOD);
			add(DP[i - 1][j + 1][0], DP[i][j][0]);
			if (N >> i - 1 & 1) {
				add(DP[i - 1][j][1], LL(j ? 1LL << j - 1 : 0) * DP[i][j][1] % MOD);	
				add(DP[i - 1][j][0], LL(j ? 1LL << j - 1 : 1) * DP[i][j][1] % MOD);
				add(DP[i - 1][j + 1][1], DP[i][j][1]);
			}
			else add(DP[i - 1][j][1], LL(j ? 1LL << j - 1 : 1) * DP[i][j][1] % MOD);
		}
	int ans = 0;
	for (int i = 0; i <= 31; i++) add(ans, DP[0][i][0]), add(ans, DP[0][i][1]);
	printf("%d\n", ans);
	return 0;
}

// AC!!!
