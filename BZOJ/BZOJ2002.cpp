// HNOI 2010
#include <cstdio>
#include <cctype>
#include <algorithm>

#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])
#define fa(_) (T[_].fa)
#define rg register
#define gch getchar

const int kMaxn = 2e5 + 10;

int n, m, K[kMaxn];

namespace lct {
	struct Node {
		int sz, tag, fa, ch[2];
	} T[kMaxn];

	inline void Maintain(int u) {
		T[u].sz = 1 + T[lson(u)].sz + T[rson(u)].sz;
	}
	inline void Reverse(int u) {
		std::swap(lson(u), rson(u));
		T[u].tag ^= 1;
	}
	void Splay(int u);
	void Access(int u);
	inline void MakeRoot(int u) {
		Access(u);
		Splay(u);
		Reverse(u);
	}
	inline void Link(int u, int v) {
		MakeRoot(u);
		fa(u) = v;
	}
	inline void Split(int u, int v) {
		MakeRoot(u);
		Access(v);
		Splay(v);
	}
	inline void Cut(int u, int v) {
		Split(u, v);
		fa(u) = lson(v) = 0;
		Maintain(v);
	}
	inline int Dep(int u) {
		Split(n + 1, u);
		return T[u].sz - 1;
	}
}
namespace fast_io {
	template <typename T>
		void Read(T & x) {
			rg char ch = gch();
			for (; !isdigit(ch); ch = gch());
			for (x = 0; isdigit(ch); ch = gch())
				x = (x << 3) + (x << 1) + (ch ^ '0');
		}
}

int main() {
	using fast_io::Read;
	
	Read(n);
	for (int i = 1; i <= n; i++) {
		Read(K[i]);
		lct::Link(i, std::min(n + 1, i + K[i]));
		lct::T[i].sz = 1;
	}
	Read(m);
	for (int o, u, x; m--; ) {
		Read(o), Read(u);
		++u;
		using namespace lct;
		if (o == 1) {
			printf("%d\n", Dep(u));
		}
		else {
			Read(x);
			lct::Cut(u, std::min(n + 1, u + K[u]));
			K[u] = x;
			lct::Link(u, std::min(n + 1, u + K[u]));
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
		static int S[kMaxn];
		int top = 0;
		S[top++] = u;
		for (int v = u; !IsRoot(v); v = fa(v)) S[top++] = fa(v);
		for (; top; ) PushDown(S[--top]);
		while (!IsRoot(u)) {
			if (IsRoot(T[u].fa)) Rotate(u);
			else if (Relat(T[u].fa) == Relat(u)) {
				Rotate(T[u].fa), Rotate(u);
			}
			else {
				Rotate(u), Rotate(u);
			}
		}
		Maintain(u);
	}
	void Access(int u) {
		for (int v = 0; u; u = T[v = u].fa) {
			Splay(u);
			rson(u) = v;
			Maintain(u);
		}
	}
}
