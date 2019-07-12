#pragma GCC optimize(2)
#include <algorithm>
#include <cstdio>
#include <cctype>

const int kMaxn = 1e5 + 10, kMaxm = 1e6 + 10;
const int kMaxv = kMaxn + kMaxm;

struct Oper {
	int t, u, v, id;
} O[kMaxn];
struct Edge {
	int u, v, w, id, cut;
	bool operator<(const Edge & e) const {
		return u == e.u ? v < e.v : u < e.u;
	}
} E[kMaxm];

int n, m, q;
int anc[kMaxn], ans[kMaxn];
int val[kMaxv];

#define rg register
#define gch getchar

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			x = 0; rg char ch = gch();
			for (; !isdigit(ch); ch = gch());
			for (; isdigit(ch); ch = gch()) x = (x << 3) + (x << 1) + (ch ^ '0');
		}
}
namespace lct {
	struct Node {
		int mx;
		int fa, ch[2];
		int rev;
	} T[kMaxv];

#define fa(_) (T[_].fa)
#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])

	void Access(int u);
	void Link(int u, int v);
	void Splay(int u);
	inline void Link(int u, int v, int id) {
		Link(u, n + id); Link(n + id, v);
	}
	inline void Reverse(int u) {
		T[u].rev ^= 1; std::swap(lson(u), rson(u));
	}
	inline void MakeRoot(int u) {
		Access(u); Splay(u); Reverse(u);
	}
	inline void Split(int u, int v) {
		MakeRoot(u); Access(v); Splay(v);
	}
}
inline void Adj(int & x, int & y) {
	x > y ? std::swap(x, y) : (void)0;
}
inline bool CmpW(const Edge & e1, const Edge & e2) {
	return e1.w < e2.w;
}
inline bool CmpId(const Edge & e1, const Edge & e2) {
	return e1.id < e2.id;
}
inline int Cmpar(int u, int v) {
	return val[u] > val[v] ? u : v;
}
void AddEdge(int u, int v, int id);
int FindEdge(int u, int v);
int Find(int u) {
	return anc[u] == u ? u : anc[u] = Find(anc[u]);
}

int main() {
	using fast_io::Read;
	Read(n), Read(m), Read(q);
	for (int i = 1; i <= m; i++) {
		Read(E[i].u), Read(E[i].v), Read(E[i].w);
		Adj(E[i].u, E[i].v);
	}
	
	std::sort(E + 1, E + m + 1, CmpW);
	for (int i = 1; i <= m; i++) {
		E[i].id = i; val[n + i] = E[i].w;
	}
	std::sort(E + 1, E + m + 1);
	
	for (int i = 0, k; i < q; i++) {
		Read(O[i].t), Read(O[i].u), Read(O[i].v);
		if (O[i].t == 1) continue;
		Adj(O[i].u, O[i].v);
		k = FindEdge(O[i].u, O[i].v);
		E[k].cut = 1, O[i].id = E[k].id;
	}

	for (int i = 1; i <= n; i++) anc[i] = i;
	std::sort(E + 1, E + m + 1, CmpId);
	for (int i = 1, cnt = 0; i <= m; i++) {
		if (E[i].cut || Find(E[i].u) == Find(E[i].v)) continue;
		lct::Link(E[i].u, E[i].v, E[i].id);
		if (++cnt == n - 1) break;
	}

	int tota = 0;
	for (int i = q - 1; i >= 0; i--) {
		if (O[i].t == 1) {
			lct::Split(O[i].u, O[i].v);
			ans[tota++] = val[lct::T[O[i].v].mx];
		} else AddEdge(O[i].u, O[i].v, O[i].id);
	}

	while (tota) printf("%d\n", ans[--tota]);
	return 0;
}

int FindEdge(int u, int v) {
	int lb = 0, ub = m;
	for (int mid; ub - lb > 1; ) {
		mid = lb + ub >> 1;
		if (E[mid].u == u) {
			if (E[mid].v < v) lb = mid;
			if (E[mid].v == v) return mid;
			if (E[mid].v > v) ub = mid;
		} else if (E[mid].u < u) lb = mid;
		else ub = mid;
	}
	return ub;
}

namespace lct {
	inline bool IsRoot(int u) {
		return lson(fa(u)) != u && rson(fa(u)) != u;
	}
	inline void Maintain(int u) {
		T[u].mx = Cmpar(u, Cmpar(T[lson(u)].mx, T[rson(u)].mx));
	}
	inline int Relat(int u) { return rson(fa(u)) == u; }
	void PushDown(int u) {
		if (T[u].rev) {
			if (lson(u)) Reverse(lson(u));
			if (rson(u)) Reverse(rson(u));
			T[u].rev = 0;
		}
	}
	void Rotate(int u) {
		int prf = fa(u), ff = fa(prf), r = Relat(u);
		fa(u) = ff;
		if (!IsRoot(prf)) T[ff].ch[Relat(prf)] = u;
		if (T[u].ch[r ^ 1]) fa(T[u].ch[r ^ 1]) = prf;
		T[prf].ch[r] = T[u].ch[r ^ 1];
		fa(prf) = u, T[u].ch[r ^ 1] = prf;
		Maintain(prf);
	}
	void Splay(int u) {
		static int S[kMaxv];
		int top = 0; S[top++] = u;
		for (int v = u; !IsRoot(v); v = fa(v)) S[top++] = fa(v);
		while (top) PushDown(S[--top]);
		while (!IsRoot(u)) {
			if (IsRoot(fa(u))) Rotate(u);
			else if (Relat(u) == Relat(fa(u))) {
				Rotate(fa(u)); Rotate(u);
			} else {
				Rotate(u); Rotate(u);
			}
		}
		Maintain(u);
	}
	void Access(int u) {
		for (int v = 0; u; u = fa(v = u)) {
			Splay(u); rson(u) = v; Maintain(u);
		}
	}
	int FindRoot(int u) {
		Access(u); Splay(u);
		for (; lson(u); u = lson(u)) PushDown(u);
		Splay(u);
		return u;
	}
	void Link(int u, int v) {
		MakeRoot(u);
		if (FindRoot(v) != u) fa(u) = v;
	}
	void Cut(int u, int v) {
		MakeRoot(u);
		if (FindRoot(v) == u && fa(v) == u && !lson(v)) {
			rson(u) = fa(v) = 0; Maintain(u);
		}
	}
	inline void Cut(int u, int v, int id) {
		Cut(u, id); Cut(id, v);
	}
}

void AddEdge(int u, int v, int id) {
	using namespace lct;
	Split(u, v);
	if (val[T[v].mx] <= E[id].w) return;
	Cut(E[T[v].mx - n].u, E[T[v].mx - n].id, T[v].mx);
	Link(u, v, id);
}
