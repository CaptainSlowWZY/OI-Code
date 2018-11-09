#pragma GCC diagnostic error "-std=c++11"
#include <cstdio>
#include <utility>
#include <vector>

#define fir first
#define sec second
#define pb push_back

typedef long long LL;
typedef std::pair<LL, LL> Pll;

const int DX[] = {-1, 1, 0, 0};
const int DY[] = {0, 0, -1, 1};

int N, dgr[35];
std::vector<int> G[35];
Pll pos[35];

void dfs(int u, int fa, Pll pu, LL elen, int invl);

int main() {
	scanf("%d", &N);
	for (int i = 1, ui, vi; i < N; i++) {
		scanf("%d%d", &ui, &vi);
		G[ui].pb(vi), G[vi].pb(ui);
		++dgr[ui], ++dgr[vi];
	}

	for (int i = 1; i <= N; i++)
		if (dgr[i] > 4) return puts("NO"), 0;

	dfs(1, 0, Pll(0, 0), (LL)1e12, -1);

	puts("YES");
	for (int i = 1; i <= N; i++) printf("%lld %lld\n", pos[i].fir, pos[i].sec);
	return 0;
}

void dfs(int u, int fa, Pll pu, LL elen, int invl) {
	pos[u] = pu;
	int i = -1;
	for (auto v : G[u]) {
		if (v == fa) continue;
		if (++i == invl) ++i;
		dfs(v, u, Pll(pu.fir + DX[i] * elen, pu.sec + DY[i] * elen), elen / 3, i ^ 1);
	}
}
