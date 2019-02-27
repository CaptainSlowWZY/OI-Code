#include <cstdio>

const int MAXN = 1e6 + 10;

typedef long long LL;

int N, X[MAXN], C[MAXN], que[MAXN];
LL sums[MAXN], sump[MAXN], DP[MAXN];

inline double slope(int j, int k) {
	return (DP[j] + sums[j] - DP[k] - sums[k]) / double(sump[j] - sump[k]);
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d%lld%d", X + i, sump + i, C + i);
		sums[i] = sums[i - 1] + (LL)X[i] * sump[i];
		sump[i] += sump[i - 1];
	}

	int hd = 0, tl = 1;
	for (int i = 1; i <= N; i++) {
		while (hd + 1 < tl && slope(que[hd + 1], que[hd]) < X[i]) ++hd;
		DP[i] = DP[que[hd]] + (sump[i] - sump[que[hd]]) * X[i] - sums[i] + sums[que[hd]] + C[i];
		while (hd + 1 < tl && slope(que[tl - 1], que[tl - 2]) > slope(i, que[tl - 1])) --tl;
		que[tl++] = i;
	}

	printf("%lld\n", DP[N]);
	return 0;
}
