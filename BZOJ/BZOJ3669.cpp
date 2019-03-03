// NOI 2014
#include <cstdio>
#include <cctype>
#include <algorithm>

#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])
#define fa(_) (T[_].fa)
#define rg register
#define gch getchar

const int kMaxv = 150010, kMaxm = 1e5 + 10, kInf = 0x7f7f7f7f;

struct Edge {
	int u, v, a, b;
	bool operator<(const Edge & e) const {
		return a < e.a;
	}
} E[kMaxm];

int n, m, val[kMaxv];

namespace lct {
	struct Node {
		int id, mxi, tag, fa, ch[2];
	} T[kMaxv];

	void Splay(int u);
	void Access(int u);
	int FindRoot(int u);
	inline void Maintain(int u) {
		T[u].mxi = T[u].id;
		if (lson(u) && val[T[lson(u)].mxi] > val[T[u].mxi]) T[u].mxi = T[lson(u)].mxi;
		if (rson(u) && val[T[rson(u)].mxi] > val[T[u].mxi]) T[u].mxi = T[rson(u)].mxi;
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
	inline bool Connect(int u, int v) {
		MakeRoot(u);
		return FindRoot(v) == u;
	}
	inline void Link(int u, int v) {
		!Connect(u, v) ? fa(u) = v : 0;
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
	inline int Select(int u, int v) {
		Split(u, v);
		return T[v].mxi;
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
	Read(n), Read(m);
	for (int i = 0; i < m; i++) {
		Read(E[i].u), Read(E[i].v), Read(E[i].a), Read(E[i].b);
	}

	std::sort(E, E + m);
	for (int i = n + 1; i <= n + m; i++) {
		val[i] = E[i - n - 1].b;
		lct::T[i].id = i;
	}
	int ans = kInf;
	for (int i = 0; i < m; i++) {
		using namespace lct;
//		printf(" i = %d\n", i);
//		printf(" E[i] = (%d, %d), a %d, b %d\n", E[i].u, E[i].v, E[i].a, E[i].b);
		if (Connect(E[i].u, E[i].v)) {
//			puts(" Connect!");
			int id = Select(E[i].u, E[i].v);
//			printf("  Select %d\n", id);
			if (val[id] > E[i].b) {
				Cut(E[id - n - 1].u, id), Cut(id, E[id - n - 1].v);
				Link(E[i].u, i + n + 1), Link(E[i].v, i + n + 1);
			}
		}
		else {
//			puts(" Not Tree yet");
			Link(E[i].u, i + n + 1), Link(E[i].v, i + n + 1);
		}
		if (Connect(1, n)) ans = std::min(ans, E[i].a + E[Select(1, n) - n - 1].b); 
	}

	printf("%d\n", ans == kInf ? -1 : ans);
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
		static int S[kMaxv];
		int top = 0;
		S[top++] = u;
		for (int v = u; !IsRoot(v); v = T[v].fa) S[top++] = T[v].fa;
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
	int FindRoot(int u) {
		Access(u);
		for (Splay(u); lson(u); u = lson(u)) {
			PushDown(u);
		}
		Splay(u);
		return u;
	}
}
