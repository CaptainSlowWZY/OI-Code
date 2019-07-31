#include <algorithm>
#include <cstdio>

const int kMaxn = 1010, kMaxv = 1e6 + 10;
const int kDx[] = {1, 0}, kDy[] = {0, 1};

struct Edge {
	int u, v, c;
	bool operator<(const Edge & e) const {
		return c < e.c;
	}
} E[kMaxv << 1];

int n, m, index, tote;
int id[kMaxn][kMaxn], fa[kMaxv];

inline int Find(int x) {
	return fa[x] == x ? x : fa[x] = Find(fa[x]);
}
inline void Merge(int x, int y) {
	x = Find(x), y = Find(y);
	fa[x] = y;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			id[i][j] = ++index;
			fa[index] = index;
		}
	}
	for (int x1, y1, x2, y2;
			~scanf("%d%d%d%d", &x1, &y1, &x2, &y2); ) {
		Merge(id[x1][y1], id[x2][y2]);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int k = 0, x, y; k < 2; k++) {
				x = i + kDx[k], y = j + kDy[k];
				if (x < 1 || x > n || y < 1 || y > m) continue;
				E[tote++] = (Edge){id[i][j], id[x][y], k + 1};
			}
		}
	}
	std::sort(E, E + tote);
	int ans = 0;
	for (int i = 0, u, v; i < tote; i++) {
		u = E[i].u, v = E[i].v;
		if (Find(u) == Find(v)) continue;
		Merge(u, v); ans += E[i].c;
	}
	printf("%d\n", ans);
	return 0;
}
