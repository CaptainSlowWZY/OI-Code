#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define forto(_) for (int e = back[_], v = B[e]; ~e; \
		v = B[e = prv[e]])

const int kMaxn = 1005, kMaxm = 10005;

int n, m, S, F;
int A[kMaxm], B[kMaxm], L[kMaxm], prv[kMaxm];
int back[kMaxn], dis[kMaxn][2], vis[kMaxn][2], way[kMaxn][2];

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		memset(back, 0xff, sizeof back);

		scanf("%d%d", &n, &m);
		for (int i = 0; i < m; i++) {
			scanf("%d%d%d", A + i, B + i, L + i);
			prv[i] = back[A[i]], back[A[i]] = i;
		}
		scanf("%d%d", &S, &F);

		memset(dis, 0x7f, sizeof dis);
		memset(vis, 0, sizeof vis);
		memset(way, 0, sizeof way);
		dis[S][0] = 0, way[S][0] = 1;
		while (true) {
			int k = -1, fg;
			for (int i = 1; i <= n; i++) {
				if (!vis[i][0] && (k == -1 || dis[k][fg] > dis[i][0])) {
					k = i, fg = 0;
				} else if (!vis[i][1] && 
					(k == -1 || dis[k][fg] > dis[i][1])) {
					k = i, fg = 1;
				}
			}
			if (k == -1) break;
			vis[k][fg] = 1;
			forto(k) {
				if (dis[v][0] > dis[k][fg] + L[e]) {
					dis[v][1] = dis[v][0];
					way[v][1] = way[v][0];
					dis[v][0] = dis[k][fg] + L[e];
					way[v][0] = way[k][fg];
				} else if (dis[v][0] == dis[k][fg] + L[e]) {
					way[v][0] += way[k][fg];
				} else if (dis[v][1] > dis[k][fg] + L[e]) {
					dis[v][1] = dis[k][fg] + L[e];
					way[v][1] = way[k][fg];
				} else if (dis[v][1] == dis[k][fg] + L[e]) {
					way[v][1] += way[k][fg];
				}
			}
		}

		printf("%d\n", 
				way[F][0] + (dis[F][1] == dis[F][0] + 1 ? way[F][1] : 0));
	}
	return 0;
}
