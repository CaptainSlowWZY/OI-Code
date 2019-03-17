#include <cstdio>

const int kMaxn = 2e5 + 10, MOD = 1e9 + 7;

int n, DP[kMaxn], last[kMaxn], L[kMaxn];

inline void Add(int & x, long long y) {
	x = (x + y) % MOD;
}

int main() {
	scanf("%d", &n);
	for (int i = 1, ci; i <= n; i++) {
		scanf("%d", &ci);
		if (last[ci] && last[ci] + 1 != i) L[i] = last[ci];
		last[ci] = i;
	}

	DP[0] = 1;
	for (int i = 1; i <= n; i++) {
		Add(DP[i], DP[i - 1]);
		if (L[i]) {
			Add(DP[i], DP[L[i]]);
		}
	}

	printf("%d\n", DP[n]);
	return 0;
}
