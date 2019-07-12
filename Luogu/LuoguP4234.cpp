#include <algorithm>
#include <cstdio>

const int kMaxn = 5e4 + 10, kMaxm = 2e5 + 10;
const int kMaxv = kMaxn + kMaxm, kInf = 0x3f3f3f3f;

struct Edge {
	int u, v, c;
	bool operator<(const Edge & e) const {
		return c < e.c;
	}
} E[kMaxm];

int n, m;

int Solve();

int main() {
	scanf("%d%d", &n, &m);
	int p;
	for (int i = p = 1; i <= m; i++) {
		scanf("%d%d%d", &E[p].u, &E[p].v, &E[p].c);
		if (E[p].u != E[p].v) ++p;
	}

	m = p - 1;
	std::sort(E + 1, E + m + 1);

	printf("%d\n", Solve());
	return 0;
}

inline int Earlier(int x, int y) {
	return x <= n ? (y <= n ? x : y) :
		(y <= n ? x : std::min(x, y));
}

namespace lct {
	struct Node {
		int erl;
		int fa, ch[2];
		int rev;
		void clear() {
			erl = kInf, fa = ch[0] = ch[1] = rev= 0 ;
		}
	} T[kMaxv];

#define fa(_) (T[_].fa)
#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])

	inline void Maintain(int u) {
		T[u].erl = Earlier(u, Earlier(T[lson(u)].erl, T[rson(u)].erl));
	}
	inline int IsRoot(int u) {
		return lson(fa(u)) != u && rson(fa(u)) != u;
	}
	inline int Relat(int u) { return rson(fa(u)) == u; }
	inline void Reverse(int u) {
		T[u].rev ^= 1; std::swap(lson(u), rson(u));
	}
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
	inline void MakeRoot(int u) {
		Access(u); Splay(u); Reverse(u);
	}
	int FindRoot(int u) {
		Access(u);
		for (Splay(u); lson(u); u = lson(u)) PushDown(u);
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
			fa(v) = rson(u) = 0; Maintain(u);
		}
	}
}

int totb, inst[kMaxm];

void InsEdge(int e) {
	using namespace lct;
	int u = E[e].u, v = E[e].v;
	MakeRoot(u);
	if (FindRoot(v) == u) {
		int e0 = T[u].erl - n;
		Cut(E[e0].u, n + e0); Cut(E[e0].v, n + e0); inst[e0] = 0;
	} else --totb;
	Link(u, n + e); Link(n + e, v); inst[e] = 1;
}

int Solve() {
	totb = n;
	int res = kInf;
	for (int lb = 1, i = 1; i <= m; i++) {
		InsEdge(i);
		for (; lb <= i && !inst[lb]; ++lb);
		if (totb == 1) res = std::min(res, E[i].c - E[lb].c);
	}
	return res;
}
