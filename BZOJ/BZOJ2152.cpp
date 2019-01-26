// BZOJ 2152
#include <cstdio>
#include <cstring>
#include <algorithm>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int MAXN = 2e4 + 10;

int N, ans, cnt[3];

namespace Graph {
	struct Edge {
		int to, cost, next;
	} E[MAXN << 1];
	
	int tote, last[MAXN];
	int sz[MAXN], vis[MAXN];

	inline void add_edge(int u, int v, int c) {
		E[++tote] = (Edge){v, c, last[u]}, last[u] = tote;
		E[++tote] = (Edge){u, c, last[v]}, last[v] = tote;
	}

	void ndiv(int, int);
}

int main() {
	scanf("%d", &N);
	for (int i = 1, u, v, c; i < N; i++) {
		scanf("%d%d%d", &u, &v, &c);
		c %= 3;
		Graph::add_edge(u, v, c);
	}

	Graph::ndiv(1, N);
	int g = std::__gcd(ans, N * N);
	printf("%d/%d\n", ans / g, N * N / g);
	return 0;
}

namespace Graph {
	namespace FindCenter {
		int totsz, cntr;

		void dfs(int u, int fa) {
			sz[u] = 1;
			int mxsz = 0;
			forto(u) {
				if (vis[v] || v == fa) continue;
				dfs(v, u);
				mxsz = std::max(mxsz, sz[v]), sz[u] += sz[v];
			}
			if (std::max(mxsz, totsz - sz[u]) * 2 <= totsz) cntr = u;
		}

		int find(int u, int usz) {
			totsz = usz;
			dfs(u, 0);
			return cntr;
		}
	}

	void dfs(int u, int fa, int dep) {
		++cnt[dep];
		forto(u) {
			if (vis[v] || v == fa) continue;
			dfs(v, u, (dep + E[e].cost) % 3);
		}
	}

	int calc(int u, int d0) {
		memset(cnt, 0, sizeof cnt);
		dfs(u, 0, d0);
		return cnt[0] * cnt[0] + 2 * cnt[1] * cnt[2];
	}

	void ndiv(int u, int usz) {
		u = FindCenter::find(u, usz);
		FindCenter::dfs(u, 0);
		vis[u] = 1;

		ans += calc(u, 0);
		forto(u) {
			if (vis[v]) continue;
			ans -= calc(v, E[e].cost);
			ndiv(v, sz[v]);
		}
	}
}
