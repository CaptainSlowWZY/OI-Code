// Luogu P2664
#include <cstdio>
#include <algorithm>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int MAXN = 1e5 + 10;

typedef long long LL;
typedef int IntArr[MAXN];
typedef LL LLArr[MAXN];

int N;
IntArr C;
LLArr sum;

namespace Graph {
	struct Edge {
		int to, next;
	} E[MAXN << 1];

	int tote, last[MAXN];

	inline void add_edge(int u, int v) {
		E[++tote] = (Edge){v, last[u]}, last[u] = tote;
		E[++tote] = (Edge){u, last[v]}, last[v] = tote;
	}
	void Div(int, int);
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) scanf("%d", C + i);
	for (int i = 1, u, v; i < N; i++) {
		scanf("%d%d", &u, &v);
		Graph::add_edge(u, v);
	}

	Graph::Div(1, N);

	for (int i = 1; i <= N; i++) printf("%lld\n", sum[i]);

	return 0;
}

namespace Graph {
	int totc, osz;
	LL totcnt;
	IntArr vis, ext, col, cntl, tmp, sz;
	LLArr ocnt, cnt;

	namespace fcntr {
		int totsz, cntr;

		void dfs(int u, int fa) {
			sz[u] = 1;
			int mxsz = 0;
			forto(u) {
				if (vis[v] || v == fa) continue;
				dfs(v, u);
				mxsz = std::max(mxsz, sz[v]);
				sz[u] += sz[v];
			}
			if (std::max(mxsz, totsz - sz[u]) * 2 <= totsz) cntr = u;
		}

		int find(int u, int usz) {
			totsz = usz;
			dfs(u, 0);
			return cntr;
		}
	}

	void dfs(int u, int fa, LL * cntar, int * colar) {
		int colu = C[u];
		if (!ext[colu]) ext[colu] = 1, colar[totc++] = colu;
		if (++cntl[colu] == 1) cntar[colu] += sz[u];
		forto(u) {
			if (vis[v] || v == fa) continue;
			dfs(v, u, cntar, colar);
		}
		--cntl[colu];
	}

	void dfs(int u, int fa, LL delta) {
		if (++cntl[C[u]] == 1) delta += osz - ocnt[C[u]];
		sum[u] += totcnt + delta;
		forto(u) {
			if (vis[v] || v == fa) continue;
			dfs(v, u, delta);
		}
		--cntl[C[u]];
	}

	void Div(int u, int usz) {
		u = fcntr::find(u, usz);
		fcntr::dfs(u, 0);
		vis[u] = 1;
		int colu = C[u];

		totc = 0;
		dfs(u, 0, ocnt, col);
		int totc0 = totc;
		totcnt = 0;
		for (int i = 0; i < totc0; i++) {
			ext[col[i]] = 0;
			totcnt += ocnt[col[i]];
		}
		LL totcnt0 = totcnt;
		sum[u] += totcnt;

		forto(u) {
			if (vis[v]) continue;

			totc = 0, cntl[colu] = 1;
			dfs(v, u, cnt, tmp);
			cntl[colu] = 0, ocnt[colu] -= sz[v], totcnt -= sz[v], osz = sz[u] - sz[v];
			for (int i = 0; i < totc; i++) {
				ext[tmp[i]] = 0;
				ocnt[tmp[i]] -= cnt[tmp[i]];
				totcnt -= cnt[tmp[i]];
			}
			
			dfs(v, u, 0);

			totcnt = totcnt0, ocnt[colu] += sz[v];
			for (int i = 0; i < totc; i++) {
				ocnt[tmp[i]] += cnt[tmp[i]];
				cnt[tmp[i]] = 0;
			}
		}

		for (int i = 0; i < totc0; i++) ocnt[col[i]] = 0;

		forto(u) {
			if (vis[v]) continue;
			Div(v, sz[v]);
		}
	}
}
