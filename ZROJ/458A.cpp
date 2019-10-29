#include <algorithm>
#include <cstdio>
#include <cmath>

#define fi first
#define se second

typedef double DB;
typedef std::pair<DB, int> Pdi;
typedef std::pair<int, DB> Pid;

const int kMaxn = 7005;
const DB kInfD = 1e12;

int n, n0, m, k, flag;
int X[kMaxn], Y[kMaxn], used[kMaxn];
DB ans;
Pdi dis[kMaxn];
std::vector<Pid> G[kMaxn];

inline DB Sqr(DB x) { return x * x; }
inline DB Dist(int a, int b) {
	if (a > b) std::swap(a, b);
	return b >= n0 ? fabs(Y[a] - Y[b]) :
		sqrt(Sqr(X[a] - X[b]) + Sqr(Y[a] - Y[b]));
}
inline void AddEdge(int u, int v, DB c) {
	if (u == v) return;
	G[u].push_back({v, c}), G[v].push_back({u, c});
}
void Dfs(int, int, DB);

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < k; ++i) {
		scanf("%d%d", X + i, Y + i);
		dis[i] = {kInfD, 0};
	} dis[0] = {0, 0}, n0 = k;
	X[k] = 0, Y[k] = 0, dis[k++] = {kInfD, 0};
	X[k] = 0, Y[k] = m, dis[k++] = {kInfD, 0};
	for (int i = 0; i < k; ++i) {
		int t = -1;
		for (int j = 0; j < k; ++j) {
			if (used[j]) continue;
			if (t == -1 || dis[j].fi < dis[t].fi) t = j;
		} AddEdge(t, dis[t].se, dis[t].fi); used[t] = 1;
//		printf(" t = %d, dis[t].fi %.5lf, se %d\n", t, dis[t].fi, dis[t].se);
		for (int j = 0; j < k; ++j) {
			if (used[j]) continue;
			DB tmp = Dist(j, t);
//			printf("   dist(%d, %d) %.5lf\n", t, j, tmp);
//			printf("   --- Dist calc -> %.5lf\n", Dist(j, t));
			if (tmp < dis[j].fi) dis[j] = {tmp, t};
		}
	} Dfs(n0, -1, 0);
	printf("%.8lf\n", ans / 2);
	return 0;
}

void Dfs(int u, int fa, DB mx) {
	if (u == n0 + 1) {
		flag = 1;
		return (void)(ans = mx);
	}
	for (auto & e : G[u]) {
		if (e.fi == fa) continue;
		Dfs(e.fi, u, std::max(mx, e.se));
		if (flag) return;
	}
}
