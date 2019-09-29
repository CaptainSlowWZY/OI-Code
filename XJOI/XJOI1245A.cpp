#include <cstdio>
#include <queue>

const int kMaxn = 1005;
const int kDx[] = {-1, 0, 0, 1}, kDy[] = {0, -1, 1, 0};

struct Stat { int x, y, step; };

int n, m, k, x0, y0;
int A[kMaxn][kMaxn], X[12], Y[12];

int Bfs(int x1, int y1, int x2, int y2);
void ClearMap();

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) scanf("%d", A[i] + j);
	}
	for (int i = 0; i < k; i++) {
		scanf("%d%d", X + i, Y + i);
		A[X[i]][Y[i]] = 2;
	} scanf("%d%d", &x0, &y0);
	A[x0][y0] = 3;
	int ans = 0;
	for (int i = 0; i < k; i++) {
		A[X[i]][Y[i]] = 0;
		int tmp = Bfs(x0, y0, X[i], Y[i]); 
		if (~tmp) {
			ans += tmp;
			A[X[i]][Y[i]] = 2;
			x0 = X[i], y0 = Y[i];
			ClearMap();
		} else {
			puts("-1");
			return 0;
		}
	} printf("%d\n", ans);
	return 0;
}

void ClearMap() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			if (A[i][j] == 3) A[i][j] = 0;
	}
}

int Bfs(int x1, int y1, int x2, int y2) {
	std::queue<Stat> que;
	que.push((Stat){x1, y1, 0});
	while (!que.empty()) {
		Stat u = que.front(); que.pop();
		for (int k = 0; k < 4; k++) {
			int nx = u.x + kDx[k],
				ny = u.y + kDy[k];
			if (nx > 0 && nx <= n && ny > 0 &&
				ny <= m && !A[nx][ny]) {
				if (nx == x2 && ny == y2)
					return u.step + 1;
				A[nx][ny] = 3;
				que.push((Stat){nx, ny, u.step + 1});
			}
		}
	} return -1;
}
