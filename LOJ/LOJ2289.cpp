#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

typedef double Db;

const int kMaxn = 1e5 + 5, kLen = 15;

struct Fuc {
	Db A[kLen];
	void set(int, Db, Db);
	void operator+=(const Fuc &);
	Db calc(Db);
} F[kMaxn];

namespace lct {
	struct Node {
		int fa, ch[2], rev;
		Fuc sum;
	} T[kMaxn];
#define FA(u) T[u].fa
#define LSON(u) T[u].ch[0]
#define RSON(u) T[u].ch[1]
	void Accs(int u);
	int FindRt(int u);
	void Maintn(int u);
	void Splay(int u);
	inline void Revrs(int u) { std::swap(LSON(u), RSON(u)); T[u].rev ^= 1; }
	inline void MkRt(int u) { Accs(u); Splay(u); Revrs(u); }
	inline void Link(int u, int v) { MkRt(u); FA(u) = v; }
	inline void Split(int u, int v) { MkRt(u); Accs(v); Splay(u); }
	inline void Cut(int u, int v) { Split(u, v); FA(v) = RSON(u) = 0; }
}

int n, m;
char op[10];

int main() {
	scanf("%d%d%*s", &n, &m);
	Db a, b;
	for (int i = 1, f; i <= n; ++i) {
		scanf("%d%lf%lf", &f, &a, &b); F[i].set(f, a, b); lct::T[i].sum = F[i];
	}
	for (int f, u, v; m--; ) {
		scanf("%s%d", op, &u); ++u;
		using namespace lct;
		if (op[0] == 'a' || op[0] == 'd') {
			scanf("%d", &v); ++v;
			if (op[0] == 'a') Link(u, v); else Cut(u, v);
		} if (op[0] == 'm') {
			scanf("%d%lf%lf", &f, &a, &b); Splay(u); F[u].set(f, a, b); Maintn(u);
		} if (op[0] == 't') {
			scanf("%d%lf", &v, &a); ++v;
			MkRt(u);
			if (FindRt(v) != u) puts("unreachable");
			else printf("%.10f\n", T[u].sum.calc(a));
		}
	}
	return 0;
}

namespace lct {
	inline bool IsRt(int u) { return LSON(FA(u)) != u && RSON(FA(u)) != u; }
	inline int Relat(int u) { return RSON(FA(u)) == u; }
	void PushDw(int u) {
		if (T[u].rev) {
			if (LSON(u)) Revrs(LSON(u));
			if (RSON(u)) Revrs(RSON(u));
			T[u].rev = 0;
		}
	}
	void Maintn(int u) {
		T[u].sum = F[u];
		if (LSON(u)) T[u].sum += T[LSON(u)].sum;
		if (RSON(u)) T[u].sum += T[RSON(u)].sum;
	}
	void Rotat(int u) {
		int prf = FA(u), ff = FA(prf), r = Relat(u);
		if (!IsRt(prf)) T[ff].ch[Relat(prf)] = u;
		if (T[u].ch[r ^ 1]) FA(T[u].ch[r ^ 1]) = prf;
		FA(u) = ff, FA(prf) = u, T[prf].ch[r] = T[u].ch[r ^ 1], T[u].ch[r ^ 1] = prf, Maintn(prf);
	}
	void Splay(int u) {
		static int S[kMaxn];
		int top = 0;
		S[top++] = u;
		for (int v = u; !IsRt(v); v = FA(v)) S[top++] = FA(v);
		while (top) PushDw(S[--top]);
		while (!IsRt(u)) {
			if (IsRt(FA(u))) Rotat(u);
			else if (Relat(u) == Relat(FA(u))) { Rotat(FA(u)), Rotat(u); }
			else { Rotat(u); Rotat(u); }
		} Maintn(u);
	}
	void Accs(int u) {
		for (int v = 0; u; u = FA(v = u)) { Splay(u); RSON(u) = v, Maintn(u); }
	}
	int FindRt(int u) {
		Accs(u); Splay(u);
		for (; LSON(u); u = LSON(u)) PushDw(u);
		Splay(u); return u;
	}
}

void Fuc::set(int tp, Db a, Db b) {
	memset(A, 0, sizeof A);
	if (tp == 3) { A[0] = b, A[1] = a; }
	if (tp == 1) {
		Db pa = 1;
		for (int i = 0, f = 0; i < kLen; ++i, f = (f + 1) % 4, pa *= a)
			A[i] = (f & 1 ? cos(b) : sin(b)) * (f < 2 ? 1 : -1) * pa;
	}
	if (tp == 2) {
		Db pa = 1;
		b = exp(b);
		for (int i = 0; i < kLen; ++i, pa *= a) A[i] = pa * b;
	}
/*	printf("ser: ");
	for (int i = 0; i < 5; ++i) printf("%.5lf ", A[i]); puts(""); */
}

void Fuc::operator+=(const Fuc & f) {
	for (int i = 0; i < kLen; ++i) A[i] += f.A[i];
}

Db Fuc::calc(Db x) {
	Db res = 0, px = 1, fac = 1;
	for (int i = 0; i < kLen; ++i, px *= x, fac *= i) res += A[i] * px / fac;
	return res;
}
