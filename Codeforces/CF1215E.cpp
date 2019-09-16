#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

#define PB push_back

typedef long long LL;
typedef std::pair<int, int> Pii;

const LL kInf64 = 0x3f3f3f3f3f3f3f3f;

int n;
LL cost[20][20], DP[1 << 20];
std::vector<int> pos[20], can;

LL Calc(int a, int b);
LL Dfs(int mask);

int main() {
	scanf("%d", &n);
	for (int i = 1, ai; i <= n; i++) {
		scanf("%d", &ai);
		pos[ai - 1].PB(i);
	}
	
	int end = 0;
	for (int i = 0; i < 20; i++) {
		if (pos[i].empty()) continue;
		for (int j = 0; j < 20; j++) {
			if (pos[j].empty()) continue;
			if (i != j) cost[i][j] = Calc(i, j);
		}
		end |= 1 << i, can.PB(i);
	}
	memset(DP, 0x3f, sizeof DP);
	printf("%lld\n", Dfs(end));
	return 0;
}

LL Calc(int a, int b) {
	int ia = 0, ib = 0,
		sa = pos[a].size(), sb = pos[b].size();
	LL res = 0;
	while (ia < sa && ib < sb) {
		if (pos[a][ia] < pos[b][ib]) {
			res += ib; ++ia;
		} else ++ib;
	}
	return res + 1ll * ib * (sa - ia);
}

LL Dfs(int mask) {
	if (!mask) return 0;
	if (DP[mask] != kInf64) return DP[mask];
	for (auto i : can) {
		if (mask >> i & 1 ^ 1) continue;
		LL c = 0;
		for (auto j : can)
			if (mask >> j & 1) c += cost[j][i];
		DP[mask] = std::min(Dfs(mask & ~(1 << i)) + c, DP[mask]);
	}
	return DP[mask];
}
