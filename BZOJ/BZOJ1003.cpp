// BZOJ 1003
#include <cstdio>
#include <cstring>
#include <algorithm>

const int INF = 0x3f3f3f3f;

int N, M, K, E, D[25][25], dsa[25][105], DP[105], dist[25], used[25];

int SP(int, int);

int main() {
	memset(D, 0x3f, sizeof D);

	scanf("%d%d%d%d", &N, &M, &K, &E);
	for (int i = 0, x, y, z; i < E; i++) {
		scanf("%d%d%d", &x, &y, &z);
		D[x][y] = D[y][x] = z;
	}
	int d;
	scanf("%d", &d);
	for (int i = 0, p, s, e; i < d; i++) {
		scanf("%d%d%d", &p, &s, &e);
		for (int j = s; j <= e; j++) dsa[p][j] = 1;
	}

	for (int i = 1; i <= M; i++)
		for (int j = 1; j <= N; j++) dsa[i][j] += dsa[i][j - 1];
	DP[0] = -K;
	for (int i = 1; i <= N; i++) {
		DP[i] = INF;
		for (int j = 0; j < i; j++) {
			int cost = SP(j + 1, i);
			if (cost == INF) continue;
			DP[i] = std::min(DP[i], DP[j] + (i - j) * cost + K);
		}
	}

	printf("%d\n", DP[N]);

	return 0;
}

inline int enable(int p, int srt, int end) {
	return !(dsa[p][end] - dsa[p][srt - 1]);
}

int SP(int srt, int end) {
	memset(dist, 0x3f, sizeof dist);
	memset(used, 0, sizeof used);
	dist[1] = 0;
	for (; ; ) {
		int k = -1;
		for (int i = 1; i <= M; i++)
			if (enable(i, srt, end) && !used[i] && (k == -1 || dist[k] > dist[i])) k = i;
		if (k == -1) break;
		used[k] = 1;
		for (int i = 1; i <= M; i++)
			if (!used[i]) dist[i] = std::min(dist[i], dist[k] + D[k][i]);
	}
	return dist[M];
}
