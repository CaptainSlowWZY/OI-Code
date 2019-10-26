#include <algorithm>
#include <cstdio>

const int kMaxn = 1e5 + 5;

int n, m, k;
int fa[kMaxn << 1], cnt[kMaxn], flag[kMaxn];

inline int Find(int x) { return fa[x] == x ? x : (fa[x] = Find(fa[x])); }
inline void Merge(int x, int y) { fa[Find(x)] = Find(y); }

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n + m; ++i) fa[i] = i;
	for (int u, v; k--; ) {
		scanf("%d%d", &u, &v);
		Merge(u, n + v); ++cnt[v], flag[u] = 1;
	}
	int ans = 0, e = 0;
	for (int i = 1; i <= n + m; ++i) {
		if (!flag[i] && i <= n) { ++ans; continue; }
		if (Find(i) == i && (i <= n || cnt[i - n])) ++e;
	} printf("%d\n", ans + std::max(0, e - 1));
	return 0;
}
