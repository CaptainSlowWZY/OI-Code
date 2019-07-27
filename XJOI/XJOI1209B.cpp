#include <algorithm>
#include <cstdio>

typedef long long LL;

const int kMaxn = 205;

int n, P;
LL A[kMaxn][kMaxn];

int main() {
	scanf("%d%d", &n, &P);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%lld", A[i] + j);
			A[i][j] %= P;
		}
	}

	int rev = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int r1 = i, r2 = j;
			for (int t; A[r2][i]; std::swap(r1, r2)) {
				t = A[r1][i] / A[r2][i];
				for (int k = 0; k < n; k++)
					(A[r1][k] -= t * A[r2][k] % P) %= P;
			}
			if (r1 ^ i) {
				rev ^= 1;
				for (int k = 0; k < n; k++)
					std::swap(A[r1][k], A[i][k]);
			}
		}
	}
	LL ans = rev ? -1 : 1;
	for (int i = 0; i < n; i++) (ans *= A[i][i]) %= P;
	(ans += P) %= P;
	printf("%lld\n", ans);
	return 0;
}
