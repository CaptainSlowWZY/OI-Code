// HNOI 2015
#include <cstdio>
#include <algorithm>

#define forto(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)

const int kMaxn = 4e4 + 10, kLgN = 16, kInf = 0x3f3f3f3f;

typedef int IAr[kMaxn];

struct Line {
	int x, yl, yr, key, tag;
	bool operator<(const Line & l) const {
		return x ^ l.x ? x < l.x : tag > l.tag;
	}
} L[kMaxn * 3];
struct Edge {
	int to, next;
} E[kMaxn << 1];

int n, p, q, tote, totl;
int F[kMaxn][kLgN];
IAr back, dep, idfn, odfn, ans;

void Dfs(int u);
int Climb(int u, int d);
int Lca(int u, int v);
void Solve(int al, int ar, int ql, int qr);
inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, back[v]}, back[v] = tote;
}
inline void PushRect(int x1, int y1, int x2, int y2, int k) {
	L[totl++] = (Line){x1, y1, y2, k, 1};
	L[totl++] = (Line){x2, y1, y2, k, -1};
}

int main() {
	scanf("%d%d%d", &n, &p, &q);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		AddEdge(u, v);
	}
	dep[1] = 1;
	Dfs(1);
	int minc = kInf, maxc = 0;
	for (int i = 0, a, b, c, l, w; i < p; i++) {
		scanf("%d%d%d", &a, &b, &c);
		minc = std::min(minc, c);
		maxc = std::max(maxc, c);
		if (idfn[a] > idfn[b]) std::swap(a, b);
		l = Lca(a, b);
		if (a == l) {
			w = Climb(b, dep[b] - dep[a] - 1);
			PushRect(1, idfn[b], idfn[w] - 1, odfn[b], c);
			if (odfn[w] < n) {
				PushRect(idfn[b], odfn[w] + 1, odfn[b], n, c);
			}
		} else {
			PushRect(idfn[a], idfn[b], odfn[a], odfn[b], c);
		}
	}
	for (int i = 0, u, v, k; i < q; i++) {
		scanf("%d%d%d", &u, &v, &k);
		if (idfn[u] > idfn[v]) std::swap(u, v);
		L[totl++] = (Line){idfn[u], idfn[v], i, k, 0};
	}

	std::sort(L, L + totl);
	Solve(minc - 1, maxc, 0, totl);

	for (int i = 0; i < q; i++) printf("%d\n", ans[i]);
	
	return 0;
}

int Climb(int u, int d) {
	for (int i = 0; (1 << i) <= d; i++) {
		if (d >> i & 1) u = F[u][i];
	}
	return u;
}

int Lca(int u, int v) {
	if (dep[u] < dep[v]) std::swap(u, v);
	u = Climb(u, dep[u] - dep[v]);
	if (u == v) return u;
	for (int i = kLgN - 1; i >= 0; i--) {
		if (F[u][i] ^ F[v][i]) {
			u = F[u][i], v = F[v][i];
		}
	}
	return F[u][0];
}

namespace bit {
	int T[kMaxn];

	void _add(int p, int d) {
		for (; p <= n; p += p & -p) T[p] += d;
	}
	inline void Add(int l, int r, int del) {
		_add(l, del), _add(r + 1, -del);
	}
	int Count(int p) {
		int ret = 0;
		for (; p; p &= p - 1) ret += T[p];
		return ret;
	}
}

void Solve(int al, int ar, int ql, int qr) {
	if (ql == qr) return;
	if (ar - al <= 1) {
		for (int i = ql; i < qr; i++) {
			if (L[i].tag) continue;
			ans[L[i].yr] = ar;
		}
		return;
	}
	int mid = al + ar >> 1, tl = ql;
	static Line buf[kMaxn * 3];
	static int flag[kMaxn * 3];
	for (int i = ql, tmp; i < qr; i++) {
		if (L[i].tag) {
			if (L[i].key > mid) continue;
			bit::Add(L[i].yl, L[i].yr, L[i].tag);
			buf[tl++] = L[i];
		} else {
			flag[i] = 0;
			if ((tmp = bit::Count(L[i].yl)) >= L[i].key) {
				buf[tl++] = L[i];
			} else {
				L[i].key -= tmp;
				flag[i] = 1;
			}
		}
	}
	int tl0 = tl;
	for (int i = ql; i < qr; i++) {
		if (L[i].tag && L[i].key > mid || !L[i].tag && flag[i]) {
			buf[tl++] = L[i];
		}
	}
	for (int i = ql; i < qr; i++) L[i] = buf[i];
	Solve(al, mid, ql, tl0);
	Solve(mid, ar, tl0, qr);
}

void Dfs(int u) {
	static int dfs_clock = 0;
	idfn[u] = ++dfs_clock;
	for (int i = 1; i < kLgN && F[u][i - 1]; i++) {
		F[u][i] = F[F[u][i - 1]][i - 1];
	}
	forto(u) {
		if (v == F[u][0]) continue;
		dep[v] = dep[u] + 1, F[v][0] = u;
		Dfs(v);
	}
	odfn[u] = dfs_clock;
}
