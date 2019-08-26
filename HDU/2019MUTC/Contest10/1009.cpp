#include <cstdio>
#include <queue>

#define x first
#define y second

typedef std::pair<int, int> Pii;

const int kMaxn = 2005;
const int kDx[] = {-1, 0, 0, 1};
const int kDy[] = {0, -1, 1, 0};

int n, m, q;
int A[kMaxn][kMaxn];
std::queue<Pii> que;

inline bool Drop(int x, int y) {
	return A[x - 1][y] + A[x + 1][y] <= 1 &&
		A[x][y - 1] + A[x][y + 1] <= 1;
}

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d%d%d", &n, &m, &q);
		for (int i = 0; i <= m + 1; i++) {
			A[0][i] = A[n + 1][i] = 1;
		}
		for (int i = 0; i <= n + 1; i++) {
			A[i][0] = A[i][m + 1] = 1;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) A[i][j] = 1;
		}
		for (int x, y; q--; ) {
			scanf("%d%d", &x, &y);
			if (!A[x][y]) { puts("0"); continue; }
			int ans = 0; A[x][y] = 0;	
			que.push({x, y});
			while (!que.empty()) {
				Pii p = que.front(); que.pop(); ++ans;
				for (int k = 0; k < 4; k++) {
					int nx = p.x + kDx[k],
						ny = p.y + kDy[k];
					if (nx <= 0 || nx > n || ny <= 0 || ny > m)
						continue;
					if (Drop(nx, ny) && A[nx][ny]) {
						A[nx][ny] = 0; que.push({nx, ny});
					}
				}
			} printf("%d\n", ans);
		}
	} return 0;
}
