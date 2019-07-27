#include <cstdio>
#include <cmath>
#include <cstring>

#define forto(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)

const int kMaxn = 1010, kMaxm = 5010;
const double kEps = 1e-5;

struct Edge {
	int to;
	double cost;
	int next;
} E[kMaxm];

int n, m, tote;
int A[kMaxn], back[kMaxn], vis[kMaxn];
int U[kMaxm], V[kMaxm], T[kMaxm];
double dis[kMaxn];

bool Check(double);

int main() {
	scanf("%d%d", &n, &m);
	double lb = 0, ub = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", A + i);
		ub += A[i];
	}
	for (int i = 0; i < m; i++)
		scanf("%d%d%d", U + i, V + i, T + i);

	for (double mid; fabs(ub - lb) > kEps; ) {
		mid = (lb + ub) / 2.0;
		if (Check(mid)) lb = mid;
		else ub = mid;
	}
	printf("%.2lf\n", lb - 0.0005);
	return 0;
}

bool Dfs(int u) {
	vis[u] = 1;
	forto(u) {
		if (dis[u] + E[e].cost < dis[v]) {
			dis[v] = dis[u] + E[e].cost;
			if (vis[v] || Dfs(v)) return true;
		}
	}
	vis[u] = 0;
	return false;
}

inline void AddEdge(int u, int v, double c) {
//	printf("   addedge %d -> %d, cost %.2lf\n", u, v, c);
	E[++tote] = (Edge){v, c, back[u]}, back[u] = tote;
}

bool Check(double x) {
	tote = 0;
	memset(back, 0, sizeof back);
	memset(dis, 0, sizeof dis);
	memset(vis, 0, sizeof vis);

//	printf(" # CHECK %.2lf\n", x);
	for (int i = 0; i < m; i++)
		AddEdge(U[i], V[i], x * T[i] - A[V[i]]);
	for (int i = 1; i <= n; i++) {
		if (Dfs(i)) return true;
	}
	return false;
}
