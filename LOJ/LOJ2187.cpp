#include <algorithm>
#include <cstdio>
#include <cassert>

const int kMaxn = 5e5 + 10;

int n, q;
int son[kMaxn][3];

namespace lct {
#define fa(_) (T[_].fa)
#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])
	struct Node {
		int stat;
		int fa, ch[2];
		int dn[2], tag;
	} T[kMaxn * 3];

	inline void Flip(int u, int t) {
		T[u].stat ^= 3, std::swap(T[u].dn[0], T[u].dn[1]), T[u].tag += t;
	}
	void Access(int u);
	void Maintain(int u);
	void Splay(int u);
}
void Dfs(int);

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", son[i], son[i] + 1, son[i] + 2);
	}
	for (int i = n + 1; i <= 3 * n + 1; i++) {
		scanf("%d", &lct::T[i].stat);
		lct::T[i].stat <<= 1;
	}

	Dfs(1);
	int out = lct::T[1].stat >> 1;

	scanf("%d", &q);
	for (int u, tp; q--; ) {
		scanf("%d", &u);
		using namespace lct;
		tp = 1 - (bool)(T[u].stat ^= 2);	// 0->1, tp=0; 1->0, tp=1
		Access(u = fa(u));
		Splay(u);
		if (~T[u].dn[tp]) {
			Splay(u = T[u].dn[tp]);
			Flip(rson(u), tp ? -1 : 1);
			Maintain(rson(u));
			T[u].stat += tp ? -1 : 1;
			Maintain(u);
		} else {
			Flip(u, tp ? -1 : 1);
			Maintain(u);
			out ^= 1;
		}
		printf("%d\n", out);
	}	

	return 0;
}

void Dfs(int u) {
	using namespace lct;
	T[u].dn[0] = T[u].dn[1] = -1;
	if (u > n) return;
	for (int i = 0, v; i < 3; i++) {
		v = son[u][i], fa(v) = u;
		Dfs(v);
		T[u].stat += T[v].stat >> 1;
	}
}

namespace lct {
	inline int IsRoot(int u) {
		return lson(fa(u)) != u && rson(fa(u)) != u;
	}
	inline int Relat(int u) { return rson(fa(u)) == u; }
	void PushDown(int u) {
		if (T[u].tag) {
			if (lson(u)) Flip(lson(u), T[u].tag);
			if (rson(u)) Flip(rson(u), T[u].tag);
			T[u].tag = 0;
		}
	}
	void Maintain(int u) {
		for (int i = 0; i < 2; i++) {
			T[u].dn[i] = rson(u) && ~T[rson(u)].dn[i] ? T[rson(u)].dn[i] :
				(T[u].stat != i + 1 ? u : (
				 lson(u) && ~T[lson(u)].dn[i] ? T[lson(u)].dn[i] : -1));
		}
	}
	void Rotate(int u) {
		int prf = fa(u), ff = fa(prf), r = Relat(u);
		fa(u) = ff;
		if (!IsRoot(prf)) T[ff].ch[Relat(prf)] = u;
		if (T[u].ch[r ^ 1]) fa(T[u].ch[r ^ 1]) = prf;
		T[prf].ch[r] = T[u].ch[r ^ 1];
		T[u].ch[r ^ 1] = prf, fa(prf) = u;
		Maintain(prf);
	}
	void Splay(int u) {
		static int S[kMaxn];
		int top = 0;
		S[top++] = u;
		for (int v = u; !IsRoot(v); v = fa(v)) S[top++] = fa(v);
		while (top) PushDown(S[--top]);
		while (!IsRoot(u)) {
			if (IsRoot(fa(u))) Rotate(u);
			else if (Relat(u) == Relat(fa(u))) {
				Rotate(fa(u)), Rotate(u);
			} else {
				Rotate(u), Rotate(u);
			}
		}
		Maintain(u);
	}
	void Access(int u) {
		for (int v = 0; u; u = fa(v = u)) {
			Splay(u); rson(u) = v; Maintain(u);
		}
	}
}
