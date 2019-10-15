// also see UVa 1670
#include <algorithm>
#include <cstdio>
#include <vector>

#define fir first
#define sec second
#define pch putchar
#define pb push_back
#define SZ(_) (int)_.size()

typedef std::pair<int, int> Pii;
typedef std::vector<int> Vi;

const int kMaxn = 1e5 + 5;

int n, rt;
int deg[kMaxn];
Vi G[kMaxn], L;
std::vector<Pii> ans;

void Dfs(int, int);

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; ++i) {
			G[i].clear(); deg[i] = 0;
		}
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].pb(v); G[v].pb(u);
			++deg[u], ++deg[v];
		} rt = -1;
		for (int i = 1; i <= n; ++i) {
			if (deg[i] > 1) rt = i;
		}
		if (rt == -1) {
			for (int i = 1; i <= n; ++i) {
				if (deg[i] == 1) printf("%d ", i);
			} pch('\n'); continue;
		} ans.clear(); L.clear(); Dfs(rt, 0);
		if (SZ(L) == 1) ans.pb({rt, L[0]});
		if (SZ(L) == 2) ans.pb({L[0], L[1]});
		printf("%d\n", SZ(ans));
		for (auto & p : ans) printf("%d %d\n", p.fir, p.sec);
	} return 0;
}

void Dfs(int u, int fa) {
	for (auto v : G[u]) {
		if (v == fa) continue;
		Dfs(v, u);
	}
	if (deg[u] == 1) {
		L.pb(u);
		if (SZ(L) == 3) {
			std::swap(L[0], L[1]);
			ans.pb({L[1], L[2]});
			L.pop_back(); L.pop_back();
		}
	}
}
