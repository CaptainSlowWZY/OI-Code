// SDOI 2016
#include <cstdio>
#include <algorithm>

typedef long long LL;

const int kMaxn = 3010;

int n, m, sum[kMaxn], que[kMaxn];
LL DP[2][kMaxn], sqrs[kMaxn], *prv, *nxt, sqrm, avg;

inline LL Sqr(LL x) { return x * x; }
inline double Slope(int k, int j) {
	return ((prv[j] + sqrm * sqrs[j] + sum[j] * avg) -
			(prv[k] + sqrm * sqrs[k] + sum[k] * avg)) /
			(double)(sum[j] - sum[k]);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", sum + i);
		sum[i] += sum[i - 1];
		sqrs[i] = Sqr(sum[i]);
	}

	prv = DP[0], nxt = DP[1];
	sqrm = Sqr(m), avg = sum[n] * m << 1;
	for (int i = 1; i <= n; i++) {
		prv[i] = sqrm * sqrs[i] - avg * sum[i] + sqrs[n];
	}
	for (int i = 2, hd, tl; i <= m; i++) {
		hd = 0, tl = 0;
		que[tl++] = i - 1;
		for (int j = i, k; j <= n; j++) {
			while (hd + 1 < tl && 
				Slope(que[hd], que[hd + 1]) <= 2 * sqrm * sum[j]) ++hd;
			k = que[hd];
		/*	printf(" from DP[%d][%d](%lld) -> DP[%d][%d]\n",
					k, i - 1, prv[k], j, i);*/
			nxt[j] = prv[k] + 
				(sqrs[j] + sqrs[k] - 2 * sum[j] * sum[k]) * sqrm + 
				sqrs[n] + avg * (sum[k] - sum[j]);
		/*	printf(" i = %d, j = %d, DP[%d][%d] = %lld\n", 
					i, j, j, i, nxt[j]);*/
			while (hd + 1 < tl && 
				Slope(que[tl - 2], que[tl - 1]) > 
				Slope(que[tl - 1], j)) --tl;
			que[tl++] = j;
		}
		std::swap(prv, nxt);
	}

	printf("%lld\n", prv[n] / m);
	return 0;
}
