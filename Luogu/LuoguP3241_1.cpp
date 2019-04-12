// HNOI2015
// Solved by segment-tree
#include <cstdio>
#include <algorithm>
#include <cassert>

#define forto(_) for (int e = back[_], v = E[e].to; e; \
						v = E[e = E[e].next].to)

const int kMaxn = 150010;

typedef int IAr[kMaxn];
typedef long long LL;

struct Edge {
	int to, cost, next;
} E[kMaxn << 1];
struct Monster {
	int age, pos;
	Monster(int age_ = 0, int pos_ = 0) :
		age(age_), pos(pos_) {}
	bool operator<(const Monster & m) const {
		return age < m.age;
	}
} M[kMaxn];

int n, q, A, tote;
IAr sume, back;
LL sumd[kMaxn];

namespace hld {
	IAr sz, son, fa, dep, top, dfn, upe;
	
	void Dfs1(int u);
	void Dfs2(int u, int tp);
	inline void Init() {
		upe[1] = dep[1] = 1;
		Dfs1(1);
		Dfs2(1, 1);
	}
	int Modify(int u);
	LL Query(int u, int fir, int lst);
}
namespace smt {
	IAr root;
};

inline void AddEdge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, c, back[v]}, back[v] = tote;
}

int main() {
	scanf("%d%d%d", &n, &q, &A);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &M[i].age);
		M[i].pos = i;
	}
	for (int i = 1, u, v, c; i < n; i++) {
		scanf("%d%d%d", &u, &v, &c);
		AddEdge(u, v, c);
	}

	std::sort(M + 1, M + n + 1);
	hld::Init();
	for (int i = 1; i <= n; i++) {
		sume[i] += sume[i - 1];
		sumd[i] = sumd[i - 1] + hld::dep[M[i].pos];
	}
	for (int i = 1; i <= n; i++) {
		smt::root[i] = hld::Modify(M[i].pos);
	}

	LL lans = 0;
	for (int u, a, b, l, r; q--; ) {
		using namespace hld;
		scanf("%d%d%d", &u, &a, &b);
		l = std::min((a + lans) % A, (b + lans) % A);
		r = std::max((a + lans) % A, (b + lans) % A);
	//	printf("***l = %d, r = %d\n", l, r);
		l = std::lower_bound(M + 1, M + n + 1, Monster(l)) - M;
		r = std::upper_bound(M + 1, M + n + 1, Monster(r)) - M - 1;
	//	assert(l <= r);
	//	printf("   query[%d, %d]\n", l, r);
		lans = LL(r - l + 1) * dep[u] + sumd[r] - sumd[l - 1] - 
			(Query(u, l, r) << 1);
		printf("%lld\n", lans);
	}

	return 0;
}

namespace smt {
	const int kMaxt = 1e7 + 10;

	struct Node {
		int cnt;
		LL sum;
		int ls, rs;
	} T[kMaxt];

	int Modify(int prv, int l, int r, int ql, int qr) {
		static int newn = 0;
		int rt = ++newn;
		T[rt] = T[prv];
	/*	printf("@@@smt_modify l, r[%d, %d]; ql, qr[%d, %d]\n",
				l, r, ql, qr);*/
		if (l == ql && r == qr) {
			++T[rt].cnt;
			return rt;
		}
		T[rt].sum += sume[qr] - sume[ql - 1];
		int mid = l + r >> 1;
		if (ql <= mid) {
			T[rt].ls = Modify(T[prv].ls, l, mid, ql, std::min(qr, mid));
		}
		if (mid < qr) {
			T[rt].rs = Modify(T[prv].rs, mid + 1, r, 
					std::max(ql, mid + 1), qr);
		}
		return rt;
	}
	LL Query(int rf, int rb, int l, int r, int ql, int qr) {
		LL sum = LL(sume[qr] - sume[ql - 1]) * (T[rb].cnt - T[rf].cnt);
		if (l == ql && r == qr) return sum + T[rb].sum - T[rf].sum;
		int mid = l + r >> 1;
		if (ql <= mid) {
			sum += Query(T[rf].ls, T[rb].ls, l, mid, 
					ql, std::min(qr, mid));
		}
		if (qr > mid) {
			sum += Query(T[rf].rs, T[rb].rs, mid + 1, r, 
					std::max(mid + 1, ql), qr);
		}
		return sum;
	}
}

namespace hld {
	void Dfs1(int u) {
		sz[u] = 1, son[u] = -1;
		forto(u) {
			if (v == fa[u]) continue;
			fa[v] = u, dep[v] = dep[u] + (upe[v] = E[e].cost);
			Dfs1(v);
			sz[u] += sz[v];
			if (son[u] == -1 || sz[v] > sz[son[u]]) son[u] = v;
		}
	}
	void Dfs2(int u, int tp) {
		static int dfs_clock = 0;
		sume[dfn[u] = ++dfs_clock] = upe[u], top[u] = tp;
		if (son[u] == -1) return;
		Dfs2(son[u], tp);
		forto(u) {
			if (v == fa[u] || v == son[u]) continue;
			Dfs2(v, v);
		}
	}
	int Modify(int u) {
		static int prv = 0;
		for (; u; u = fa[top[u]]) {
			prv = smt::Modify(prv, 1, n, dfn[top[u]], dfn[u]);
		}
		return prv;
	}
	LL Query(int u, int fir, int lst) {
		LL res = 0;
		for (; u; u = fa[top[u]]) {
			res += smt::Query(smt::root[fir - 1], smt::root[lst], 
					1, n, dfn[top[u]], dfn[u]);
		}
		return res;
	}
}
