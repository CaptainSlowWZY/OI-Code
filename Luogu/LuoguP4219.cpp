#include <algorithm>
#include <cstdio>

const int kMaxn = 1e5 + 10;

int n, q;
char S[10];

namespace lct {
#define fa(_) (T[_].fa)
#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])
	struct Node {
		int sz, vsz;
		int fa, ch[2];
		int rev;
	} T[kMaxn];

	inline void Reverse(int u) {
		T[u].rev ^= 1; std::swap(lson(u), rson(u));
	}
	void Access(int u);
	void Cut(int u, int v);
	void Link(int u, int v);
	void Splay(int u);
	inline void MakeRoot(int u) {
		Access(u); Splay(u); Reverse(u);
	}
	inline void Maintain(int u) {
		T[u].sz = 1 + T[lson(u)].sz + T[rson(u)].sz + T[u].vsz;
	}
	inline void Link(int u, int v) {
		MakeRoot(u); MakeRoot(v);
		fa(u) = v; T[v].vsz += T[u].sz; Maintain(v);
	}
	inline void Split(int u, int v) {
		MakeRoot(u); Access(v); // Splay(v);
	}
}

int main() {
	scanf("%d%d", &n, &q);
	for (int x, y, szx, szy; q--; ) {
		scanf("%s%d%d", S, &x, &y);
		using namespace lct;
		if (S[0] == 'A') Link(x, y);
		else {
			Split(y, x); szx = T[x].vsz + 1;
			Split(x, y); szy = T[y].vsz + 1;
			printf("%lld\n", 1ll * szx * szy);
		}
	}
	return 0;
}

namespace lct {
	inline int IsRoot(int u) {
		return lson(fa(u)) != u && rson(fa(u)) != u;
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
			Splay(u);
			T[u].vsz += T[rson(u)].sz - T[v].sz;
			rson(u) = v; Maintain(u);
		}
	}
	int FindRoot(int u) {
		Access(u);
		for (Splay(u); lson(u); u = lson(u)) PushDown(u);
		Splay(u);
		return u;
	}
}
