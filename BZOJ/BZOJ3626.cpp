// BZOJ 3626
// LNOI 2014
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <utility>
#include <vector>

#define rg register
#define gch getchar
#define fir first
#define sec second
#define forto(_) for (rg int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int kMaxn = 5e4 + 10, MOD = 201314;

typedef long long LL;
typedef std::pair<int, int> Pii;
typedef std::vector<Pii> VPii;
typedef int IntArr[kMaxn];

struct Edge {
	int to, next;
} E[kMaxn];

int n, q, tote;
IntArr last, Z, ans;
VPii qry[kMaxn];

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			rg char ch = gch(); x = 0;
			for (; !isdigit(ch); ch = gch());
			for (; isdigit(ch); ch = gch())
				x = (x << 3) + (x << 1) + (ch ^ '0');
		}
}
inline int & Add(int & x, LL y) {
	return (x = (x + y) % MOD);
}
namespace hld {
	IntArr sz, son, dep, fa, top, dfn;
	int dfs_clock;

	void Dfs1(int u);
	void Dfs2(int u, int tp);
	inline void Init() {
		dep[1] = 1;
		Dfs1(1);
		Dfs2(1, 1);
	}
	void Insert(int u);
	int Query(int u);
}
inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
}

int main() {
	using fast_io::Read;
	
	Read(n), Read(q);
	for (int i = 2, fai; i <= n; i++) {
		Read(fai);
		AddEdge(++fai, i);
	}
	for (int i = 0, li, ri, zi; i < q; i++) {
		Read(li), Read(ri), Read(zi);
		qry[li].push_back(Pii(-(++zi), i));
		qry[++ri].push_back(Pii(zi, i));
	}

	hld::Init();
	int last = 0;
	for (int i = 1; i <= n; i++) {
	   for (; last < i; ) {
		   hld::Insert(++last);
	   }
	   for (VPii::iterator it = qry[i].begin(); it != qry[i].end(); ++it) {
//		   printf(" ans[%d] %c= %d\n", abs(it->sec), it->sec > 0 ? '+' : '-', hld::Query(it->fir));
		   Add(ans[it->sec], (it->fir > 0 ? 1 : -1) * hld::Query(abs(it->fir)));
	   }
	}

	for (int i = 0; i < q; i++) {
		printf("%d\n", (ans[i] + MOD) % MOD);
	}
	return 0;
}

namespace hld {
	void Dfs1(int u) {
		sz[u] = 1, son[u] = -1;
		forto(u) {
			fa[v] = u;
			Dfs1(v);
			sz[u] += sz[v];
			if (son[u] == -1 || sz[son[u]] < sz[v]) son[u] = v;
		}
	}
	void Dfs2(int u, int tp) {
		dfn[u] = ++dfs_clock, top[u] = tp;
		if (son[u] == -1) return;
		Dfs2(son[u], tp);
		forto(u) {
			if (v == son[u]) continue;
			Dfs2(v, v);
		}
	}
	namespace sgm {
		struct Node {
			int val, tag;
		} T[kMaxn << 1];
		int ql, qr;
		
		inline int Id(int l, int r) {
			return l + r | l != r;
		}
		void PushDown(int l, int r) {
			int cur = Id(l, r);
			if (T[cur].tag) {
				int mid = l + r >> 1, lson = Id(l, mid), rson = Id(mid + 1, r);
				Add(T[lson].val, T[cur].tag * LL(mid - l + 1) % MOD);
				Add(T[lson].tag, T[cur].tag);
				Add(T[rson].val, T[cur].tag * LL(r - mid) % MOD);
				Add(T[rson].tag, T[cur].tag);
				T[cur].tag = 0;
			}
		}
		int U(int l, int r) {
			int cur = Id(l, r);
			if (r < ql || l > qr) return T[cur].val;
			if (ql <= l && r <= qr) {
				Add(T[cur].tag, 1);
				return Add(T[cur].val, r - l + 1);
			}
			int mid = l + r >> 1;
			PushDown(l, r);
			return T[cur].val = (U(l, mid) + U(mid + 1, r)) % MOD;
		}
		int Q(int l, int r) {
			if (r < ql || l > qr) return 0;
			if (ql <= l && r <= qr) return T[Id(l, r)].val;
			int mid = l + r >> 1;
			PushDown(l, r);
			return (Q(l, mid) + Q(mid + 1, r)) % MOD;
		}
		inline void Update(int l_, int r_) {
			ql = l_, qr = r_;
			U(1, n);
		}
		inline int Sum(int l_, int r_) {
			ql = l_, qr = r_;
			return Q(1, n);
		}
	}
	void Insert(int u) {
		for (; u; u = fa[top[u]]) {
			sgm::Update(dfn[top[u]], dfn[u]);
		}
	}
	int Query(int u) {
		int ret = 0;
		for (; u; u = fa[top[u]]) {
			Add(ret, sgm::Sum(dfn[top[u]], dfn[u]));
		}
		return ret;
	}
}
