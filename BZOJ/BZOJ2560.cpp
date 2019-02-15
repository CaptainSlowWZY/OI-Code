// BZOJ 2560
#include <cstdio>

typedef long long LL;

const int MOD = 1e9 + 7;

int N, C[20][20], G[(1 << 16) + 5], F[(1 << 16) + 5];

inline void mult(int & x, int y) { x = (LL)x * y % MOD; }
inline void add(int & x, int y) { (x += y) %= MOD; }

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) scanf("%d", &C[i][j]);

	for (int S = (1 << N) - 1; S > 0; --S) {
		G[S] = 1;
		for (int i = 0; i < N; i++)
			if (S >> i & 1) {
				for (int j = i + 1; j < N; j++) 
					if (S >> j & 1) mult(G[S], (C[i][j] + 1) % MOD);
			}
	}
	F[0] = G[0] = 0;
	for (int S = 1, U = 1 << N; S < U; ++S) {
		F[S] = G[S];
		for (int i = 0; i < N; i++)
			if (S >> i & 1) {
				for (int T = S; T; T = T - 1 & S)
					if (T >> i & 1) add(F[S], -(LL)F[T] * G[S ^ T] % MOD);
				break;
			}
	}
	
	add(F[(1 << N) - 1], MOD);
	printf("%d\n", F[(1 << N) - 1]);
	return 0;
}
