#include <cstdio>
#include <cmath>
#include <algorithm>

const int kMaxn = 1e5 + 10, kLgN = 18;

struct Edge {
	int to, next;
} E[kMaxn << 1];
struct Query {
	int u, v, vrs, id;
	bool operator<(const Query & q) const;
} Q[kMaxn];

int n, m, q, ver, totq, totbl, blsz;
int tote, top, last[kMaxn], dep[kMaxn], F[kMaxn][kLgN], S[kMaxn];
int V[kMaxn], W[kMaxn], C[kMaxn], lasc[kMaxn];
int cnt[kMaxn], vis[kMaxn], bl[kMaxn], mu[kMaxn], mt[kMaxn];
long long happy, ans[kMaxn];

inline bool Query::operator<(const Query & q) const {
	return bl[u] ^ bl[q.u] ? bl[u] < bl[q.u] :
		(bl[v] ^ bl[q.v] ? bl[v] < bl[q.v] : vrs < q.vrs);
}
inline void Flip(int u) {
	vis[u] ? (happy -= 1ll * V[C[u]] * W[cnt[C[u]]--]) : 
			(happy += 1ll * V[C[u]] * W[++cnt[C[u]]]);
	vis[u] ^= 1;
}
inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, last[v]}, last[v] = tote;
}
void Move(int u, int v);
int Lca(int u, int v);
void Dfs(int u);

int main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= m; i++) scanf("%d", V + i);
	for (int i = 1; i <= n; i++) scanf("%d", W + i);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		AddEdge(u, v);
	}
	for (int i = 1; i <= n; i++) scanf("%d", C + i);
	for (int i = 0, tp, x, y; i < q; i++) {
		scanf("%d%d%d", &tp, &x, &y);
		if (tp) {
			Q[totq] = (Query){x, y, ver, totq};
			totq++;
		} else {
			lasc[++ver] = C[x], C[x] = y;
			mu[ver] = x, mt[ver] = y;
		}
	}

	for (int i = ver; i > 0; i--) {
		C[mu[i]] = lasc[i];
	}
	blsz = pow(n, 2.0 / 3.0), dep[1] = 1;
	Dfs(1);
	for (; top; ) bl[S[--top]] = totbl;
	std::sort(Q, Q + totq);

	int u = 1, v = 1;
	ver = 0;
	for (int i = 0, l; i < totq; i++) {
	/*	printf(" producing (%d, %d) id = %d, version %d\n",
				Q[i].u, Q[i].v, Q[i].id, Q[i].vrs);
		printf("   current version %d\n", ver);*/
		for (int cur; ver < Q[i].vrs; ) {
			++ver;
		//	printf(" cur %d, vis ? %d\n", mu[ver], vis[mu[ver]]);
			if (vis[cur = mu[ver]]) {
				happy -= 1ll * V[C[cur]] * W[cnt[C[cur]]--];
				happy += 1ll * V[mt[ver]] * W[++cnt[mt[ver]]];
			}
			C[cur] = mt[ver];
		}
		for (int cur; ver > Q[i].vrs; --ver) {
			if (vis[cur = mu[ver]]) {
				happy -= 1ll * V[C[cur]] * W[cnt[C[cur]]--];
				happy += 1ll * V[lasc[ver]] * W[++cnt[lasc[ver]]];
			}
			C[cur] = lasc[ver];
		}
		Move(u, Q[i].u), u = Q[i].u;
		Move(v, Q[i].v), v = Q[i].v;
		l = Lca(u, v);
		Flip(l);
		ans[Q[i].id] = happy;
		Flip(l);
	}

	for (int i = 0; i < totq; i++) printf("%lld\n", ans[i]);
	return 0;
}

void Move(int u, int v) {
	if (u == v) return;
	if (dep[u] < dep[v]) std::swap(u, v);
//	printf(" move %d -> %d\n", u, v);
	for (; dep[u] > dep[v]; u = F[u][0]) Flip(u);
	for (; u ^ v; u = F[u][0], v = F[v][0]) {
		Flip(u), Flip(v);
	}
}

int Lca(int u, int v) {
	if (dep[u] < dep[v]) std::swap(u, v);
	for (int i = 0, del = dep[u] - dep[v];
			i < kLgN && (1 << i) <= del; i++) {
		if (del >> i & 1) u = F[u][i];
	}
	if (u == v) return u;
	for (int i = kLgN - 1; i >= 0; i--) {
		if (F[u][i] ^ F[v][i]) {
			u = F[u][i];
			v = F[v][i];
		}
	}
	return F[u][0];
}

void Dfs(int u) {
	S[top++] = u;
	for (int i = 1; i < kLgN && F[u][i - 1]; i++) {
		F[u][i] = F[F[u][i - 1]][i - 1];
	}
	int bot = top;
	for (int e = last[u], v = E[e].to; e;
			v = E[e = E[e].next].to) {
		if (v == F[u][0]) continue;
		dep[v] = dep[u] + 1, F[v][0] = u;
		Dfs(v);
		if (top - bot >= blsz) {
			for (++totbl; top > bot; ) bl[S[--top]] = totbl;
		}
	}
}
