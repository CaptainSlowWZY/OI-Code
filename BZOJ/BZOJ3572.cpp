// BZOJ 3572
// HNOI 2014
#include <cstdio>
#include <cstring>
#include <algorithm>

#ifdef DEBUG
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif
#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int MAXN = 3e5 + 5, Lg_N = 19, INF = 0x3f3f3f3f;

typedef int IntAr[MAXN];

struct Edge {
	int to, cost, next;
} E[MAXN << 1];

int N, Q, CS, tote, dfs_clock, F[MAXN][Lg_N + 2];
IntAr last, dep, C, D, S, H, H0, ans, tag, sz, dfn;

void dfs(int u);
void dfs_up(int u);
void dfs_dn(int u);
void dfs_vt(int u);
int lca(int u, int v);
inline bool cmp(int u, int v) {
	return dfn[u] < dfn[v];
}
inline int dist(int u, int v) {
	return dep[u] + dep[v] - dep[lca(u, v)] * 2;
}
inline void add_edge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, last[u]}, last[u] = tote;
}
inline void add_vte(int u, int v) {
	debug(" add : %d -> %d, cost = %d\n", u, v, dist(u, v));
	add_edge(u, v, dist(u, v));
}
inline void init_G() {
	tote = 0;
	memset(last, 0, sizeof last);
}

int main() {
	scanf("%d", &N);
//	init_G();
	for (int i = 1, u, v; i < N; i++) {
		scanf("%d%d", &u, &v);	
		add_edge(u, v, 1);
		add_edge(v, u, 1);
	}

	dep[1] = 1;
	dfs(1);

	scanf("%d", &Q);
	int M;
	for (CS = 1; CS <= Q; CS++) {
		scanf("%d", &M);
		for (int i = 0; i < M; i++) {
			scanf("%d", H + i);
			tag[H[i]] = CS;
			ans[H[i]] = 0;
		}
		memcpy(H0, H, sizeof(int) * (M));

	//	build virtual tree
		std::sort(H, H + M, cmp);
		init_G();
		int top = 0;
		S[top++] = 1;
		for (int i = 0; i < M; i++) {
			int l = lca(S[top - 1], H[i]);
			while (dfn[l] < dfn[S[top - 1]]) {
				if (dfn[l] >= dfn[S[top - 2]]) break;
				add_vte(S[top - 2], S[top - 1]);
				l = lca(S[--top - 1], H[i]);
			}
			if (dfn[l] < dfn[S[top - 1]]) {
				int lst = S[--top];
				if (l != S[top - 1]) S[top++] = l;
				add_vte(S[top - 1], lst);
			}
			if (S[top - 1] != H[i]) S[top++] = H[i];
		}
		for (; top > 1; --top) add_vte(S[top - 2], S[top - 1]);

	//	find the closest taged vertex
		dfs_up(1);
		dfs_dn(1);
		dfs_vt(1);

		for (int i = 0; i < M; i++) printf("%d ", ans[H0[i]]);
		putchar('\n');
	}

	return 0;
}

void upd(int u, int v, int dis) {
	if (D[v] + dis < D[u] || D[v] + dis == D[u] && C[v] < C[u]) {
		D[u] = D[v] + dis;
		C[u] = C[v];
	}
}
// dfs on virtual tree
// update up
void dfs_up(int u) {
	if (tag[u] == CS) C[u] = u, D[u] = 0;
	else C[u] = -1, D[u] = INF;
	forto(u) {
		dfs_up(v);	
		upd(u, v, E[e].cost);
	}
}
// update down
void dfs_dn(int u) {
	forto(u) {
		upd(v, u, E[e].cost);
		dfs_dn(v);
	}
#ifdef DEBUG
	debug(" Close to %d : %d, dist = %d\n", u, C[u], D[u]);
#endif
}

int find(int up, int low) {
	if (C[up] == C[low]) return low;
	int v = low, d = -dist(up, C[up]) + dist(low, C[low]) + dep[low] + dep[up];
	debug(" find from %d to %d's path, len = %d, d = %d\n", low, up, d - 2 * dep[up], d);
	for (int i = Lg_N; i >= 0; --i) {
		if ((1 << i) > dep[low] - dep[up]) continue;
		if ((dep[F[v][i]] << 1) > d) v = F[v][i];
	}
	debug(" ---now v = %d\n", v);
	if ((dep[F[v][0]] << 1) == d && C[up] > C[low]) v = F[v][0];
	debug(" --then v = %d\n", v);
	return v;
}

int son(int u, int from) {
	for (int del = dep[from] - dep[u] - 1, i = 0; i <= Lg_N && (1 << i) <= del; ++i)
		if (del >> i & 1) from = F[from][i];
	return from;
}
// get ans
void dfs_vt(int u) {
	int tots = 0, rem = sz[u];
	forto(u) {
		++tots;
		int t = find(u, v), sn;
		debug(" u %d -> v %d, t %d\n", u, v, t);
		if (dep[t] <= dep[u]) t = son(u, v);
		ans[C[v]] += sz[t] - sz[v];
		ans[C[u]] += sz[sn = son(u, t)] - sz[t];
		rem -= sz[sn];
		dfs_vt(v);
	}
	ans[C[u]] += rem;
}

void dfs(int u) {
	dfn[u] = ++dfs_clock, sz[u] = 1;
	for (int i = 1; i <= Lg_N && F[u][i - 1]; i++) F[u][i] = F[F[u][i - 1]][i - 1];
	forto(u) {
		if (v == F[u][0]) continue;
		F[v][0] = u, dep[v] = dep[u] + E[e].cost;
		dfs(v);
		sz[u] += sz[v];
	}
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) std::swap(u, v);
	for (int i = 0, del = dep[u] - dep[v]; i <= Lg_N && (1 << i) <= del; i++)
		if (del >> i & 1) u = F[u][i];
	if (u == v) return u;
	for (int i = Lg_N; i >= 0; i--)
		if (F[u][i] != F[v][i]) u = F[u][i], v = F[v][i];
	return F[u][0];
}
