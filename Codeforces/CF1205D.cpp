#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

#define fir first
#define sec second
#define pb push_back

typedef std::pair<int, int> Pii;

const int kMaxn = 1005;

int n, ctr, ctr0;
int sz[kMaxn], fa[kMaxn];
std::vector<int> G[kMaxn];
std::priority_queue<Pii, std::vector<Pii>, std::greater<Pii> > hap;

void Color(int u, int fa, int s, int d);
void Dfs(int u, int fa);
int Find(int x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }
inline bool CmpSz(int a, int b) { return sz[a] < sz[b]; }
inline void Merge(int x, int y) {
	x = Find(x), y = Find(y); fa[x] = y;
}

int main() {
	scanf("%d", &n);
	if (n == 1) return 0;
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		G[u].pb(v), G[v].pb(u);
	}
	Dfs(1, 0);
	ctr = ctr0;
	for (int i = 1; i <= n; i++) fa[i] = i;	
	for (auto v : G[ctr]) {
		Dfs(v, ctr);
		hap.push({sz[v], v});
	}
	while (hap.size() > 2) {
		Pii u = hap.top(); hap.pop();
		Pii v = hap.top(); hap.pop();
		Merge(u.sec, v.sec);
		hap.push({u.fir + v.fir, Find(u.sec)});
	}
	int a = hap.top().sec, sa = hap.top().fir; hap.pop();
	int ca = 1, cb = 1;
	for (auto v : G[ctr]) {
		if (Find(v) == a) {
			Color(v, ctr, ca, 1);
			ca += sz[v];
		} else {
			Color(v, ctr, cb, sa + 1);	
			cb += sz[v];
		}
	}
	return 0;
}

void Color(int u, int fa, int t, int d) {
	printf("%d %d %d\n", u, fa, t * d);
	int s = 1;
	for (auto v : G[u]) {
		if (v == fa) continue;
		Color(v, u, s, d);
		s += sz[v];
	}
}

void Dfs(int u, int fa) {
	sz[u] = 1;
	int maxsz = 0;
	for (auto v : G[u]) {
		if (v == fa) continue;
		Dfs(v, u); sz[u] += sz[v];	
		maxsz = std::max(maxsz, sz[v]);
	}
	if (std::max(maxsz, n - sz[u]) * 2 <= n)
		ctr0 = u;
}
