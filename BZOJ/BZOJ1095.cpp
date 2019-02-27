// BZOJ 1095
// ZJOI 2007
#include <cstdio>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <cassert>

#define forto(__, _) for (int e = __.last[_], v = __.E[e].to; e; v = __.E[e = __.E[e].next].to)
#ifdef DEBUG
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif

const int MAXN = 1e5 + 10, Lg_N = 19;

typedef int IntAr[MAXN];

struct Myset {
	std::priority_queue<int> h, tg;

	void insert(int v_) { ~v_ ? h.push(v_) : (void)0; }
	void erase(int v_) { ~v_ ? tg.push(v_) : (void)0; }
	int top() {
		for (; !h.empty() && !tg.empty() && h.top() == tg.top(); h.pop(), tg.pop());
		return h.empty() ? -1 : h.top();
	}
	int stop() {
		int tp = top();
		if (h.empty()) return -1;
		else h.pop();
		int ret = top();
		h.push(tp);
		return ret;
	}
	bool empty() {
		for (; !h.empty() && !tg.empty() && h.top() == tg.top(); h.pop(), tg.pop());
		return h.empty();
	}
} deps[MAXN], subv[MAXN], ans;
struct Graph {
	struct Edge {
		int to, next;
	} E[MAXN << 1];
	int tote, last[MAXN];

	void adde(int u, int v) {
		E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	}
} OT, T;

int N, Q, totsz, totoff, dfs_clock, cntr, GCNTR, pow[Lg_N], ST[MAXN << 1][Lg_N], Log[MAXN << 1];
IntAr dfn, idfn, odfn, id, stat, fa, sz, mxsz, vis, dep;
char IN[5];

void dfsot(int u);
int dist(int u, int v);
void dfs(int u);
void fcntr(int u, int fa);
void rebuild(int u);

int main() {
	scanf("%d", &N);
	for (int i = 1, u, v; i < N; i++) {
		scanf("%d%d", &u, &v);
		OT.adde(u, v), OT.adde(v, u);
	}

	dep[1] = 1;
	dfsot(1);
	pow[0] = 1, Log[0] = -1;
	for (int i = 1; i < Lg_N; i++) pow[i] = pow[i - 1] << 1;
	for (int i = 1; i <= dfs_clock; i++) Log[i] = Log[i >> 1] + 1;
	for (int i = 1; i <= Log[dfs_clock]; i++)
		for (int j = 1; j + pow[i] - 1 <= dfs_clock; j++)
			ST[j][i] = std::min(ST[j][i - 1], ST[j + pow[i - 1]][i - 1]);
	totsz = totoff = N, cntr = dfs_clock = 0;
	fcntr(1, 0);
	GCNTR = cntr, fa[GCNTR] = 0;
	rebuild(GCNTR);
	dfs(GCNTR);
	for (int i = 1; i <= N; i++) {
		stat[i] = 1;
		if (i == GCNTR) continue;
		for (int j = idfn[i]; j <= odfn[i]; j++) {
			deps[i].insert(dist(id[j], fa[i]));
		}
	}
	for (int i = 1, tp; i <= N; i++) {
		if ((tp = deps[i].top()) == -1) continue;
		subv[fa[i]].insert(tp);
	}
	for (int i = 1, tp1, tp2; i <= N; i++) {
		if ((tp1 = subv[i].top()) == -1) continue;
		if ((tp2 = subv[i].stop()) == -1) continue;
		ans.insert(tp1 + tp2);
	}

	scanf("%d", &Q);
	for (int u; Q--; ) {
		scanf("%s", IN);
		if (IN[0] == 'C') {
			scanf("%d", &u);
			int u0 = u;
			for (int f, tp1, tp2; fa[u]; u = fa[u]) {
				f = fa[u];
				tp1 = subv[f].top(), tp2 = subv[f].stop();
				if (~tp1 && ~tp2) ans.erase(tp1 + tp2);
				subv[f].erase(deps[u].top());
				if (stat[u0]) deps[u].erase(dist(u0, fa[u]));
				else deps[u].insert(dist(u0, fa[u]));
				subv[f].insert(deps[u].top());
				tp1 = subv[f].top(), tp2 = subv[f].stop();
				if (~tp1 && ~tp2) ans.insert(tp1 + tp2);
			}
			stat[u0] ? ++totoff : --totoff;
			stat[u0] ^= 1;
		}
		else printf("%d\n", !totoff ? -1 : (ans.empty() ? 0 : ans.top()));
	}

	return 0;
}

void dfsot(int u) {
	ST[dfn[u] = ++dfs_clock][0] = dep[u];
	forto(OT, u) {
		if (v == fa[u]) continue;
		dep[v] = dep[u] + 1, fa[v] = u;
		dfsot(v);
		ST[++dfs_clock][0] = dep[u];
	}
}

int dist(int u, int v) {
	if (dfn[u] > dfn[v]) std::swap(u, v);
	int lg = Log[dfn[v] - dfn[u] + 1];
	return dep[u] + dep[v] - (std::min(ST[dfn[u]][lg], ST[dfn[v] - pow[lg] + 1][lg]) << 1);
}

void dfs(int u) {
	id[idfn[u] = ++dfs_clock] = u;
	forto(T, u) {
		dfs(v);
	}
	odfn[u] = dfs_clock;
}

void fcntr(int u, int fa) {
	sz[u] = 1, mxsz[u] = 0;
	forto(OT, u) {
		if (v == fa || vis[v]) continue;
		fcntr(v, u);
		sz[u] += sz[v];
		mxsz[u] = std::max(mxsz[u], sz[v]);
	}
	mxsz[u] = std::max(mxsz[u], totsz - sz[u]);
	if (!cntr || mxsz[u] < mxsz[cntr]) cntr = u;
}

void rebuild(int u) {
	vis[u] = 1;
	forto(OT, u) {
		if (vis[v]) continue;
		totsz = sz[v], cntr = 0;
		fcntr(v, u);
		T.adde(u, cntr);
		fa[cntr] = u;
		rebuild(cntr);
	}
}
