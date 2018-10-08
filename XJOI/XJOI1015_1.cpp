// XJOI 1015 1
#include <cstdio>
#include <cstring>
#include <algorithm>
const int MAXN = 55;
const int INF = 0x3f3f3f3f;
typedef int IntAr[MAXN];

int N, K, DP[MAXN * 10000];
IntAr A, B, C, W;

namespace FastIO {
	template <typename T>
	void read(T & x) {
		x = 0; register char ch = getchar();
		for (; ch < '0' || ch > '9'; ch = getchar());
		for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
	}
}
void readAr(int []);
int sub(int []);
int Bag(int [], int [], int, int);

inline void debugmd() { puts("========= Debug ========="); }
void debug(int arr[], int sz = N) {
	debugmd();
	for (int i = 0; i < sz; i++) printf("%d ", arr[i]);
	putchar('\n');
}

// #define _DEBUG_MD_

int main() {
	using FastIO::read;
	read(N), read(K);
	readAr(A), readAr(B), readAr(C);
	int suma = sub(A), sumb = sub(B);
#ifdef _DEBUG_MD_
	debug(A), debug(B);
	printf("suma=%d, sumb=%d\n", suma, sumb);
#endif
	int ans = std::min(Bag(A, C, K, suma), Bag(B, C, K, sumb)), sumw = 0;
	for (int i = 0; i < N; i++) sumw += (W[i] = A[i] + B[i] + 2);
#ifdef _DEBUG_MD_
	debugmd();
	debug(W);
	printf("sumw=%d\n", sumw);
#endif
	ans = std::min(ans, Bag(W, C, 2 * K - 1, sumw));
	printf("%d\n", ans == INF ? -1 : ans);
	return 0;
}

void readAr(int arr[]) {
	for (int i = 0; i < N; i++) FastIO::read(arr[i]);
}

int sub(int arr[]) {
	int res = 0;
	for (int i = 0; i < N; i++) res += --arr[i];
	return res;
}

int Bag(int wght[], int cost[], int least, int MAXW) {
	memset(DP, 0x3f, sizeof DP);
	DP[0] = 0;
#ifdef _DEBUG_MD_
	debugmd();
	printf("least=%d, MAXW=%d\n", least, MAXW);
	for (int i = 0; i < N; i++) printf("i=%d, weight=%d, cost=%d\n", i, wght[i], cost[i]);
#endif
	for (int i = 0; i < N; i++)
		for (int j = MAXW; j >= wght[i]; j--) DP[j] = std::min(DP[j - wght[i]] + cost[i], DP[j]);
	int res = INF;
	for (int i = least; i <= MAXW; i++) res = std::min(res, DP[i]);
	return res;
}
