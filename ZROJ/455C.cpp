#include <algorithm>
#include <cstdio>
#include <cstring>

int n;
int val[100005], cnt[16], DP[(1 << 16) + 5];

int Dfs(int s);

int main() {
	scanf("%d", &n);
	for (int x, y, z, i = 1; i < n; ++i) {
		scanf("%d%d%d", &x, &y, &z);
		val[x] ^= z; val[y] ^= z;
	}
	for (int i = 1; i <= n; ++i)
		++cnt[val[i]];
	memset(DP, 0xff, sizeof DP);
	int ans = n - cnt[0], u = 0;
	for (int i = 1; i < 16; ++i) {
		ans -= cnt[i] >> 1;
		u |= (cnt[i] & 1) << i - 1;
	} printf("%d\n", ans - Dfs(u));
	return 0;
}

int Dfs(int s) {
	if (!s) return DP[s] = 0;
	if (~DP[s]) return DP[s];
	for (int t = s; t; t = t - 1 & s) {
		int _xor = 0;
		for (int i = 0; i < 16; ++i)
			if (t >> i & 1) _xor ^= i + 1;
		if (!t || _xor) continue;
		DP[s] = std::max(DP[s], Dfs(s ^ t) + 1);
	}
	return DP[s];
}
