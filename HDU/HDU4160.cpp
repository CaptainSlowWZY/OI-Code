// HDU 4160
#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 505;

struct Doll {
	int wi, li, hi;
	bool operator<(const Doll & d) const {
		return wi < d.wi && li < d.li && hi < d.hi;
	}
} A[MAXN];

int N, vis[MAXN], match[MAXN];

void solve();

int main() {
	while (~scanf("%d", &N) && N) solve();
	return 0;
}

bool dfs(int u) {
	for (int v = u + 1; v < N; v++)
		if (A[u] < A[v]) {
			if (vis[v]) continue;
			vis[v] = 1;
			if (match[v] == -1 || dfs(match[v])) {
				match[v] = u;
				return true;
			}
		}
	return false;
}

inline bool cmp(const Doll & a, const Doll & b) {
	return a.wi < b.wi;
}

void solve() {
	for (int i = 0; i < N; i++) scanf("%d%d%d", &A[i].wi, &A[i].li, &A[i].hi);

	std::sort(A, A + N, cmp);
	memset(match, 0xff, sizeof match);
	int ans = N;
	for (int i = 0; i < N; i++) {
		memset(vis, 0, sizeof vis);
		if (dfs(i)) --ans;
	}	

	printf("%d\n", ans);
}

// AC!!!
