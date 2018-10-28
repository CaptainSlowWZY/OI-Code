// XJOI 3855
#include <cstdio>
#include <cstring>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif

typedef long long LL;
const int MAXN = 55;
const char IMP[] = "Impossible";
const char PSB[] = "Possible";

int N, X[MAXN][65];
LL A[MAXN], B[MAXN];

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%lld", A + i);
	for (int i = 0; i < N; i++) {
		scanf("%lld", B + i);
		if (B[i] < A[i]) return puts(IMP), 0;
		B[i] -= A[i];
	}
	
#ifdef DEBUG_MD
	for (int i = 0; i < N; i++) debug("%12lld", A[i]);
	putchar('\n');
	for (int i = 0; i < N; i++) debug("%12lld", B[i]);
	putchar('\n');
#endif
	LL tmp = B[0];
	memset(X, 0xff, sizeof X);
	/* Let X[0] = B[0] = X[0] & X[1]
	 * if B[0] == 1, X[0] = X[1] = 1
	 * if B[0] == 0,	X[0] = 0
	 *		if A[0] == 0,	X[1] = 0
	 *		if A[0] == 1,	X[1] = 1
	 */
	for (int i = 0; i <= 60; i++, tmp >>= 1) {
		if (X[0][i] = tmp & 1) {
			X[1][i] = 1;
			if (A[0] >> i & 1 ^ 1) return puts(IMP), 0;
		}
		else if (A[0] >> i & 1 ^ 1) X[0][i] = X[1][i] = 0;
	}
	/* if B[i] = X[i] & X[i + 1] == 1
	 *		X[i] = X[i + 1] = 1
	 *		A[i] = 1
	 */
	for (int i = 1; i < N; i++) {
		tmp = B[i];
		debug("i=%d\n", i);
		for (int j = 0; j <= 60; j++, tmp >>= 1)
			if (tmp & 1) {
				if (!X[i][j]) return /* debug("IMP point %d\n", 1), */ puts(IMP), 0;
				X[i][j] = X[i + 1][j] = 1;
				if (A[i] >> j & 1 ^ 1) return /* debug("IMP point %d\n", 2), */ puts(IMP), 0;
			}
			else {
				// B_i == X[i][j] & X[i + 1][j] == 0
				// if X[i][j] == 1,		X[i + 1][j] = 0
				// if X[i][j] == -1,	A_i = 0,	X[i + 1][j] = 0
				//						A_i = 1,	X[i + 1][j] = -1
				// if X[i][j] == 0,		A_i = 0,	X[i + 1][j] = 0
				//						A_i = 1,	X[i + 1][j] = 1
				if (X[i][j] == 1) {
					X[i + 1][j] = 0;
					if (A[i] >> j & 1 ^ 1) return /* debug("IMP point %d\nj=%d\n", 3, j), */ puts(IMP), 0;
				}
				if (!X[i][j]) X[i + 1][j] = A[i] >> j & 1;
				if (X[i][j] == -1 && A[i] >> j & 1 ^ 1) X[i + 1][j] = 0;
			}
		debug("  i=%d\n", i);
	}
	puts(PSB);
	return 0;
}

// AC!!!