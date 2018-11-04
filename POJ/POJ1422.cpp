// POJ 1422
#include <cstdio>
#include <cstring>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif

const int MAXN = 125;
const int MAXE = 60 * 119 + 10;

struct Edge {
	int to, next;
} E[MAXE];

int N, M, tote, last[MAXN], match[MAXN], vis[MAXN];

void solve();

int main() {
	int t;
	for (scanf("%d", &t); t--; ) solve();
	return 0;
}

bool dfs(int u) {
	for (int v, e = last[u]; e; e = E[e].next) {
		if (vis[v = E[e].to]) continue;
		vis[v] = 1;
		if (match[v] == -1 || dfs(match[v])) {
			match[v] = u;
			return true;
		}
	}
	return false;
}

inline void add_edge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
}

void solve() {
	tote = 0;
	memset(last, 0, sizeof last);
	memset(match, 0xff, sizeof match);

	scanf("%d%d", &N, &M);
	for (int i = 0, xi, yi; i < M; i++) {
		scanf("%d%d", &xi, &yi);
		add_edge(xi, yi);
	}

	int ans = N;
	for (int i = 1; i <= N; i++) {
		memset(vis, 0, sizeof vis);
		if (dfs(i)) --ans;
	}

#ifdef DEBUG_MD
	for (int i = 1; i <= N; i++) debug(" %d --match-> %d\n", i, match[i]);
#endif

	printf("%d\n", ans);
}
