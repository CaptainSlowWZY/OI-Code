// kaihuang
#include <cstdio>
#include <algorithm>
#include <stack>

const int MAXN = 1e5 + 10;
const int Lg_N = 18;

typedef long long LL;
typedef int IntAr[MAXN];

struct Edge {
	int to, next;
} E[MAXN << 1];


int N, Q, tote, F[MAXN][Lg_N], totv, dfs_clock;
IntAr last, val, bgn, end, V, dep;
LL sumV[MAXN];

namespace BIT {
	LL T[MAXN];

	void add(int p, LL d) {
		for (; p <= N; p += p & -p) T[p] += d;
	}
	LL query(int p) {
		LL res = 0;
		for (; p > 0; p &= p - 1) res += T[p];
		return res;
	}
	void add(int l, int r, LL delta) {
		add(l, delta);
		add(r + 1, -delta);
	}
}
inline bool cmpv(int a, int b) { return bgn[a] < bgn[b]; }
inline void add_edge(int u, int v) {
	E[++tote].to = v, E[tote].next = last[u], last[u] = tote;
	E[++tote].to = u, E[tote].next = last[v], last[v] = tote;
}
void dfs(int u);
int lca(int u, int v);

int main() {
	scanf("%d%d", &N, &Q);
	for (int i = 1; i <= N; i++) scanf("%d", val + i);
	for (int i = 1, ui, vi; i < N; i++) {
		scanf("%d%d", &ui, &vi);
		add_edge(ui, vi);
	}
	dep[1] = 1, sumV[1] = val[1], dfs(1);
	for (int i = 1; i <= N; i++) BIT::add(bgn[i], bgn[i], sumV[i]);
	char input[5];
	for (; Q--; ) {
		scanf("%s", input);
		if (input[0] == 'Q') {
			totv = 0;
			for (int tmp; ~scanf("%d", &tmp) && tmp; ) V[totv++] = tmp;
			std::sort(V, V + totv, cmpv);
			std::stack<int> rlink;
			LL ans = 0;
			rlink.push(V[0]);
			for (int i = 1; i < totv; i++) {
				int l = lca(V[i], rlink.top()), lst = -1;
				for (; !rlink.empty() && bgn[l] < bgn[rlink.top()]; rlink.pop()) lst = rlink.top();
				if (rlink.empty() && ~lst) ans += BIT::query(bgn[lst]) - BIT::query(bgn[l]);
				if (rlink.empty() || rlink.top() != l) rlink.push(l);
				rlink.push(V[i]), ans += BIT::query(bgn[V[i]]) - BIT::query(bgn[l]);
			}
			int lst = -1;
			for (; !rlink.empty(); rlink.pop()) lst = rlink.top();
			if (~lst) ans += BIT::query(bgn[lst]) - BIT::query(bgn[F[lst][0]]);
			printf("%lld\n", ans);
		}
		else {
			int x, y;
			scanf("%d%d", &x, &y);
			BIT::add(bgn[x], end[x], (LL)y - BIT::query(bgn[x]) + BIT::query(bgn[F[x][0]]));
		}
	}
	return 0;
}

void dfs(int u) {
	bgn[u] = ++dfs_clock;
	for (int i = 1; i < Lg_N && F[u][i - 1]; i++) F[u][i] = F[F[u][i - 1]][i - 1];
	for (int v, e = last[u]; e; e = E[e].next)
		if ((v = E[e].to) != F[u][0]) {
			dep[v] = dep[u] + 1, F[v][0] = u, sumV[v] = sumV[u] + val[v];
			dfs(v);
		}
	end[u] = dfs_clock;
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) std::swap(u, v);
	for (int i = Lg_N - 1; i >= 0; i--)
		if (dep[F[u][i]] >= dep[v]) u = F[u][i];
	if (u == v) return u;
	for (int i = Lg_N - 1; i >= 0; i--)
		if (F[u][i] != F[v][i]) u = F[u][i], v = F[v][i];
	return F[u][0];
}

// AC!!!