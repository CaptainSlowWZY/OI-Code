#include <cstdio>
#include <vector>

const int kMaxn = 1e5 + 10, kLg = 18;

int n, k;
int F[kMaxn][kLg], dep[kMaxn], tag[kMaxn];
std::vector<int> G[kMaxn];

void Dfs(int u);
int Climb(int u, int d);
int GetAns(int u);

int main() {
	scanf("%d%d", &n, &k);
	for (int u, v, i = 1; i < n; i++) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v), G[v].push_back(u);
	} Dfs(1);
	for (int v, i = 2; i <= n; i++) {
		v = Climb(i, k);
		--tag[F[v][0]], ++tag[F[i][0]];
	}
	GetAns(1);
	for (int i = 1; i <= n; i++) printf("%d\n", tag[i]);
	return 0;
}

int GetAns(int u) {
	for (auto v : G[u]) {
		if (v == F[u][0]) continue;
		tag[u] += GetAns(v);
	} return tag[u];
}

int Climb(int u, int d) {
	d = std::min(d, dep[u]);
	for (int i = kLg - 1; i >= 0; i--) {
		if (d >> i & 1 && F[u][i]) u = F[u][i];
	} return u;
}

void Dfs(int u) {
	for (int i = 1; i < kLg && F[u][i - 1]; i++)
		F[u][i] = F[F[u][i - 1]][i - 1];
	for (auto v : G[u]) {
		if (v == F[u][0]) continue;
		F[v][0] = u, dep[v] = dep[u] + 1;
		Dfs(v);
	}
}
