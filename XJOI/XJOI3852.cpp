// XJOI 3852
#include <cstdio>
#include <algorithm>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...)
#endif

typedef long long LL;

const int INF = 1e9 + 10;

int main() {
	int n, m, w1, w2;
	scanf("%d%d%d%d", &n, &m, &w1, &w2);

	int lb = 0, ub = INF, mid;
	while (ub - lb > 1) {
		// [lb, ub)
		mid = lb + ub >> 1;
		LL d1 = std::min(mid, n - 1),
		   lb1 = (LL)n * mid - ((1 + d1) * d1 / 2 + (n - 1 - d1) * d1), ub1 = (LL)n * mid + (LL)n * (n - 1) / 2,
		   d2 = std::min(mid, m),
		   lb2 = (LL)m * mid - ((1 + d2) * d2 / 2 + (m - d2) * d2), ub2 = (LL)m * mid + (LL)m * (m + 1) / 2;
		lb1 = std::max(lb1, 0LL);
		lb2 = std::max(lb2, 0LL);
		debug(" [%d, %d)\n", lb, ub);
		debug("  1: [%lld, %lld], 2: [%lld, %lld]\n", lb1, ub1, lb2, ub2);
		debug("   w1=%d, w2=%d\n", w1, w2);
		if (w1 < lb1 && w2 > ub2 || w1 > ub1 && w2 < lb2) return puts("Impossible"), 0;
		if (lb1 <= w1 && w1 <= ub1 && lb2 <= w2 && w2 <= ub2) return puts("Possible"), 0;
		if (w1 < lb1 || w2 < lb2) ub = mid;
		else lb = mid;
	}
	mid = lb;
	LL d1 = std::min(mid, n - 1),
	   lb1 = (LL)n * mid - ((1 + d1) * d1 / 2 + (n - 1 - d1) * d1), ub1 = (LL)n * mid + (LL)n * (n - 1) / 2,
	   d2 = std::min(mid, m),
	   lb2 = (LL)m * mid - ((1 + d2) * d2 / 2 + (m - d2) * d2), ub2 = (LL)m * mid + (LL)m * (m + 1) / 2;
	lb1 = std::max(lb1, 0LL);
	lb2 = std::max(lb2, 0LL);
	if (lb1 <= w1 && w1 <= ub1 && lb2 <= w2 && w2 <= ub2) puts("Possible");
	else puts("Impossible");
	return 0;
}

// AC!!!
