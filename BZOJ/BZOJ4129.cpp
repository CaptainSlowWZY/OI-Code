#include <cstdio>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <cassert>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int kMaxn = 5e4 + 10, kLgN = 17;

typedef int IAr[kMaxn];

struct Edge {
	int to, next;
} E[kMaxn << 1];
struct Query {
	int u, v, t, id;
	bool operator<(const Query & q) const;
} Q[kMaxn];

int n, m, B, tote, totq, top, totbl, F[kMaxn][kLgN];
IAr last, bl, A, ou, oa, dep, vis, ans, S, orgn;

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			register char ch = getchar();
			register bool f = false; x = 0;
			for (; !isdigit(ch); f |= (ch == '-'), ch = getchar());
			for (; isdigit(ch); ch = getchar())
				x = (x << 3) + (x << 1) + (ch ^ '0');
			f ? x = -x : 0;
		}
}
namespace Set {
	struct Block {
		int l, r;
	} block[kMaxn];
	IAr sum, bl, cnt;
	int bsz, totb, size;

	inline void Insert(int v_) {
		v_ <= size ? sum[bl[v_]] += (cnt[v_]++ == 0) : 0;
	}
	inline void Erase(int v_) {
		v_ <= size ? sum[bl[v_]] -= (--cnt[v_] == 0) : 0;
	}
	void Init();
	int Mex();
}
inline bool Query::operator<(const Query & q) const {
	return bl[u] == bl[q.u] ? 
			(bl[v] == bl[q.v] ? t < q.t : bl[v] < bl[q.v]) :
		   bl[u] < bl[q.u];
}
inline void Xor(int u) {
	vis[u] ? Set::Erase(A[u]) : Set::Insert(A[u]);
	vis[u] ^= 1;
}
inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, last[v]}, last[v] = tote;
}
void Dfs(int u);
int Lca(int u, int v);
void Move(int u, int v);

int main() {
	using fast_io::Read;

	Read(n), Read(m);
	for (int i = 1; i <= n; i++) {
		Read(A[i]);
		++A[i];
	}
	for (int i = 1, u, v; i < n; i++) {
		Read(u), Read(v);
		AddEdge(u, v);
	}
	int ver = 0;
	for (int i = 0, o, u, x; i < m; i++) {
		Read(o);
		if (!o) {
			Read(u), Read(x);
			ou[++ver] = u, oa[ver] = ++x;
		}
		else {
			Read(Q[totq].u), Read(Q[totq].v);
			Q[totq].id = totq, Q[totq++].t = ver;
		}
	}

	dep[1] = 1, B = pow(n, 0.45);
	Dfs(1);
	while (top) bl[S[--top]] = totbl;
	std::sort(Q, Q + totq);
	int curu = 1, curv = 1;
	ver = 0;
	Set::Init();
	// fprintf(stderr, "lol\n");
	for (int i = 0, l; i < totq; i++) {
		// fprintf(stderr, " i = %d\n", i);
		for (int p; ver < Q[i].t; ) {
			p = ou[++ver], orgn[ver] = A[p];
			if (vis[p]) {
				Set::Erase(A[p]);
				Set::Insert(oa[ver]);
			}
			A[p] = oa[ver];
		}
		for (int p; ver > Q[i].t; ) {
			p = ou[ver];
			if (vis[p]) {
				Set::Erase(A[p]);
				Set::Insert(orgn[ver]);
			}
			A[p] = orgn[ver--];
		}
		if (curu != Q[i].u) Move(curu, Q[i].u), curu = Q[i].u;
		if (curv != Q[i].v) Move(curv, Q[i].v), curv = Q[i].v;
		l = Lca(curu, curv);
		Xor(l);
		ans[Q[i].id] = Set::Mex() - 1;
		Xor(l);
	}

	for (int i = 0; i < totq; i++) printf("%d\n", ans[i]);
	return 0;
}

int Lca(int u, int v) {
	if (dep[u] < dep[v]) std::swap(u, v);
	for (int i = 0, del = dep[u] - dep[v]; (1 << i) <= del; i++)
		if (del >> i & 1) u = F[u][i];
	if (u == v) return u;
	for (int i = kLgN - 1; i >= 0; i--)
		if (F[u][i] != F[v][i]) {
			u = F[u][i];
			v = F[v][i];
		}
	return F[u][0];
}

void Dfs(int u) {
	for (int i = 1; i < kLgN && F[u][i - 1]; i++) {
		F[u][i] = F[F[u][i - 1]][i - 1];
	}
	S[top++] = u;
	int bot = top;
	forto(u) {
		if (v == F[u][0]) continue;
		F[v][0] = u, dep[v] = dep[u] + 1;
		Dfs(v);
		if (top - bot >= B) {
			for (++totbl; top > bot; ) {
				bl[S[--top]] = totbl;
			}
		}
	}
}

namespace Set {
	void Init() {
		size = n + 1, bsz = sqrt(size + 0.5), totb = (size - 1) / bsz + 1;
		for (int i = 1; i <= size; i++) bl[i] = (i - 1) / bsz + 1;
		for (int i = 1; i <= totb; i++) {
			block[i].l = (i - 1) * bsz + 1;
			block[i].r = i * bsz;
		}
		block[totb].r = size;
	}
	int Mex() {
		for (int i = 1; i <= totb; i++) {
			if (sum[i] != block[i].r - block[i].l + 1) {
				for (int j = block[i].l; j <= block[i].r; j++)
					if (!cnt[j]) return j;
			}
		}
		return -1;
	}
}

void Move(int u, int v) {
	if (dep[u] < dep[v]) std::swap(u, v);
	for (; dep[u] > dep[v]; u = F[u][0]) Xor(u);
	for (; u ^ v; u = F[u][0], v = F[v][0]) {
		Xor(u), Xor(v);
	}
}
