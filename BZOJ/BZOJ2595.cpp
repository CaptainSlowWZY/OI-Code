// WC2008
#include <cstdio>
#include <cstring>
#include <utility>

#define fir first
#define sec second

typedef std::pair<int, int> Pii;

const int kInf = 0x3f3f3f3f;
const int kDx[] = {-1, 0, 0, 1}, kDy[] = {0, -1, 1, 0};

int r, c, n;
int A[10][10], inq[10][10], flag[10][10];
int prvs[10][10][1050], DP[10][10][1050];
Pii que[300], prvp[10][10][1050];

void Dfs(int x, int y, int s);

int main() {
	memset(DP, 0x3f, sizeof DP);

	scanf("%d%d", &r, &c);
	int sx, sy;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			scanf("%d", &A[i][j]);
			if (!A[i][j]) {
				DP[i][j][1 << n++] = 0;
				sx = i, sy = j;
			}
		}
	}

	for (int S = 1, hd, tl; S < 1 << n; S++) {
		hd = tl = 0;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				for (int T = S - 1 & S; T; T = T - 1 & S) {
					if (DP[i][j][T] + DP[i][j][S ^ T] - A[i][j] <
						DP[i][j][S]) {
						DP[i][j][S] = 
							DP[i][j][T] + DP[i][j][S ^ T] - A[i][j];
						prvp[i][j][S] = Pii(i, j), prvs[i][j][S] = T;
					}

				}
				if (DP[i][j][S] < kInf) {
					que[tl++] = Pii(i, j);
					inq[i][j] = 1;
				}
			}
		}

		for (int x, y; hd < tl; hd++) {
			x = que[hd].fir, y = que[hd].sec;
			for (int i = 0, nx, ny; i < 4; i++) {
				nx = x + kDx[i], ny = y + kDy[i];
				if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
				if (DP[nx][ny][S] > DP[x][y][S] + A[nx][ny]) {
					DP[nx][ny][S] = DP[x][y][S] + A[nx][ny];
					prvp[nx][ny][S] = Pii(x, y), prvs[nx][ny][S] = S;
					if (!inq[nx][ny]) {
						que[tl++] = Pii(nx, ny);
						inq[nx][ny] = 1;
					}
				}
			}
			inq[x][y] = 0;
		}
	}

	printf("%d\n", DP[sx][sy][(1 << n) - 1]);
	Dfs(sx, sy, (1 << n) - 1);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (!A[i][j]) putchar('x');
			else if (flag[i][j]) putchar('o');
			else putchar('_');
		}
		putchar('\n');
	}

	return 0;
}

void Dfs(int x, int y, int mask) {
	if (!prvs[x][y][mask]) return;
	flag[x][y] = 1;
	Dfs(prvp[x][y][mask].fir, prvp[x][y][mask].sec, prvs[x][y][mask]);
	if (prvp[x][y][mask].fir == x && prvp[x][y][mask].sec == y) {
		Dfs(prvp[x][y][mask].fir, prvp[x][y][mask].sec, 
				mask ^ prvs[x][y][mask]);
	}
}
