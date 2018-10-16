// qinggong
#include <cstdio>
#include <cstring>
#include <algorithm>

// #define _JUDGE_MD_
// #define _DEBUG_MD_

typedef long long LL;
const int MAXN = 505;
const int MAXK = 105;
const LL INF_64 = 0x3f3f3f3f3f3f3f3f;

int N, K, W, C[MAXN], A[MAXN], Q, invl[MAXN][MAXK];
LL DP[MAXN][MAXK];

namespace FastIO {
	template <typename T>
		void read(T & x) {
			x = 0; register char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
}

int main() {
#ifdef _JUDGE_MD_
	freopen("qinggong.in", "r", stdin);
	freopen("qinggong.out", "w", stdout);
#endif
	using FastIO::read;
	read(N), read(K), read(W);
	for (int i = 0; i < K; i++) read(C[i]), read(A[i]);
	read(Q);
	for (int i = 0, xi, ki; i < Q; i++) {
		read(xi), read(ki);
		++invl[xi][--ki];
	}
#ifdef _DEBUG_MD_
	for (int i = 0; i < K; i++) printf("cost %d, can cross %d\n", A[i], C[i]);
	putchar('\n');
#endif
	memset(DP, 0x3f, sizeof DP);
	for (int i = 0; i < K; i++)
		if (!invl[0][i]) DP[0][i] = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 0; j < K; j++) invl[i][j] += invl[i - 1][j];
#ifdef _DEBUG_MD_
	for (int i = 0; i < K; i++) {
		for (int j = 1; j <= N; j++) printf("\t%d", invl[j][i]);
		putchar('\n');
	}
#endif
	for (int i = 1; i <= N; i++)
#ifdef _DEBUG_MD_
	{
#endif
		for (int j = 0; j < K; j++)
		   if (C[j] <= i && invl[i][j] - invl[i - C[j]][j] == 0) {
			   for (int k = 0; k < K; k++)
				   if (DP[i - C[j]][k] != INF_64) DP[i][j] = std::min(DP[i][j], DP[i - C[j]][k] + (k == j ? 0 : W) + A[j]);
		   }
#ifdef _DEBUG_MD_
		printf("\ni=%d\n", i);
		for (int j = 0; j < K; j++) printf("j=%d, DP[i][j]=%lld; ", j, DP[i][j]);
		putchar('\n');
	}
#endif
	LL ans = INF_64;
	for (int i = 0; i < K; i++) ans = std::min(ans, DP[N][i]);
	printf("%lld\n", ans == INF_64 ? -1 : ans);
#ifdef _JUDGE_MD_
 	fclose(stdin); fclose(stdout);
#endif
	return 0;
}

// AC!!!
