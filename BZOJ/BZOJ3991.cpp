#include <cstdio>
#include <set>

#define forto(_) for (int e = back[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int kMaxn = 1e5 + 5, kLg = 17;

typedef long long LL;
typedef int IAr[kMaxn];

struct Edge {
	int to, len, next;
} E[kMaxn << 1];

int n, m, tote;
int F[kMaxn][kLg];
IAr dfn, ind, back, dep, col;
LL dis[kMaxn];
std::set<int> S;

inline void AddEdge(int u, int v, int w) {
	E[++tote] = (Edge){v, w, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, w, back[v]}, back[v] = tote;
}
void Dfs(int);
LL Dist(int, int);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, x, y, z; i < n; i++) {
		scanf("%d%d%d", &x, &y, &z);
		AddEdge(x, y, z);
	}

	dep[1] = 1;
	Dfs(1);

	LL ans = 0;
	for (int u, d; m--; ) {
		scanf("%d", &u);
		d = dfn[u];
		if (col[u]) {
			if (S.size() >= 2) {
				if (d == *S.begin()) {
					ans -= Dist(u, ind[*(++S.begin())]);
					ans -= Dist(u, ind[*S.rbegin()]);
					S.erase(d);
					ans += Dist(ind[*S.begin()], ind[*S.rbegin()]);
				} else if (d == *S.rbegin()) {
					ans -= Dist(u, ind[*(++S.rbegin())]);
					ans -= Dist(u, ind[*S.begin()]);
					S.erase(d);
					ans += Dist(ind[*S.begin()], ind[*S.rbegin()]);
				} else {
					std::set<int>::iterator it = S.find(d);
					int prv = ind[*(--it)], nxt;
					ans -= Dist(u, prv);
					++it, nxt = ind[*(++it)];
					ans -= Dist(u, nxt);
					S.erase(d);
					ans += Dist(prv, nxt);
				}
			} else S.erase(d);
		} else {
			if (S.size()) {
				if (d < *S.begin() || d > *S.rbegin()) {
					ans -= Dist(ind[*S.begin()], ind[*S.rbegin()]);
					ans += Dist(ind[*S.begin()], u) + Dist(ind[*S.rbegin()], u);
				} else {
					std::set<int>::iterator it = S.lower_bound(d);
					int nxt = ind[*it], prv = ind[*(--it)];
					ans -= Dist(prv, nxt);
					ans += Dist(prv, u) + Dist(u, nxt);
				}
			}
			S.insert(d);
		}
		col[u] ^= 1;
		printf("%lld\n", ans);
	}

	return 0;
}

void Dfs(int u) {
	static int dfs_clock = 0;
	ind[dfn[u] = ++dfs_clock] = u;
	for (int i = 1; i < kLg && F[u][i - 1]; i++) {
		F[u][i] = F[F[u][i - 1]][i - 1];
	}
	forto(u) {
		if (v == F[u][0]) continue;
		F[v][0] = u, dep[v] = dep[u] + 1;
		dis[v] = dis[u] + E[e].len;
		Dfs(v);
	}
}

LL Dist(int u, int v) {
	if (u == v) return 0;
	int u0 = u, v0 = v;
	if (dep[u] < dep[v]) std::swap(u, v);
	for (int i = 0, del = dep[u] - dep[v];
		(1 << i) <= del; i++) {
		if (del >> i & 1) u = F[u][i];
	}
	int l;
	if (u == v) l = u;
	else {
		for (int i = kLg - 1; i >= 0; i--) {
			if (F[u][i] != F[v][i]) {
				u = F[u][i];
				v = F[v][i];
			}
		}
		l = F[u][0];
	}
	return dis[u0] + dis[v0] - (dis[l] << 1);
}
