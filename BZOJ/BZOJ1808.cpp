// BZOJ 1808
// IOI 2007 Training
#include <cstdio>
#include <vector>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif
#define RG register
#define pb push_back

const int MAXN = 1010;
const int MAXM = 5010;
const int Lg_N = 11;

typedef std::vector<int> Vec;
typedef int Arr[MAXN];

struct TEdge {
	int to, next;
} E[MAXN << 1];
struct Edge {
	int u, v, c;
} ee[MAXM];

int N, M, tote, totnt, totc, F[MAXN][Lg_N], DP[MAXN][(1 << 10) + 10];
Arr last, dep, sid;
Vec crs[MAXN];

namespace FastIO {
	template <typename T>
		void read(T & x) {
			RG char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (x = 0; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
}
inline void add_edge(int u, int v) {
	E[++tote] = (TEdge){v, last[u]}, last[u] = tote;
	E[++tote] = (TEdge){u, last[v]}, last[v] = tote;
}
void dfs1(int u);
void dfs2(int u);
int lca(int, int);

int main() {
	using FastIO::read;

	read(N), read(M);
	for (int i = 0, a, b, c; i < M; i++) {
		read(a), read(b), read(c);
		if (!c) add_edge(a, b);
		else ee[totnt++] = (Edge){a, b, c}, totc += c;
	}

	dfs1(1);

	for (int i = 0; i < totnt; i++) {
		Edge & e = ee[i];
		int l = lca(e.u, e.v), len = dep[e.u] + dep[e.v] - (dep[l] << 1);
		if (len & 1 ^ 1) crs[l].pb(i);
	}
	dfs2(1);

	printf("%d\n", totc - DP[1][0]);
	return 0;
}

void dfs1(int u) {
	for (int i = 1; i < Lg_N && F[u][i - 1]; i++) F[u][i] = F[F[u][i - 1]][i - 1];
	for (int v, e = last[u]; e; e = E[e].next) {
		if ((v = E[e].to) == F[u][0]) continue;
		dep[v] = dep[u] + 1, F[v][0] = u;
		dfs1(v);
	}
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) std::swap(u, v);
	for (int i = 0, delta = dep[u] - dep[v]; i < Lg_N && (1 << i) <= delta; i++)
		if (delta >> i & 1) u = F[u][i];
	if (u == v) return u;
	for (int i = Lg_N - 1; i >= 0; i--)
		if (F[u][i] != F[v][i]) u = F[u][i], v = F[v][i];
	return F[u][0];
}

void dfs2(int u) {
	Vec son;
	for (int v, e = last[u]; e; e = E[e].next) {
		if ((v = E[e].to) == F[u][0]) continue;
		dfs2(v);
		son.pb(v);
	}
	int totson = son.size();
	for (int i = 0; i < totson; i++) sid[son[i]] = i;
	for (int mask = (1 << totson) - 1; mask >= 0; --mask) {
		for (int i = 0; i < totson; i++)
			if (mask >> i & 1 ^ 1) DP[u][mask] += DP[son[i]][0];
	}
	for (Vec::iterator it = crs[u].begin(); it != crs[u].end(); ++it) {
		int x = ee[*it].u, y = ee[*it].v, ret = ee[*it].c, 
			s1id = sid[x], s2id = sid[y];
		if (x != u) {
			ret += DP[x][0];
			for (; F[x][0] != u; x = F[x][0]) ret += DP[F[x][0]][1 << sid[x]];
			if (F[x][0] == u) s1id = sid[x];
		}
		if (y != u) {
			ret += DP[y][0];
			for (; F[y][0] != u; y = F[y][0]) ret += DP[F[y][0]][1 << sid[y]];
			if (F[y][0] == u) s2id = sid[y];
		}
		x = ee[*it].u, y = ee[*it].v;
		for (int mask = 0, lmt = 1 << totson; mask < lmt; ++mask) {
			int prf = mask;
			if (x ^ u) {
				if (mask >> s1id & 1) continue;
				prf |= 1 << s1id;
			}
			if (y ^ u) {
				if (mask >> s2id & 1) continue;
				prf |= 1 << s2id;
			}
			DP[u][mask] = std::max(DP[u][mask], DP[u][prf] + ret);
		}
	}
}

// AC!!!
