#include <cstdio>

const int kMaxn = 1005;

int n;
int A[kMaxn][kMaxn], stat[kMaxn][kMaxn];
int sver[kMaxn][kMaxn], shor[kMaxn][kMaxn];

int Dfs(int, int);

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				scanf("%d", A[i] + j);
				sver[j][i] = sver[j][i - 1] + A[i][j];
				shor[i][j] = shor[i][j - 1] + A[i][j];
				stat[i][j] = -1;
			}
		} puts(Dfs(n, n) ? "W" : "L");
	} return 0;
}

int Dfs(int x, int y) {
	if (!x || !y) return 0;
	if (~stat[x][y]) return stat[x][y];
	if (sver[y][x] & 1 ^ 1 && !Dfs(x, y - 1))
		return stat[x][y] = 1;
	if (shor[x][y] & 1 ^ 1 && !Dfs(x - 1, y))
		return stat[x][y] = 1;
	return stat[x][y] = 0;
}
