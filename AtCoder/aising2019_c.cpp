#include <bits/stdc++.h>

#define fir first
#define sec second

typedef std::pair<int, int> Pii;

const int DX[] = {-1, 0, 0, 1};
const int DY[] = {0, -1, 1, 0};

char S[410][410];
int H, W, vis[410][410];

long long BFS(int, int);

int main() {
	scanf("%d%d", &H, &W);
	for (int i = 0; i < H; i++) scanf("%s", S[i]);

	long long ans = 0;
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			if (!vis[i][j]) ans += BFS(i, j);

	printf("%lld\n", ans);
	
	return 0;
}

long long BFS(int sx, int sy) {
	std::queue<Pii> que;
	long long cnt1, cnt2;
	for (cnt1 = cnt2 = 0, vis[sx][sy] = 1, que.push(Pii(sx, sy)); !que.empty(); ) {
		Pii now = que.front(); que.pop();
		S[now.fir][now.sec] == '#' ? ++cnt1 : ++cnt2;
		for (int k = 0; k < 4; k++) {
			int nx = now.fir + DX[k], ny = now.sec + DY[k];
			if (nx >= 0 && nx < H && ny >=0 && ny < W && !vis[nx][ny] && S[nx][ny] ^ S[now.fir][now.sec]) {
				vis[nx][ny] = 1;
				que.push(Pii(nx, ny));
			}
		}
	}

	return cnt1 * cnt2;
}
