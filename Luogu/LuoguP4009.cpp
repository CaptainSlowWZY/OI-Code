// Luogu P4009
#include <bits/stdc++.h>

const int MAXN = 105;
const int MAXK = 12;
const int MAXV = 200010;
const int INF = 0x7f7f7f7f;
const int DX[] = {1, 0, -1, 0};
const int DY[] = {0, 1, 0, -1};

struct Edge {
	int to, cost, next;
} E[MAXV << 2];

int N, K, A, B, C, tote, M[MAXN][MAXN], id[MAXN][MAXN][MAXK], dist[MAXV], in_que[MAXV], last[MAXV];
std::queue<int> que;

inline void add_edge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, last[u]}, last[u] = tote;
}
void SPFA(int s);

int main() {
	scanf("%d%d%d%d%d", &N, &K, &A, &B, &C);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			scanf("%d", &M[i][j]);
			for (int k = 0; k <= K; k++) id[i][j][k] = i * N + j + k * N * N;
		}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (M[i][j]) {
				for (int d = 0; d < 4; d++) {
					int nx = i + DX[d], ny = j + DY[d];
					if (nx >= 0 && nx < N && ny >= 0 && ny < N)
						d < 2 ? add_edge(id[i][j][K], id[nx][ny][K - 1], 0) :
						add_edge(id[i][j][K], id[nx][ny][K - 1], B);
				}
			}
			for (int k = 0; k <= K; k++) {
				if (k < K) 
					M[i][j] ? add_edge(id[i][j][k], id[i][j][K], A) : 
					add_edge(id[i][j][k], id[i][j][K], A + C);
				if (k > 0 && !M[i][j]) {
					for (int d = 0; d < 4; d++) {
						int nx = i + DX[d], ny = j + DY[d];
						if (nx >= 0 && nx < N && ny >= 0 && ny < N)
							d < 2 ? add_edge(id[i][j][k], id[nx][ny][k - 1], 0) :
							add_edge(id[i][j][k], id[nx][ny][k - 1], B);
					}
				}
			}
		}
	SPFA(id[0][0][K]);
	int ans = INF;
	for (int i = 0; i <= K; i++) ans = std::min(ans, dist[id[N - 1][N - 1][i]]);
	printf("%d\n", ans);

	return 0;
}

void SPFA(int s) {
	memset(dist, 0x7f, sizeof dist);
	for (dist[s] = 0, que.push(s), in_que[s] = 1; !que.empty(); ) {
		int u = que.front(); que.pop();	
		for (int e = last[u], v = E[e].to; e; v = E[e = E[e].next].to) 
			if (dist[v] > dist[u] + E[e].cost) {
				dist[v] = dist[u] + E[e].cost; 
				if (!in_que[v]) que.push(v), in_que[v] = 1;
			}
		in_que[u] = 0;
	}
}
