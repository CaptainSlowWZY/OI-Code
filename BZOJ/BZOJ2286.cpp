// BZOJ 2286
// SDOI 2011
#include <cstdio>
#include <algorithm>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif
#define rg register
#define gch getchar
#define pch putchar
#define forto(_) for (rg int v, e = last[_]; e; e = E[e].next)

const int MAXN = 250010;
const int Lg_N = 18;
const int INF = 0x7f7f7f7f;

typedef long long LL;
typedef int Arr[MAXN];

struct Edge {
	int to, cost, next;
} E[MAXN << 1];

int N, M, tote, top, dfs_clock, h[MAXN << 1], vt[MAXN << 2], F[MAXN][Lg_N], MC[MAXN][Lg_N];
Arr last, dep, impt, dfn;
LL DP[MAXN];

namespace FastIO {
	template <typename T>
		void read(T & x);
	template <typename T>
		void write(T x);
	template <typename T>
		inline void writeln(T x) {
			write(x), pch('\n');
		}
}
void dfs(int u);
int lca(int u, int v);
int query(int lw, int up);
LL calc_dp(int u, int vfa) {
	LL ret = impt[u] ? query(u, vfa) : std::min((LL)query(u, vfa), DP[u]);
	DP[u] = 0;
	return ret;
}
inline void add_edge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, c, last[v]}, last[v] = tote;
}
inline bool cmp_h(int h1, int h2) {
	return dfn[h1] < dfn[h2];
}

void print_sp(int t) {
#ifdef DEBUG_MD
	for (; t--; ) debug("%c", ' ');
#endif
}
void vt_DEBUG(int t) {
#ifdef DEBUG_MD
	print_sp(t), debug(" Virtual Tree: (top -> bottem)%c", '\n');
	for (int i = top - 1; i >= 0; i--) print_sp(t + 2), debug(" vertex: %d, dep=%d, dfn=%d\n", vt[i], dep[vt[i]], dfn[vt[i]]);
	print_sp(t), debug(" -----   END   -----%c", '\n');
#endif
}

int main() {
	using FastIO::read;
	
	read(N);
	for (int x, y, z, i = 1; i < N; i++) {
		read(x), read(y), read(z);
		add_edge(x, y, z);
	}
	dfs(1);

	read(M);
	for (int ki, cs = 0; cs < M; cs++) {
		read(ki);
		for (int i = 0; i < ki; i++) {
			read(h[i]);
			impt[h[i]] = 1;
		}
		debug(" CASE %d\n", cs);

		std::sort(h, h + ki, cmp_h);
		DP[vt[0] = top = 1] = 0;	// DP[u] - min cost to cut subtree u from u's father
		for (int i = 0; i < ki; i++) {
			print_sp(2), debug(" insert: %d\n", h[i]);
			vt_DEBUG(4);
			int l0 = lca(vt[top - 1], h[i]);
			while (dfn[l0] < dfn[vt[top - 1]]) {
				print_sp(4), debug(" top=%d; l0=%d, dfn=%d; vt[top - 1]=%d, dfn=%d; vt[top - 2]=%d, dfn=%d\n", top, l0, dfn[l0], vt[top - 1], dfn[vt[top - 1]], vt[top - 2], dfn[vt[top - 2]]);
				if (dfn[l0] >= dfn[vt[top - 2]]) break;
				if (!impt[vt[top - 2]]) DP[vt[top - 2]] += calc_dp(vt[top - 1], vt[top - 2]);
				else calc_dp(vt[top - 1], vt[top - 2]);
				l0 = lca(vt[--top - 1], h[i]);
			}
			// the lca may not in VT
			if (dfn[l0] < dfn[vt[top - 1]]) {	
				int lst = vt[--top];
				if (l0 ^ vt[top - 1]) vt[top++] = l0;
				if (!impt[vt[top - 1]]) DP[vt[top - 1]] += calc_dp(lst, vt[top - 1]);
			}
			if (vt[top - 1] ^ h[i]) vt[top++] = h[i];
		}
		vt_DEBUG(2);
		for (; top > 1; --top)
			if (!impt[vt[top - 2]]) DP[vt[top - 2]] += calc_dp(vt[top - 1], vt[top - 2]);
			else calc_dp(vt[top - 1], vt[top - 2]);
		
		FastIO::writeln(DP[1]);

		DP[1] = 0;
		for (int i = 0; i < ki; i++) impt[h[i]] = 0;
	}

	return 0;
}

void dfs(int u) {
	dfn[u] = ++dfs_clock;
	for (int i = 1; i < Lg_N && F[u][i - 1]; i++) {
		F[u][i] = F[F[u][i - 1]][i - 1];
		MC[u][i] = std::min(MC[u][i - 1], MC[F[u][i - 1]][i - 1]);
	}
	forto(u) {
		if ((v = E[e].to) == F[u][0]) continue;
		F[v][0] = u, dep[v] = dep[u] + 1, MC[v][0] = E[e].cost;
		dfs(v);
	}
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) std::swap(u, v);
	for (int i = 0, d = dep[u] - dep[v]; i < Lg_N && (1 << i) <= d; i++)
		if (d >> i & 1) u = F[u][i];
	if (u == v) return u;
	for (int i = Lg_N - 1; i >= 0; i--)
		if (F[u][i] ^ F[v][i]) u = F[u][i], v = F[v][i];
	return F[u][0];
}

int query(int lw, int up) {
	int ret = INF;
	for (int i = 0, d = dep[lw] - dep[up]; i < Lg_N && (1 << i) <= d; i++)
		if (d >> i & 1) {
			ret = std::min(ret, MC[lw][i]);
			lw = F[lw][i];
		}
	return ret;
}

namespace FastIO {
	template <typename T>
		void read(T & x) {
			rg char ch = gch();
			for (; ch < '0' || ch > '9'; ch = gch());
			for (x = 0; ch >= '0' && ch <= '9'; ch = gch()) x = (x << 3) + (x << 1) + (ch ^ '0');
		}
	template <typename T>
		void write(T x) {
			if (!x) return (void)pch('0');
			if (x < 0) x = -x, pch('-');
			rg int arr[20], len = 0;
			for (; x; x /= 10) arr[len++] = x % 10;
			while (len) pch(arr[--len] ^ '0');
		}
}
