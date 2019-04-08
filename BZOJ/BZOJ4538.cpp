// HNOI2016
#pragma GCC optimize(2)
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <queue>

#define forto(_) for (rg int e = last[_], v = E[e].to; e; \
						v = E[e = E[e].next].to)
#define fir first
#define sec second
#define rg register

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			rg char ch = getchar();
			rg bool f = false; x = 0;
			for (; !isdigit(ch); f |= (ch == '-'), ch = getchar());
			for (; isdigit(ch); ch = getchar())
				x = (x << 3) + (x << 1) + (ch ^ '0');
			f ? x = -x : 0;
		}
	template <typename T>
		void Print(T x) {
			if (!x) return (void)(putchar('0'));
			if (x < 0) x = -x, putchar('-');
			rg int arr[20], len = 0;
			for (; x; arr[len++] = x % 10, x /= 10);
			while (len) putchar(arr[--len] ^ '0');
		}
	template <typename T>
		inline void Println(T x) {
			Print(x), putchar('\n');
		}
}

const int kMaxn = 1e5 + 10;

typedef int IAr[kMaxn];
typedef std::pair<int, int> Pii;

namespace hld {
	IAr dfn, dep, sz, top, fa, son;

	void Dfs1(int u);
	void Dfs2(int u, int tp);
	inline void Init() {
		dep[1] = 1;
		Dfs1(1);
		Dfs2(1, 1);
	}
	namespace smt {
		int Query(int l, int r, int qpos);
	}
	void Modify(int u, int v, int val);
}

struct Edge {
	int to, next;
} E[kMaxn << 1];

int n, m, tote;
IAr last;
int U[kMaxn << 1], V[kMaxn << 1], W[kMaxn << 1];

inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, last[v]}, last[v] = tote;
}

int main() {
	using fast_io::Read;
	Read(n), Read(m);
	for (rg int i = 1, u, v; i < n; i++) {
		Read(u), Read(v);
		AddEdge(u, v);
	}

	hld::Init();

	for (rg int tp, t, i = 1; i <= m; i++) {
		using namespace hld;
		Read(tp);
		switch (tp) {
			case 0 :
				Read(U[i]), Read(V[i]), Read(W[i]);
				Modify(U[i], V[i], W[i]);
				break;
			case 1 :
				Read(t);
				Modify(U[t], V[t], -W[t]);
				break;
			case 2 :
				Read(t);
				fast_io::Println(smt::Query(1, n, dfn[t]));
		}
	}
	
	return 0;
}

namespace hld {
	void Dfs1(int u) {
		sz[u] = 1, son[u] = -1;
		forto(u) {
			if (v == fa[u]) continue;
			dep[v] = dep[u] + 1, fa[v] = u;
			Dfs1(v);
			sz[u] += sz[v];
			if (son[u] == -1 || sz[v] > sz[son[u]]) son[u] = v;
		}
	}
	void Dfs2(int u, int tp) {
		static int dfs_clock = 0;
		dfn[u] = ++dfs_clock, top[u] = tp;
		if (son[u] == -1) return;
		Dfs2(son[u], tp);
		forto(u) {
			if (v == fa[u] || v == son[u]) continue;
			Dfs2(v, v);
		}
	}
	namespace smt {
		struct Heap {
			std::priority_queue<int> val, bin;

			void push(int x) { val.push(x); }
			int top() {
				while (!val.empty() && !bin.empty()) {
					if (val.top() ^ bin.top()) break;
					val.pop(), bin.pop();
				}
				return val.empty() ? -1 : val.top();
			}
			void erase(int x) { bin.push(x); }
		} T[kMaxn << 1];

		inline int Id(int l, int r) { return l + r | l != r; }
		void Upd(int l, int r, int ql, int qr, int val) {
			if (ql <= l && r <= qr) {	
				val > 0 ? T[Id(l, r)].push(val) : T[Id(l, r)].erase(-val);
				return;
			}
			int mid = l + r >> 1;
			if (ql <= mid) Upd(l, mid, ql, qr, val);
			if (qr > mid) Upd(mid + 1, r, ql, qr, val);
		}
		int Query(int l, int r, int qpos) {
			int rt = Id(l, r);
			if (l == r) return T[rt].top();
			int mid = l + r >> 1;
			if (qpos <= mid) {
				return std::max(T[rt].top(), Query(l, mid, qpos));
			} else {
				return std::max(T[rt].top(), Query(mid + 1, r, qpos));
			}
		}
	}
	void Modify(int u, int v, int val) {
		int totv = 0;
		static Pii trv[kMaxn];

		for (; top[u] ^ top[v]; u = fa[top[u]]) {
			if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
			trv[totv++] = Pii(dfn[top[u]], dfn[u]);
		}
		if (dep[u] > dep[v]) std::swap(u, v);
		trv[totv++] = Pii(dfn[u], dfn[v]);
		std::sort(trv, trv + totv);
		int last = 1;
		for (rg int i = 0; i < totv; i++) {
			if (trv[i].fir > last) {
				smt::Upd(1, n, last, trv[i].fir - 1, val);
			}
			last = trv[i].sec + 1;
		}
		if (last <= n) smt::Upd(1, n, last, n, val);
	}
}
