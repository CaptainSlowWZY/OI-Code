// Luogu P3690
// Link Cut Tree Template
#include <cstdio>
#include <algorithm>

#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])
#define fa(_) (T[_].fa)

const int kMaxn = 3e5 + 10;

int n, m, val[kMaxn];

namespace lct {
	struct Node {
		int ch[2], fa, tag, _xor;
	} T[kMaxn];

#ifdef DEBUG
	void Debug() {
		puts("====== DEBUG ======");
		for (int i = 1; i <= n; i++) {
			printf(" Node %2d : ls %2d, rs %2d, fa %2d, tag %2d, _xor %2d\n", i, lson(i), rson(i), fa(i), T[i].tag, T[i]._xor);
		}
		puts("------ ----- ------");
	}
#endif
	void Access(int u);
	void Splay(int u);
	void Link(int u, int v);
	void Cut(int u, int v);
	inline void Maintain(int u) {
		T[u]._xor = T[lson(u)]._xor ^ T[rson(u)]._xor ^ val[u];
	}
	inline void Reverse(int u) {
		std::swap(lson(u), rson(u));
		T[u].tag ^= 1;
	}
	inline void MakeRoot(int u) {
		Access(u);
		Splay(u);
		Reverse(u);
	}
	inline void Split(int u, int v) {
		MakeRoot(u);
		Access(v);
		Splay(v);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", val + i);
	
	for (int o, x, y; m--; ) {
		scanf("%d%d%d", &o, &x, &y);
		using namespace lct;
		switch (o) {
			case 0 :
				Split(x, y);
				printf("%d\n", T[y]._xor);
				break;
			case 1 :
				Link(x, y);
				break;
			case 2 :
				Cut(x, y);
				break;
			case 3 :
				Splay(x);
				val[x] = y;
				Maintain(x);
		}
#ifdef DEBUG
		Debug();
#endif
	}
	return 0;
}

namespace lct {
	inline bool IsRoot(int u) {
		return lson(T[u].fa) != u && rson(T[u].fa) != u;
	}
	inline int Relat(int u) {
		return rson(T[u].fa) == u;
	}
	void PushDown(int u) {
		if (T[u].tag) {
			if (lson(u)) Reverse(lson(u));
			if (rson(u)) Reverse(rson(u));
			T[u].tag = 0;
		}
	}
	void Rotate(int u) {
		int prf = T[u].fa, ff = T[prf].fa, r = Relat(u);
		T[u].fa = ff;
		if (!IsRoot(prf)) T[ff].ch[Relat(prf)] = u;
		if (T[u].ch[r ^ 1]) fa(T[u].ch[r ^ 1]) = prf;
		T[prf].ch[r] = T[u].ch[r ^ 1];
		T[prf].fa = u, T[u].ch[r ^ 1] = prf;
		Maintain(prf);
	}
	void Splay(int u) {
		int top = 0;
		static int S[kMaxn];
		S[top++] = u;
		for (int v = u; !IsRoot(v); v = fa(v)) S[top++] = fa(v);
		for (; top; ) PushDown(S[--top]);
		while (!IsRoot(u)) {
			if (IsRoot(T[u].fa)) Rotate(u);
			else if (Relat(T[u].fa) == Relat(u)) {
				Rotate(T[u].fa);
				Rotate(u);
			}
			else {
				Rotate(u), Rotate(u);
			}
		}
		Maintain(u);
	}
	void Access(int u) {
		for (int v = 0; u; v = u, u = fa(u)) {
			Splay(u);
			rson(u) = v;
			Maintain(u);
		}
	}
	int FindRoot(int u) {
		Access(u);
		for (Splay(u); lson(u); u = lson(u)) {
			PushDown(u);
		}
		Splay(u);
		return u;
	}
	void Link(int u, int v) {
		MakeRoot(u);
		if (FindRoot(v) != u) fa(u) = v;
	}
	void Cut(int u, int v) {
		MakeRoot(u);
		if (FindRoot(v) == u && T[v].fa == u && !lson(v)) {
			T[v].fa = rson(u) = 0;
		}
	}
}
