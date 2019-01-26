// POJ 1741
#include <cstdio>
#include <cstring>
#include <algorithm>

#define forto(_) for (int e = last[_], v; e; e = E[e].next)

const int MAXN = 10010;

int N, K, ans;

void solve();

int main() {
	while (scanf("%d%d", &N, &K) == 2 && N && K) solve();

	return 0;
}

namespace Graph {
	struct Edge {
		int to, cost, next;
	} E[MAXN << 1];

	int tote, last[MAXN];
	int totp, D[MAXN], sz[MAXN], vis[MAXN];

	void init() {
		tote = 0;
		memset(last, 0, sizeof last);
		memset(vis, 0, sizeof vis);
	}
	
	inline void add_edge(int u, int v, int c) {
		E[++tote] = (Edge){v, c, last[u]}, last[u] = tote;
		E[++tote] = (Edge){u, c, last[v]}, last[v] = tote;
	}

	namespace FindCenter {
		int totsz, cntr;

		void dfs(int u, int fa) {
			sz[u] = 1;
			int mxsz = 0;
			forto(u) {
				if (vis[v = E[e].to] || v == fa) continue;
				dfs(v, u);
				mxsz = std::max(mxsz, sz[v]);
				sz[u] += sz[v];
			}
			if (std::max(totsz - sz[u], mxsz) * 2 <= totsz) cntr = u;
		}

		int find(int u, int usz) {
			totsz = usz;
			dfs(u, 0);
			return cntr;
		}
	}

	void dfs(int u, int fa, int dep) {
		D[totp++] = dep;
		forto(u) {
			if (vis[v = E[e].to] || v == fa) continue;
			dfs(v, u, dep + E[e].cost);
		}
	}

	int calc(int u, int d0) {
		totp = 0;
		dfs(u, 0, d0);
		std::sort(D, D + totp);
		int ret = 0;
		for (int i = 0, j = totp - 1; i < totp; i++) {
			while (i < j && D[i] + D[j] > K) --j;
			ret += std::max(0, j - i);
		}
		return ret;
	}

	void ndiv(int u, int usz) {
		u = FindCenter::find(u, usz);
		FindCenter::dfs(u, 0);
		vis[u] = 1;

		ans += calc(u, 0);
		forto(u) {
			if (vis[v = E[e].to]) continue;
			ans -= calc(v, E[e].cost);
			ndiv(v, sz[v]);
		}
	}
}

void solve() {
	Graph::init();

	for (int i = 1, u, v, c; i < N; i++) {
		scanf("%d%d%d", &u, &v, &c);
		Graph::add_edge(u, v, c);
	}

	ans = 0;
	Graph::ndiv(1, N);

	printf("%d\n", ans);
}
