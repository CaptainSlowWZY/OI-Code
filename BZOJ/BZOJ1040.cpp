// BZOJ 1040 (ZJ0I 2008)
#include <cstdio>
#include <algorithm>

// #define _DEBUG_MD_

typedef long long LL;
const int MAXN = 1e6 + 10;
struct Edge {
	int to, next, tag;
} E[MAXN << 1];

int N, val[MAXN], last[MAXN], tote, vis[MAXN], u0, v0, gotlp;
LL DP[MAXN][2];

namespace FastIO {
	template <typename T>
	void read(T & x) {
		x = 0; register char ch = getchar();
		for (; ch < '0' || ch > '9'; ch = getchar());
		for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
	}
}
inline void add_edge(int u, int v) {
	E[++tote].to = v, E[tote].next = last[u], last[u] = tote;
	E[++tote].to = u, E[tote].next = last[v], last[v] = tote;
}
void dfs1(int u, int fa);
void dfs2(int u, int fa);

int main() {
	using FastIO::read;
	read(N);
	tote = 1;
	for (int i = 1, ht; i <= N; i++) {
		read(val[i]), read(ht);
		add_edge(i, ht);
	}
	LL ans = 0;
	for (int i = 1; i <= N; i++)
		if (!vis[i]) {

#ifdef _DEBUG_MD_
			printf("i=%d\n", i);
#endif

			gotlp = 0;
			dfs1(i, 0);

#ifdef _DEBUG_MD_
			puts("dfs1 finished.");
#endif

			if (!gotlp) {
				dfs2(i, 0);

#ifdef _DEBUG_MD_
				puts("TREE & dfs2 finished.");
#endif

				ans += std::max(DP[i][0], DP[i][1]);
				continue;
			}
			dfs2(u0, 0);

#ifdef _DEBUG_MD_
				puts("TREE with loop & dfs2-turn1 finished.");
#endif

			LL tmp = DP[u0][0];
			dfs2(v0, 0);

#ifdef _DEBUG_MD_
				puts("TREE with loop & dfs3-turn1 finished.");
#endif

			ans += std::max(DP[v0][0], tmp);
		}
	printf("%lld\n", ans);
	return 0;
}

void dfs1(int u, int fa) {
	vis[u] = 1;
	for (int v, e = last[u]; e; e = E[e].next)
		if ((v = E[e].to) != fa) {
			if (vis[v]) {

#ifdef _DEBUG_MD_
				printf("FIND loop! u: %d, v: %d\n", u, v);
#endif

				E[e].tag = E[e ^ 1].tag = 1;
				u0 = u, v0 = v;
				gotlp = 1;
				continue;
			}
			dfs1(v, u);
		}
}

void dfs2(int u, int fa) {
	DP[u][0] = 0, DP[u][1] = val[u];
	for (int v, e = last[u]; e; e = E[e].next)
		if ((v = E[e].to) != fa && !E[e].tag) {
			dfs2(v, u);
			DP[u][0] += std::max(DP[v][0], DP[v][1]);
			DP[u][1] += DP[v][0];
		}
}
