// aising 2019 E Attack to a Tree
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define pb push_back

typedef long long LL;

const int MAXN = 5010;

int N, A[MAXN], sz[MAXN];
LL DP[MAXN][MAXN][2], INVALID;
std::vector<int> G[MAXN];

inline void upd_min(LL & x, LL y) { y < x ? x = y : 0; }
void dfs(int, int);

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d", A + i);
	for (int i = 1, ui, vi; i < N; i++) {
		scanf("%d%d", &ui, &vi);
		--ui, --vi;
		G[ui].pb(vi), G[vi].pb(ui);
	}

	memset(DP, 0x3f, sizeof DP);
	INVALID = DP[0][0][0];
	dfs(0, -1);
	for (int i = 0; i < N; i++)
		if (DP[0][i][0] != INVALID || DP[0][i][1] < 0) {
			printf("%d\n", i);
			return 0;
		}

	return 0;
}

void dfs(int u, int fa) {
	sz[u] = 1;
	DP[u][0][A[u] > 0 ? 0 : 1] = A[u];
	/* DP[u][j][0 / 1] - u is root, disconnect j cable(s), 
	 * whether there's a computer in the connected component
	 * 0 - no, 1 - yes
	 */
	LL (*nxt)[2] = DP[5005];
	for (auto v : G[u]) {
		if (v == fa) continue;
		dfs(v, u);

		for (int i = 0; i < MAXN; i++) nxt[i][0] = nxt[i][1] = INVALID;
		for (int i = 0; i < sz[u]; i++)
			for (int j = 0; j < sz[v]; j++) {
				// let v be alone
				if (DP[v][j][0] != INVALID || DP[v][j][1] < 0) {
					upd_min(nxt[i + j + 1][0], DP[u][i][0]);
					upd_min(nxt[i + j + 1][1], DP[u][i][1]);
				}
				for (int su = 0; su <= 1; su++)
					for (int sv = 0; sv <= 1; sv++)
						if (DP[u][i][su] != INVALID && DP[v][j][sv] != INVALID)
							upd_min(nxt[i + j][su | sv], DP[u][i][su] + DP[v][j][sv]);
			}
		for (int i = 0; i < MAXN; i++) {
			DP[u][i][0] = nxt[i][0];
			DP[u][i][1] = nxt[i][1];
		}
		sz[u] += sz[v];
	}
}
