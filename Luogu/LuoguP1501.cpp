// Tree II
#include <cstdio>
#include <algorithm>

#ifdef DEBUG
	#define db(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define db(format, ...) 0
#endif
#define fa(_) (T[_].fa)
#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])

const int kMaxn = 1e5 + 10, MOD = 51061;

typedef long long LL;

int n, q;

namespace lct {
	struct Node {
		int sz, val, sum;	// identity
		int fa, ch[2];	// relation
		int add, mul, rev;	// tag
	} T[kMaxn];


	template <typename T> inline
		void Add(T & x, LL y) {
			(x += y) >= MOD ? (x -= MOD) : 0;
		}
	template <typename T> inline
		void Mult(T & x, LL y) {
			x = x * y % MOD;
		}
	void Debug() {
		db("\n###### Debuger for LCT ######%c", '\n');
#ifdef DEBUG
		for (int i = 1; i <= n; i++) {
			db("  %d, fa %d, ch(0: %d, 1: %d), val %d, sum %d, sz %d\n    tag: * %d + %d, reverse %d\n",
					i, fa(i), lson(i), rson(i), T[i].val, T[i].sum, T[i].sz, T[i].mul, T[i].add, T[i].rev);
		}
#endif
		db("###### E    N    D ######%c", '\n');
	}
	inline void Reverse(int u) {
		std::swap(lson(u), rson(u));
		T[u].rev ^= 1;
	}
	inline void Maintain(int u) {
		T[u].sum = (T[lson(u)].sum + T[rson(u)].sum) % MOD;
		Add(T[u].sum, T[u].val);
		T[u].sz = T[lson(u)].sz + T[rson(u)].sz + 1;
	}
	void Splay(int u);
	void Access(int u);
	inline void MakeRoot(int u) {
		Access(u);
		Splay(u);
		Reverse(u);
	}
	int FindRoot(int u);
	inline void Split(int u, int v) {
		db(" ====== split %d ======%c", u, '\n');
		MakeRoot(u);
		Access(v);
		db(" After access%c", '\n');
		Debug();
		Splay(v);
		db(" After splay%c", '\n');
		Debug();
		db(" ====== end split ====== %c", '\n');
	}
	inline void Link(int u, int v) {
		MakeRoot(u);
		if (FindRoot(v) != u) fa(u) = v;
	}
	inline void Cut(int u, int v) {
		MakeRoot(u);
		if (FindRoot(v) == u && fa(v) == u && !lson(v)) {
			fa(v) = rson(u) = 0;
		}
	}
	inline void AddTag(int v, int del) {
		Add(T[v].val, del);
		Add(T[v].add, del);
		Add(T[v].sum, (LL)T[v].sz * del % MOD);
	}
	inline void MulTag(int v, int c) {
		Mult(T[v].add, c);
		Mult(T[v].mul, c);
		Mult(T[v].sum, c);
		Mult(T[v].val, c);
	}
	inline int Query(int u, int v) {
		Split(u, v);
		return (T[v].sum + MOD) % MOD;
	}
}

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) {
		using namespace lct;
		T[i].sz = T[i].sum = 1;
		T[i].mul = T[i].val = 1;
	}
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		lct::Link(u, v);
	}
	char IN[5];
	for (int a, b, c, d; q--; ) {
		scanf("%s", IN);
		using namespace lct;
		db("q = %d\n", q);
		if (IN[0] == '+') {
			scanf("%d%d%d", &a, &b, &c);
			db("+ %d, %d %d\n", a, b, c);
			Split(a, b);
			AddTag(b, c);
		} else if (IN[0] == '-') {
			scanf("%d%d%d%d", &a, &b, &c, &d);
			db(" cut %d %d, link %d, %d\n", a, b, c, d);
			Cut(a, b);
			Link(c, d);
		} else if (IN[0] == '*') {
			scanf("%d%d%d", &a, &b, &c);
			db("* %d, %d %d\n", a, b, c);
			Split(a, b);
			MulTag(b, c);
		} else {
			scanf("%d%d", &a, &b);
			db("q %d %d\n", a, b);
			printf("%d\n", Query(a, b));
		}
		Debug();
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
		db("    psuhdown %d\n", u);
		if (T[u].mul != 1) {
			if (lson(u)) MulTag(lson(u), T[u].mul);
			if (rson(u)) MulTag(rson(u), T[u].mul);
			T[u].mul = 1;
		}
		if (T[u].add) {
			if (lson(u)) {
				db("      push add %d -> %d\n", T[u].add, lson(u));
				AddTag(lson(u), T[u].add);
			}
			if (rson(u)) {
				db("      push add %d -> %d\n", T[u].add, rson(u));
				AddTag(rson(u), T[u].add);
			}
			T[u].add = 0;
		}
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
		db(" Splay %d\n", u);
		while (top) {
			PushDown(S[--top]);
			db(" %d%c", S[top], top ? ' ' : '\n');
		}
		db(" Is root %d? %d\n", u, IsRoot(u));
		while (!IsRoot(u)) {
			if (IsRoot(T[u].fa)) Rotate(u);
			else if (Relat(T[u].fa) == Relat(u)) {
				Rotate(T[u].fa), Rotate(u);
			} else {
				Rotate(u), Rotate(u);
			}
		}
		Maintain(u);
	}
	void Access(int u) {
		db("------ ACCESS %d ------\n", u);
		for (int v = 0; u; u = fa(v = u)) {
			Splay(u);
			db(" splay %d\n", u);
			rson(u) = v;
			Maintain(u);
		}
		db(" After access %d\n", u);
		Debug();
		db("----------------%c", '\n');
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
