#include <cstdio>
#include <cmath>
#include <vector>

const int kMaxn = 1005;
const double kEps = 1e-8;

struct Chain { int to; double ratio; };

int n, m;
int vis[kMaxn];
double turn[kMaxn];
std::vector<Chain> G[kMaxn];

bool Dfs(int u, int fa);

int main() {
	int t;
	scanf("%d", &t);
	for (int cs = 1; cs <= t; cs++) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) {
			G[i].clear(); vis[i] = 0;
		}
		for (int u, v, x, y; m--; ) {
			scanf("%d%d%d%d", &u, &v, &x, &y);
			G[u].push_back((Chain){v, 1.0 * y / x});
			G[v].push_back((Chain){u, 1.0 * x / y});
		} int fail = 0;	
		for (int i = 1; i <= n; i++) {
			if (vis[i]) continue;
			turn[i] = 1;
			if (!Dfs(i, 0)) { fail = 1; break; }
		} printf("Case #%d: %s\n", cs, fail ? "No" : "Yes");
	} return 0;
}

inline bool Eq(double x, double y) {
	return fabs(x - y) <= kEps;
}

bool Dfs(int u, int fa) {
	vis[u] = 1;
	for (std::vector<Chain>::iterator c = G[u].begin();
			c != G[u].end(); ++c) {
		if (c->to == fa) continue;
		if (!vis[c->to]) {
			turn[c->to] = turn[u] * c->ratio;
			if (!Dfs(c->to, u)) return false;
		} else if (!Eq(turn[c->to], turn[u] * c->ratio)) {
			return false;
		}
	} return true;
}
