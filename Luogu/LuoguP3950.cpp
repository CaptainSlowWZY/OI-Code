#include <cstdio>
#include <algorithm>

#define fir first
#define sec second
#define fa(_) (T[_].fa)
#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])

typedef std::pair<int, int> Pii;

const int kMaxn = 3e5 + 10;

int n, m, totw;

namespace lct {
	struct Node {
		int fa, ch[2];
		int rev;
	} T[kMaxn];

	void Splay(int u);
	void Access(int u);
	int FindRoot(int u);

	inline void Maintain(int u) {
		// something ?
	}
	inline void Reverse(int u) {
		std::swap(lson(u), rson(u));
		T[u].rev ^= 1;
	}
	inline void MakeRoot(int u) {
		Access(u);
		Splay(u);
		Reverse(u);
	}
	inline void Link(int u, int v) {
		MakeRoot(u);
		T[u].fa = v;
	}
	inline void Split(int u, int v) {
		MakeRoot(u);
		Access(v);
		Splay(v);
	}
	inline void Cut(int u, int v) {
		Split(u, v);
		T[u].fa = lson(v) = 0;
		Maintain(v);
	}
}

Pii war[kMaxn];
char IN[5];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		lct::Link(u, v);
	}
	
	for (int u, v; m--; ) {
		using namespace lct;
		scanf("%s", IN);
		if (IN[0] == 'Q') {
			scanf("%d%d", &u, &v);
			MakeRoot(u);
			puts(FindRoot(v) == u ? "Yes" : "No");
		} else if (IN[0] == 'C') {
			scanf("%d%d", &u, &v);
			war[totw++] = Pii(u, v);
			Cut(u, v);
		} else {
			scanf("%d", &u);
			--u;
			Link(war[u].fir, war[u].sec);
		}
	}

	return 0;
}

namespace lct {
	inline bool IsRoot(int u) {
		return lson(fa(u)) != u && rson(fa(u)) != u;
	}
	inline int Relat(int u) {
		return rson(fa(u)) == u;
	}
	inline void PushDown(int u) {
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
		if (T[u].ch[r ^ 1]) fa(T[u].ch[r ^ 1]) = prf;
		T[prf].ch[r] = T[u].ch[r ^ 1];
		T[prf].fa = u, T[u].ch[r ^ 1] = prf;
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
			rson(u) = v;
			Maintain(u);
		}
	}
	int FindRoot(int u) {
		Access(u);
		for (Splay(u); lson(u); u = lson(u)) PushDown(u);
		Splay(u);
		return u;
	}
}
