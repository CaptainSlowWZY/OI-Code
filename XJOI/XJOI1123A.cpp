#include <cstdio>
#include <cctype>

#define rg register
#define gch getchar
#define forto(_) for (rg int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int kMaxn = 1e5 + 10, MOD = 998244353;

typedef long long LL;
typedef int IntArr[kMaxn];

struct Edge {
	int to, next;
} E[kMaxn << 1];

int n, q, tote;
IntArr A, last, ans;

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			rg char ch = gch(); x = 0;
			for (; !isdigit(ch); ch = gch());
			for (; isdigit(ch); ch = gch())
				x = (x << 3) + (x << 1) + (ch ^ '0');
		}
}
template <typename T>
inline T & Add(T & x, LL y) {
	return (x = (x + y) % MOD);
}
namespace hld {
	IntArr sz, son, fa, dep, top, dfn;
	int dfs_clock;

	void Dfs1(int u);
	void Dfs2(int u, int tp);
	inline void Init() {
		dep[1] = 1;
		Dfs1(1);
		Dfs2(1, 1);
	}
	LL Insert(int u, int val);
}
inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, last[v]}, last[v] = tote;
}

int main() {
	using fast_io::Read;
	
	Read(n), Read(q);
	for (int i = 1, u, v; i < n; i++) {
		Read(u), Read(v);
		AddEdge(u, v);
	}
	for (int i = 1; i <= n; i++) Read(A[i]);

	hld::Init();
	LL del1 = 0, del2 = 0, sumid = 0;
	for (int i = 1, dcur; i <= n; i++) {
		Add(sumid, (LL)i * (dcur = hld::dep[A[i]]) % MOD);
		del2 = (sumid + (LL(i + 1) * i >> 1) % MOD * dcur % MOD - (hld::Insert(A[i], i) << 1) % MOD) % MOD;
		ans[i] = (ans[i - 1] + Add(del1, del2)) % MOD;
		Add(ans[i], MOD);
	}

	for (int ki; q--; ) {
		Read(ki);
		printf("%d\n", ans[ki]);
	}
	return 0;
}

namespace hld {
	void Dfs1(int u) {
		sz[u] = 1, son[u] = -1;
		forto(u) {
			if (v == fa[u]) continue;
			fa[v] = u, dep[v] = dep[u] + 1;
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
			if (v == fa[u] || v == son[u]) continue;
			Dfs2(v, v);
		}
	}
	namespace sgm {
		struct Node {
			int val, tag;
		} T[kMaxn << 1];
		int ql, qr, del;
		
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
				Add(T[cur].tag, del);
				return Add(T[cur].val, LL(r - l + 1) * del % MOD);
			}
			int mid = l + r >> 1;
			PushDown(l, r);
			return T[cur].val = ((LL)U(l, mid) + U(mid + 1, r)) % MOD;
		}
		int Q(int l, int r) {
			if (r < ql || l > qr) return 0;
			if (ql <= l && r <= qr) return T[Id(l, r)].val;
			int mid = l + r >> 1;
			PushDown(l, r);
			return ((LL)Q(l, mid) + Q(mid + 1, r)) % MOD;
		}
		inline void Update(int l_, int r_, int v_) {
			ql = l_, qr = r_, del = v_;
			U(1, n);
		}
		inline int Sum(int l_, int r_) {
			ql = l_, qr = r_;
			return Q(1, n);
		}
	}
	LL Insert(int u, int val) {
		LL ret = 0;
		for (val %= MOD; u; u = fa[top[u]]) {
			sgm::Update(dfn[top[u]], dfn[u], val);
			Add(ret, sgm::Sum(dfn[top[u]], dfn[u]));
		}
		return ret;
	}
}
