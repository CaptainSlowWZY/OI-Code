#include <cstdio>
#include <algorithm>

#define fa(_) (T[_].fa)
#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])

const int kMaxn = 1e5 + 5;

namespace lct {
	struct Node {
		int fa, ch[2];
		int rev;
		int col, blc;
	} T[kMaxn];

	inline void Maintain(int u) {
		T[u].blc = ~T[rson(u)].blc ? T[rson(u)].blc : 
			(T[u].col ? u : T[lson(u)].blc);
	}
	inline void Reverse(int u) {
		T[u].rev ^= 1;
		std::swap(lson(u), rson(u));
	}
	void Splay(int u);
	void Access(int u);
	inline void MakeRoot(int u) { Access(u); Splay(u); Reverse(u); }
	inline void Link(int u, int v) { MakeRoot(u); T[u].fa = v; }
	inline void Split(int u, int v) { MakeRoot(u); Access(v); Splay(v); }

	void debug() {
		puts("### DEBUGer");
		for (int i = 1; i <= 9; i++) {
			printf(" %d, fa %d, ch(%d, %d) | col %c | blc %d\n",
					i, fa(i), lson(i), rson(i), T[i].col ? 'B' : 'W', 
					T[i].blc);
		}
		puts("---end\n");
	}
}

int n, q;

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 0; i <= n; i++) lct::T[i].blc = -1;
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		lct::Link(u, v);
	}
	
	for (int op, v; q--; ) {
		scanf("%d%d", &op, &v);
		using namespace lct;
		if (op) {
			Split(v, 1);
		//	debug();
			printf("%d\n", T[1].blc);
		} else {
			Split(v, v);
			T[v].col ^= 1;
			Maintain(v);
		//	printf(" T[%d].blc = %d\n", v, T[v].blc);
		}
	}

	return 0;
}

namespace lct {
	inline bool IsRoot(int u) {
		return lson(T[u].fa) != u && rson(T[u].fa) != u;
	}
	inline int Relat(int u) { return rson(T[u].fa) == u; }
	void PushDown(int u) {
		if (T[u].rev) {
			if (lson(u)) Reverse(lson(u));
			if (rson(u)) Reverse(rson(u));
			T[u].rev = 0;
		}
	}
	void Rotate(int u) {
		int prf = T[u].fa, ff = T[prf].fa, r = Relat(u);
		T[u].fa = ff;
		if (!IsRoot(prf)) T[ff].ch[Relat(prf)] = u;
		T[prf].fa = u;
		if (T[u].ch[r ^ 1]) fa(T[u].ch[r ^ 1]) = prf;
		T[prf].ch[r] = T[u].ch[r ^ 1], T[u].ch[r ^ 1] = prf;
		Maintain(prf);
	}
	void Splay(int u) {
		static int S[kMaxn];
		int top = 0;
		S[top++] = u;
		for (int v = u; !IsRoot(v); v = T[v].fa) S[top++] = T[v].fa;
		while (top) PushDown(S[--top]);
		while (!IsRoot(u)) {
			if (IsRoot(T[u].fa)) Rotate(u);
			else if (Relat(u) == Relat(T[u].fa)) {
				Rotate(T[u].fa), Rotate(u);
			} else {
				Rotate(u), Rotate(u);
			}
		}
		Maintain(u);
	}
	void Access(int u) {
		for (int v = 0; u; u = T[v = u].fa) {
			Splay(u), rson(u) = v, Maintain(u);
		}
	}
}
