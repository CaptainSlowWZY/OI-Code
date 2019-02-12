// Luogu P1879
// USACO 06 NOV
#include <cstdio>
#include <vector>

const int MOD = 1e8;

int N, M, stat[13], DP[13][400];
std::vector<int> V;

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++) {
		int & cur = stat[i];
		for (int x, j = 0; j < M; j++) {
			scanf("%d", &x);
			cur |= x << j;
		}
	}

	for (int mask = (1 << M) - 1; mask >= 0; mask--) {
		int fail = 0;
		for (int i = 0; i + 1 < M; i++)
			if (mask >> i & 1 && mask >> i + 1 & 1) {
				fail = 1;
				break;
			}
		if (fail) continue;
		V.push_back(mask);
	}
	int sz = V.size();
	DP[0][sz - 1] = 1;
	for (int i = 1; i <= N; i++)
		for (int j = 0; j < sz; j++) {
			if ((V[j] & stat[i]) != V[j]) continue;
			for (int k = 0; k < sz; k++) {
				if (V[j] & V[k]) continue;
				(DP[i][j] += DP[i - 1][k]) %= MOD;
			}
		}
	int ans = 0;
	for (int i = 0; i < sz; i++) (ans += DP[N][i]) %= MOD;
	
	ans = (ans % MOD + MOD) % MOD;
	printf("%d\n", ans);
	return 0;
}
