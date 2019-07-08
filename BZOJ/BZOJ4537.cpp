#include <cmath>
#include <cstdio>
#include <algorithm>

const int kMaxm = 1e5 + 5, kMaxn = 5e4 + 5, kInf = 0x3f3f3f3f;

typedef int IAr[kMaxn];

struct Edge {
	int u, v, a, b;
	bool operator<(const Edge & e) const {
		return a == e.a ? b < e.b : a < e.a;
	}
	void in() { scanf("%d%d%d%d", &u, &v, &a, &b); }
} E[kMaxm];
struct Query {
	int u, v, a, b, id;
	bool operator<(const Query & e) const {
		return b == e.b ? a < e.a : b < e.b;
	}
	void in() { scanf("%d%d%d%d", &u, &v, &a, &b); }
} Q[kMaxn], cur[kMaxn];
struct Oper {
	int u, v, szu, mxa, mxb;
} O[kMaxm];

int n, m, q, top;
IAr fa, maxa, maxb, sz, ans;

inline bool ECmpB(const Edge & e1, const Edge & e2) {
	return e1.b == e2.b ? e1.a < e2.a : e1.b < e2.b;
}
int Find(int x) {
	return fa[x] == x ? x : Find(fa[x]);
}
void Merge(const Edge &);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) E[i].in();
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		Q[i].in();
		Q[i].id = i;
	}

	std::sort(E, E + m);
	std::sort(Q, Q + q);
	int size = sqrt(m * log2(n));
	E[m].a = kInf;
	for (int lb = 0, alb, aub, totc; lb < m; lb += size) {
		alb = E[lb].a, aub = E[std::min(lb + size, m)].a, totc = 0;
		for (int i = 0; i < q; i++) {
			if (alb <= Q[i].a && Q[i].a < aub) {
				cur[totc++] = Q[i];
			}
		}
		if (!totc) continue;
		if (lb) std::sort(E, E + lb, ECmpB);
		for (int i = 1; i <= n; i++) {
			fa[i] = i, sz[i] = 1;
			maxa[i] = maxb[i] = -1;
		}
		for (int i = 0, j = 0, k; i < totc; i++) {
			for (; j < lb && E[j].b <= cur[i].b; j++) Merge(E[j]);
			top = 0;
			for (k = lb; k < lb + size && k < m; k++) {
				if (E[k].a <= cur[i].a && E[k].b <= cur[i].b) Merge(E[k]);
			}
			int u = Find(cur[i].u), v = Find(cur[i].v);
			ans[cur[i].id] = u == v && maxa[u] == cur[i].a && maxb[u] == cur[i].b;
			// some operation to undo
			for (; top--; ) {
				fa[O[top].v] = O[top].v, sz[O[top].u] = O[top].szu;
				maxa[O[top].u] = O[top].mxa;
				maxb[O[top].u] = O[top].mxb;
			}
		}
	}

	for (int i = 0; i < q; i++) puts(ans[i] ? "Yes" : "No");
	return 0;
}

void Merge(const Edge & e) {
	int x = Find(e.u), y = Find(e.v);
	if (sz[x] < sz[y]) std::swap(x, y);
	O[top++] = (Oper){x, y, sz[x], maxa[x], maxb[x]};
	if (x != y) {
		fa[y] = x, sz[x] += sz[y];
		maxa[x] = std::max(maxa[x], maxa[y]);
		maxb[x] = std::max(maxb[x], maxb[y]);
	}
	maxa[x] = std::max(maxa[x], e.a);
	maxb[x] = std::max(maxb[x], e.b);
}
