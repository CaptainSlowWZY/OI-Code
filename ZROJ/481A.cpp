#include <cstdio>
#include <vector>

#define SZ(_) (int)_.size()

const int kMaxn = 5005;

int n, rt, ans, F[kMaxn][kMaxn][2], dep[kMaxn], col[kMaxn];
std::vector<int> G[kMaxn];

void Dfs(int u);
void Way(int u, int i, int c);

int main() {
	scanf("%d", &n);
	for (int fa, i = 1; i <= n; ++i) {
		scanf("%d", &fa);
		if (!fa) rt = i;
		G[fa].push_back(i);
	} Dfs(rt);
	for (int i = 0; i <= dep[rt]; ++i) {
	//	printf(" F[rt = %d][%d]: 0, %d; 1, %d\n", rt, i, F[rt][i][0], F[rt][i][1]);
		if (F[rt][i][0]) { Way(rt, i, 0); break; }
		if (F[rt][i][1]) { Way(rt, i, 1); break; }
	} if (ans) {
		for (int i = 1; i <= n; ++i) putchar(col[i] ? 'B' : 'R');
		putchar('\n');
	} else puts("Impossible");
	return 0;
}

void Way(int u, int i, int c) {
	ans = 1, col[u] = c;
	if (G[u].empty()) return;
	int v = G[u][0];
	if (c && i && F[v][i - 1][0]) Way(v, i - 1, 0);
	else if (c && i && F[v][i - 1][1]) Way(v, i - 1, 1);
	else if (!c && F[v][i][1]) Way(v, i, 1);
	if (SZ(G[u]) > 1) {
		v = G[u][1];
		if (c && i && F[v][i - 1][0]) Way(v, i - 1, 0);
		else if (c && i && F[v][i - 1][1]) Way(v, i - 1, 1);
		else if (!c && F[v][i][1]) Way(v, i, 1);
	}
}

void Dfs(int u) {
	if (G[u].empty()) {
		F[u][0][0] = F[u][1][1] = 1, dep[u] = 1;
		return;
	} dep[u] = n;
	int v, w;
	if (SZ(G[u]) == 1) {
		Dfs(v = G[u][0]); dep[u] = dep[v] + 1;	
		F[u][1][1] = F[v][0][0];
	} else {
		Dfs(v = G[u][0]); Dfs(w = G[u][1]); dep[u] = std::min(dep[v], dep[w]) + 1;
		for (int i = 0; i <= dep[u]; ++i) {
			F[u][i][0] = F[v][i][1] & F[w][i][1];
			if (i) F[u][i][1] = (F[v][i - 1][0] | F[v][i - 1][1]) & (F[w][i - 1][0] | F[w][i - 1][1]);
		}
	}
}
