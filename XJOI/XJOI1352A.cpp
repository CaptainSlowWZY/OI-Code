#include <algorithm>
#include <cassert>
#include <cstdio>
#include <set>

typedef std::multiset<int> Mys;

const int kMaxn = 1e5 + 5, kInf = 0x3f3f3f3f;

int n, m;
int V[kMaxn], A[kMaxn], B[kMaxn];
char S[10];

namespace lct {
	struct Node {
		int fa, ch[2], rev;
		int pre, suf, sv, med, ald;
		Mys vir, vrd;
	} T[kMaxn];
	int rt;
#define LSON(u) T[u].ch[0]
#define RSON(u) T[u].ch[1]
#define FA(u) T[u].fa
	void Accs(int u);
	void Maintn(int u);
	void Splay(int u);
	inline void Revrs(int u) { std::swap(LSON(u), RSON(u)), std::swap(T[u].pre, T[u].suf), T[u].rev ^= 1; }
	inline void MkRt(int u) { Accs(u); Splay(u); Revrs(u); rt = u; }
	inline void Link(int u, int v) { MkRt(u), MkRt(v); FA(u) = v, T[v].vir.insert(T[u].pre); T[v].vrd.insert(T[u].ald); Maintn(v); }
	inline void Cut(int u, int v) { MkRt(u); Accs(v); Splay(u); RSON(u) = FA(v) = 0; Maintn(u); }
	void Out() {
		for (int i = 1; i <= n; ++i) {
			printf(" node %d, fa %d, ch(%d, %d), pre %d, suf %d, sv %d, med %d, ald %d\n",
				i, FA(i), LSON(i), RSON(i), T[i].pre, T[i].suf, T[i].sv, T[i].med, T[i].ald);
			printf("   vir list:");
			for (auto x : T[i].vir) printf(" %d", x);
			puts("");
			printf("   vrd list:");
			for (auto x : T[i].vrd) printf(" %d", x);
			puts("");
		}
	} 
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; ++i) scanf("%d%d", A + i, B + i);
	using namespace lct;
	T[0].pre = T[0].suf = -kInf, rt = 1;
	for (int i = 1; i <= n; ++i) scanf("%d", V + i); 
	for (int i = 1; i < n; ++i) Link(A[i], B[i]); 
//	Accs(1); Splay(1);
	MkRt(rt); printf("%d\n", T[rt].ald);
	for (int a, b, c, d; m--; ) {
		scanf("%s", S);
		if (S[0] == 'M') {
			scanf("%d%d", &a, &b);
		//	Accs(a); Splay(a);
			MkRt(a);
			V[a] = b; Maintn(a);
		} else {
			scanf("%d%d%d%d", &a, &b, &c, &d); Cut(a, b); Link(c, d);
		} // Accs(1), Splay(1);
		MkRt(rt); printf("%d\n", T[rt].ald);
	} return 0;
}

void UpdMax(int x, int & m1, int & m2) {
	if (x > m1) { m2 = m1, m1 = x; } else m2 = std::max(m2, x);
}

inline int Max(const Mys & st) { return st.empty() ? 0 : *st.rbegin(); }

inline int Max2(const Mys & st) {
	if (st.empty()) return 0;
	if ((int)st.size() == 1) return Max(st);
	auto it = st.rbegin();
	int res = *it;
	return res + *++it;
}

namespace lct {
	inline bool IsRt(int u) { return LSON(FA(u)) != u && RSON(FA(u)) != u; }
	inline int Relat(int u) { return RSON(FA(u)) == u; }
	void Maintn(int u) {
		T[u].suf = std::max(T[RSON(u)].suf, V[u] + T[RSON(u)].sv + std::max({T[LSON(u)].suf, 0, Max(T[u].vir)}));
		T[u].pre = std::max(T[LSON(u)].pre, V[u] + T[LSON(u)].sv + std::max({T[RSON(u)].pre, 0, Max(T[u].vir)}));
		T[u].sv = V[u] + T[LSON(u)].sv + T[RSON(u)].sv;
		int m1 = 0, m2 = 0;
		UpdMax(T[LSON(u)].suf, m1, m2); UpdMax(T[RSON(u)].pre, m1, m2); UpdMax(Max(T[u].vir), m1, m2);
		T[u].ald = std::max({T[LSON(u)].ald, T[RSON(u)].ald, T[u].med = std::max(m1 + m2, Max2(T[u].vir)) + V[u], Max(T[u].vrd)});
	}
	void Rot(int u) {
		int prf = FA(u), ff = FA(prf), r = Relat(u);
		if (!IsRt(prf)) T[ff].ch[Relat(prf)] = u;
		if (T[u].ch[r ^ 1]) FA(T[u].ch[r ^ 1]) = prf;
		FA(u) = ff, FA(prf) = u, T[prf].ch[r] = T[u].ch[r ^ 1];
		T[u].ch[r ^ 1] = prf; Maintn(prf);
	}
	void PushDw(int u) {
		if (!T[u].rev) return;
		if (LSON(u)) Revrs(LSON(u));
		if (RSON(u)) Revrs(RSON(u));
		T[u].rev = 0;
	}
	void Splay(int u) {
		static int S[kMaxn];
		int top = 0;
		S[top++] = u;
		for (int v = u; !IsRt(v); v = FA(v)) S[top++] = FA(v);
		while (top) PushDw(S[--top]);
		while (!IsRt(u)) {
			if (IsRt(FA(u))) Rot(u);
			else if (Relat(u) == Relat(FA(u))) { Rot(FA(u)), Rot(u); }
			else { Rot(u), Rot(u); }
		} Maintn(u);
	}
	void Accs(int u) {
		for (int v = 0; u; u = FA(v = u)) {
			Splay(u);
			if (RSON(u)) { T[u].vir.insert(T[RSON(u)].pre), T[u].vrd.insert(T[RSON(u)].ald); }
			if (v) {
			//	assert(T[u].vir.find(T[v].pre) != T[u].vir.end());
			//	assert(T[u].vrd.find(T[v].ald) != T[u].vrd.end());
				T[u].vir.erase(T[u].vir.find(T[v].pre)), T[u].vrd.erase(T[u].vrd.find(T[v].ald));
			}
			RSON(u) = v; Maintn(u);
		}
	}
}
