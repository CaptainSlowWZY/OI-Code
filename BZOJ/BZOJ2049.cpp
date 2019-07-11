#include <algorithm>
#include <cstdio>

const int kMaxn = 1e4 + 10;

int n, m;
char S[20];

namespace lct {
#define fa(_) (T[_].fa)
#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])
	struct Node {
		int val;
		int fa, ch[2];
		int rev;
	} T[kMaxn];

	inline void Reverse(int u) {
		T[u].rev ^= 1; std::swap(lson(u), rson(u));
	}
	void Access(int u);
	void Cut(int u, int v);
	int FindRoot(int u);
	void Link(int u, int v);
	void Splay(int u);
}

int main() {
	scanf("%d%d", &n, &m);

	for (int x, y; m--; ) {
		scanf("%s%d%d", S, &x, &y);
		using namespace lct;
		if (S[0] == 'C') Link(x, y);
		if (S[0] == 'D') Cut(x, y);
		if (S[0] == 'Q') {
			puts(FindRoot(x) == FindRoot(y) ? "Yes" : "No");
		}
	}
	return 0;
}

namespace lct {
	inline void Maintain(int u) {
	}
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
			Splay(u); rson(u) = v; Maintain(u);
		}
	}
	int FindRoot(int u) {
		Access(u);
		for (Splay(u); lson(u); u = lson(u)) PushDown(u);
		Splay(u);
		return u;
	}
	inline void MakeRoot(int u) {
		Access(u); Splay(u); Reverse(u);
	}
	void Link(int u, int v) {
		MakeRoot(u);
		if (FindRoot(v) != u) fa(u) = v;
	}
	void Cut(int u, int v) {
		MakeRoot(u);
		if (FindRoot(v) == u && fa(v) == u && !lson(v)) {
			fa(v) = rson(u) = 0; Maintain(u);
		}
	}
}
