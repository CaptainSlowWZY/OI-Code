// UVa 1521
#include <cstdio>
#include <algorithm>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif

const int MAXN = 1e4;

int N, P[MAXN + 10], flag[MAXN + 10], totp;

void init();
void work();

int main() {
	init();	
	
	while (scanf("%d", &N) == 1) work();

	return 0;
}

void init() {
	for (int i = 2; i <= MAXN; i++) {
		if (!flag[i]) P[totp++] = i;
		for (int j = 0; j < totp && P[j] * i <= MAXN; j++) {
			flag[P[j] * i] = 1;
			if (i % P[j] == 0) break;
		}
	}
}

void work() {
	int lst = std::upper_bound(P, P + totp, N) - P - 1, fir, ans;
	for (fir = ans = 0; fir <= lst; --lst, ++ans) {
		int tmp = N / P[lst];
		for (; fir <= lst && tmp / P[fir] > 0; ++fir, tmp /= P[fir]);
	}
	printf("%d\n", ans);
}
