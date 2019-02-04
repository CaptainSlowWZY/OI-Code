// Luogu P4011
#include <cstdio>
#include <cstring>
#include <queue>

const int DX[] = {-1, 0, 0, 1};
const int DY[] = {0, -1, 1, 0};

struct Stat {
	int x, y, mask;
	Stat(int x_ = 0, int y_ = 0, int m_ = 0) : x(x_), y(y_), mask(m_) {}
};

int N, M, P, K, S, A[105][105], have[12][12], DP[12][12][1010];
std::queue<Stat> que;

inline bool in(int x, int y) {
	return x > 0 && x <= N && y > 0 && y <= M;
}

int main() {
	scanf("%d%d%d%d", &N, &M, &P, &K);
	for (int x1, y1, x2, y2, g, id1, id2; K--; ) {
		scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &g);
		id1 = (x1 - 1) * M + y1, id2 = (x2 - 1) * M + y2;
		A[id1][id2] = A[id2][id1] = g ? 1 << g - 1 : -1;
	}
	scanf("%d", &S);
	for (int x, y, q; S--; ) {
		scanf("%d%d%d", &x, &y, &q);
		have[x][y] |= 1 << q - 1;
	}

	memset(DP, 0x7f, sizeof DP);
	DP[1][1][0] = 0;
	for (que.push(Stat(1, 1, 0))/*, in_que[1][1][0] = 1*/; !que.empty(); ) {
		Stat u = que.front(); que.pop();
		for (int k = 0; k < 4; k++) {
			int nx = u.x + DX[k], ny = u.y + DY[k], id1 = (u.x - 1) * M + u.y, id2 = (nx - 1) * M + ny, nxt;
			if (in(nx, ny) && (~A[id1][id2] ? (A[id1][id2] & u.mask) == A[id1][id2] : 0)
				&& DP[nx][ny][nxt = u.mask | have[nx][ny]] > DP[u.x][u.y][u.mask] + 1) {
				DP[nx][ny][nxt] = DP[u.x][u.y][u.mask] + 1;
				if (nx == N && ny == M) {
					printf("%d\n", DP[nx][ny][nxt]);
					return 0;
				}
//				if (!in_que[nx][ny][nxt]) que.push(Stat(nx, ny, nxt)), in_que[nx][ny][nxt] = 1;
				que.push(Stat(nx, ny, nxt));
			}
		}
//		in_que[u.x][u.y][u.mask] = 0;
	}

	puts("-1");
	return 0;
}
