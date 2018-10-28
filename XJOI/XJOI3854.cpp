// XJOI 3854
#include <cstdio>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...)
#endif

const int MAXN = 55;

int N, A[MAXN], lmt[MAXN];

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d", A + i), lmt[i] = 1;

	int ans = 0;
	for (int i = 30; i >= 0; i--) {
		int k = -1;
		for (int j = 0; j < N; j++)
			if (lmt[j] && A[j] >> i & 1 || !lmt[j]) {
				if (k == -1 || (A[j] & (1 << i) - 1) > (A[k] & (1 << i) - 1)) k = j;
			}
		if (~k) {
			debug("i=%d, k=%d\n", i, k);
			ans += 1 << i;
			for (int j = 0; j < N; j++)
				if (j != k) lmt[j] = lmt[j] & (A[j] >> i & 1 ^ 1);
		}
	}

	printf("%d\n", ans);
	return 0;
}

// AC!!!
