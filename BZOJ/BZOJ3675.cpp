// BZOJ 3675
// APIO 2014
#include <cstdio>
#include <cstring>

typedef long long LL;

const int MAXN = 1e5 + 5, MAXK = 205;
const LL INF = 0x3f3f3f3f3f3f3f3f;

int N, K, Q[MAXN], pre[MAXK][MAXN];
LL F[MAXN], G[MAXN], S[MAXN];

inline LL sqr(LL x) { return x * x; }
inline double slope(int j, int k) {	// k < j, so S[k] < S[j]
	return S[j] == S[k] ? (F[j] >= F[k] ? -INF : INF) : double(sqr(S[j]) - F[j] - sqr(S[k]) + F[k]) / (S[j] - S[k]);
}

int main() {
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; i++) {
		scanf("%lld", S + i);
		S[i] += S[i - 1];
	}

	for (int i = 1; i <= K; i++) {
		int hd = 0, tl = 0;
		Q[tl++] = 0;
		for (int j = 1; j <= N; j++) {
			while (hd + 1 < tl && slope(Q[hd + 1], Q[hd]) <= S[j]) ++hd;
			pre[i][j] = Q[hd];
			int pr = Q[hd];
			G[j] = F[pr] - sqr(S[pr]) + S[pr] * S[j];
			while (hd + 1 < tl && slope(j, Q[tl - 1]) <= slope(Q[tl - 1], Q[tl - 2])) --tl;
			Q[tl++] = j;
		}
		memcpy(F, G, sizeof(LL) * (N + 1));	
	}
	
	printf("%lld\n", F[N]);
	for (int i = pre[K][N], j = K - 1; j >= 0; i = pre[j--][i]) printf("%d ", i);
	putchar('\n');
	return 0;
}
