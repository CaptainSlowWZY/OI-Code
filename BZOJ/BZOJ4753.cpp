#include <cmath>
#include <cstdio>

#define forto(_) for (int e = back[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int kMaxn = 2505;
const double kEps = 1e-10, kInf = 1e10;

struct Edge {
	int to, next;
} E[kMaxn];

int n, k, tote;
int S[kMaxn], P[kMaxn], sz[kMaxn], back[kMaxn];
double DP[kMaxn][kMaxn], val[kMaxn];

inline void AddEdge(int u, int v) { E[++tote] = (Edge){v, back[u]}, back[u] = tote; }
inline void Umax(double & x, double y) { y > x ? x = y : 0; }
bool Check(double);

int main() {
	scanf("%d%d", &k, &n);
	double mid, lb = 0, ub = 0;
	for (int i = 1, Ri; i <= n; i++) {
		scanf("%d%d%d", S + i, P + i, &Ri);
		AddEdge(Ri, i);
		Umax(ub, P[i] / (1.0 * S[i]));
	}

	double ans;
	for (++k; fabs(ub - lb) > 1e-4; ) {
		mid = (lb + ub) / 2;
		if (Check(mid)) {
			lb = mid;
			ans = mid;
		} else ub = mid;
	}

	printf("%.3f\n", ans);
	return 0;
}

void Upd(int v, int u) {
	static double F[kMaxn];
	for (int i = sz[u] + sz[v]; i >= 0; i--) F[i] = -kInf;
	for (int i = 0; i <= sz[u]; i++) {
		for (int j = 0; j <= sz[v]; j++) Umax(F[i + j], DP[u][i] + DP[v][j]);
	}
	sz[u] += sz[v];
	for (int i = sz[u]; i >= 0; i--) Umax(DP[u][i], F[i]);
}

void Dfs(int u) {
	DP[u][0] = sz[u] = 0;
	forto(u) {
		Dfs(v);
		Upd(v, u);
	}
	for (int i = sz[u]; i >= 0; i--) DP[u][i + 1] = DP[u][i] + val[u];
	++sz[u];
	DP[u][0] = 0;
}

bool Check(double lamb) {
	for (int i = 0; i <= n; i++) {
		val[i] = P[i] - lamb * S[i];
		for (int j = 0; j <= n; j++) DP[i][j] = -kInf;
	}
	Dfs(0);
	return DP[0][k] > 0;
}
