// XJOI 1015 2
#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>
#define fir first
#define sec second
typedef std::pair<int, int> P;
typedef long long LL;
const int MAXN = 305;
const int MAXM = 2505;
const int INF_32 = 0x3f3f3f3f;

int N, M, A[MAXM], B[MAXM], DP[MAXN][MAXN];
LL D[MAXN][MAXN];
P V[MAXN];

namespace FastIO {
	template <typename T>
	void read(T & x) {
		x = 0; register char ch = getchar();
		for (; ch < '0' || ch > '9'; ch = getchar());
		for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
	}
}
void readAr(int arr[]) {
	for (int i = 0; i < M; i++) FastIO::read(arr[i]);
}

int main() {
	using FastIO::read;
	read(N), read(M);
	readAr(A), readAr(B);
	memset(DP, 0x3f, sizeof DP);
	for (int i = 0; i < N; i++) DP[i][i] = 0;
	for (int i = 0, wi; i < M; i++) {
		read(wi);
		DP[A[i]][B[i]] = DP[B[i]][A[i]] = std::min(DP[B[i]][A[i]], wi);
	}
	for (int i = 0; i < N; i++) {
		read(V[i].fir);
		V[i].sec = i;
	}
	std::sort(V, V + N);
	memset(D, 0x7f, sizeof D);
	for (int k = 0; k < N; k++) 
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				int u = V[i].sec, t = V[k].sec, v = V[j].sec;
				DP[u][v] = std::min(DP[u][v], std::max(DP[u][t], DP[t][v]));	
				if (DP[u][v] == INF_32) continue;
				D[u][v] = std::min(D[u][v], (LL)std::max(V[i].fir, std::max(V[j].fir, V[k].fir)) * DP[u][v]);
			}
	LL ans = 0;
	for (int i = 1; i < N; i++)
		for (int j = 0; j < i; j++) ans += D[i][j];
	printf("%lld\n", ans);
	return 0;
}
