#include <algorithm>
#include <cstdio>
#include <map>
#include <cassert>

typedef long long LL;

const int kMaxn = 1e5 + 10;

int n, m, k;
char IN[10];

namespace lct {
	struct Node {
		int col, val, sz, vsz;
		LL len, lsum, rsum, vsum;
		int fa, ch[2], rev;

		Node() {}
		Node(int v_) :
			val(v_), len(v_) {
				lsum = rsum = vsum = col = vsz = 0;
				fa = ch[0] = ch[1] = rev = sz = 0;
			}
	} T[kMaxn << 1];
	int size, pltp;
	int pool[kMaxn];

#define fa(_) (T[_].fa)
#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])

	inline void Reverse(int u) {
		std::swap(lson(u), rson(u));
		std::swap(T[u].lsum, T[u].rsum);
		T[u].rev ^= 1;
	}
	inline void Maintain(int u) {
		T[u].lsum = T[rson(u)].lsum + T[lson(u)].lsum + T[u].vsum + 
			1ll * (T[rson(u)].sz + T[u].col + T[u].vsz) *
			(T[lson(u)].len + T[u].val);
		T[u].rsum = T[rson(u)].rsum + T[lson(u)].rsum + T[u].vsum +
			1ll * (T[lson(u)].sz + T[u].col + T[u].vsz) *
			(T[rson(u)].len + T[u].val);
		T[u].len = T[lson(u)].len + T[u].val + T[rson(u)].len;
		T[u].sz = T[u].col + T[lson(u)].sz + T[rson(u)].sz + T[u].vsz;
	}
	void Splay(int u);
	void Access(int u);
	inline void MakeRoot(int u) {
		Access(u); Splay(u); Reverse(u);
	}
	inline void Flip(int u) {
		MakeRoot(u); T[u].col ^= 1; Maintain(u);
	}
	inline LL Query(int u) {
		MakeRoot(u);
		return T[u].lsum;
	}
	void Link(int u, int v, int w);
	void Cut(int u, int v);
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	lct::size = n;
	for (int u, v, w; m--; ) {
		scanf("%d%d%d", &u, &v, &w);
		lct::Link(u, v, w);
	}
	
	for (int u, v, w; k--; ) {
		scanf("%s", IN);
		using namespace lct;
		switch (IN[0]) {
			case 'L' :
				scanf("%d%d%d", &u, &v, &w);
				Link(u, v, w); break;
			case 'C' :
				scanf("%d%d", &u, &v);
				Cut(u, v); break;
			case 'F' : 
				scanf("%d", &u);
				Flip(u); break;
			case 'Q' :
				scanf("%d", &u);
				printf("%lld\n", Query(u));
		}
	}
	return 0;
}

namespace lct {
	inline bool IsRoot(int u) {
		return lson(fa(u)) != u && rson(fa(u)) != u;
	}
	inline int Relat(int u) { return rson(fa(u)) == u; }
	int NewNode(int v_) {
		int u = pltp ? pool[--pltp] : ++size;
		T[u] = Node(v_);
		return u;
	}
	void PushDown(int u) {
		if (!T[u].rev) return;
		if (lson(u)) Reverse(lson(u));
		if (rson(u)) Reverse(rson(u));
		T[u].rev = 0;
	}
	void Rotate(int u) {
		int prf = fa(u), ff = fa(prf), r = Relat(u);
		if (!IsRoot(prf)) T[ff].ch[Relat(prf)] = u;
		if (T[u].ch[r ^ 1]) fa(T[u].ch[r ^ 1]) = prf;
		T[prf].ch[r] = T[u].ch[r ^ 1], T[u].ch[r ^ 1] = prf;
		fa(u) = ff, fa(prf) = u; Maintain(prf);
	}
	void Splay(int u) {
		static int S[kMaxn << 1];
		int top = 0;
		S[top++] = u;
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
			Splay(u);
			T[u].vsz += T[rson(u)].sz - T[v].sz;
			T[u].vsum += T[rson(u)].lsum - T[v].lsum;
			rson(u) = v; Maintain(u);
		}
	}
	inline void Release(int u) { pool[pltp++] = u; }
	inline void _Link(int u, int v) {
		MakeRoot(u); MakeRoot(v); fa(u) = v;
		T[v].vsz += T[u].sz; T[v].vsum += T[u].lsum;
		Maintain(v);
	}

	std::map<int, int> G[kMaxn];

	void Link(int u, int v, int w) {
		if (u > v) std::swap(u, v);
		assert(!G[u][v]);
		int e = G[u][v] = NewNode(w);
		_Link(u, e); _Link(e, v);
	}
	inline void _Cut(int u, int v) {
		MakeRoot(u); Access(v); Splay(u);
		rson(u) = fa(v) = 0; Maintain(u);
	}
	void Cut(int u, int v) {
		if (u > v) std::swap(u, v);
		int e = G[u][v];
		_Cut(u, e); _Cut(e, v);
		Release(e); G[u].erase(v);
	}
}
