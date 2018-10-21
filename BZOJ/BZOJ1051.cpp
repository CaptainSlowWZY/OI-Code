// BZOJ 1051
#include <cstdio>
#include <algorithm>
#include <stack>

const int MAXN = 1e4 + 5;
const int MAXM = 5e4 + 5;

typedef int IntAr[MAXN];

struct Edge {
	int to, next;
} E[MAXM];

int N, M, tote, dfs_clock, scc;
IntAr last, dfn, low, col, odgr, size;
std::stack<int> stk;

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
}
void dfs(int u);

int main() {
	using FastIO::read;
	read(N), read(M);
	for (int i = 0, ai, bi; i < M; i++) {
		read(ai), read(bi);
		add_edge(ai, bi);
	}
	for (int i = 1; i <= N; i++)
		if (!dfn[i]) dfs(i);
	for (int i = 1; i <= N; i++)
		for (int v, e = last[i]; e; e = E[e].next)
			if (col[i] ^ col[v = E[e].to]) ++odgr[col[i]];
	int ans = 0;
	for (int i = 1; i <= scc; i++)
		if (!odgr[i]) {
			if (ans) return puts("0"), 0;
			ans = size[i];
		}
	printf("%d\n", ans);
	return 0;
}

void dfs(int u) {
	stk.push(u), dfn[u] = low[u] = ++dfs_clock;
	for (int v, e = last[u]; e; e = E[e].next) {
		if (!dfn[v = E[e].to]) {
			dfs(v);
			low[u] = std::min(low[u], low[v]);
		}
		else if (!col[v]) low[u] = std::min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		++scc;
		for (; !stk.empty(); stk.pop()) {
			++size[scc], col[stk.top()] = scc;
			if (stk.top() == u) { stk.pop(); break; }
		}
	}
}

// AC!!!
