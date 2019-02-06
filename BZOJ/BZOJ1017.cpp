// BZOJ 1017
#include <cstdio>
#include <cstring>
#include <algorithm>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int MAXN = 55;
const int MAXM = 2010;

typedef int IntAr[MAXN];

struct Edge {
	int to, need, next;
} E[MAXN << 1];

int N, M, tote, DP[MAXM], F[MAXN][MAXM][110];
IntAr last, C, L, P, deg;
char str[20];

inline void add_edge(int u, int v, int nd) {
	E[++tote] = (Edge){v, nd, last[u]}, last[u] = tote, ++deg[v];
}
void dfs(int u);

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++) {
		scanf("%d%s", P + i, str);
		if (str[0] == 'A') {
			int ci;
			scanf("%d", &ci);
			for (int to, nd; ci--; ) {
				scanf("%d%d", &to, &nd);
				add_edge(i, to, nd);
			}
		}
		else scanf("%d%d", C + i, L + i);
	}

	memset(F, 0, sizeof F);
	for (int i = 1; i <= N; i++)
		if (!deg[i]) {
			dfs(i);
			for (int j = M; j >= 0; j--) {
				for (int k = 0; k <= j; k++)
					DP[j] = std::max(DP[j], DP[j - k] + F[i][k][0]);
			}
		}
	printf("%d\n", DP[M]);
	return 0;
}

void dfs(int u) {
	if (!last[u]) {
		L[u] = std::min(L[u], M / C[u]);
		for (int i = 0; i <= L[u]; i++)
			for (int j = 0; j <= i; j++)
				F[u][i * C[u]][j] = (i - j) * P[u];
		return;
	}
	L[u] = 0x7f7f7f7f;
	forto(u) {
		dfs(v);
		L[u] = std::min(L[u], L[v] / E[e].need), C[u] += C[v] * E[e].need;
	}
	L[u] = std::min(L[u], M / C[u]);
	static int g[MAXM];
	for (int i = L[u]; i >= 0; i--) {
		memset(g, 0, sizeof g);
		g[0] = 0;
		forto(u) {
			for (int j = M; j >= 0; j--) {
				int t = 0;
				for (int k = 0; k <= j; k++)
					t = std::max(t, g[j - k] + F[v][k][i * E[e].need]);
				g[j] = t;
			}
		}
		for (int j = 0; j <= i; j++)
			for (int k = 0; k <= M; k++)
				F[u][k][j] = std::max(F[u][k][j], g[k] + P[u] * (i - j));
	}
}
