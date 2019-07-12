#include <algorithm>
#include <cstdio>

const int kMaxn = 150010;

typedef int IAr[kMaxn];

int n, m;
IAr re, num, sum;

int Find(int u) { return re[u] == u ? u : re[u] = Find(re[u]); }
void AddEdge(int u, int v);
namespace lct {
	struct Node {
		int tot;
		int fa, ch[2];
		int rev;
	} T[kMaxn];
#define fa(_) (T[_].fa)
#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])

	inline void Maintain(int u) {
		T[u].tot = sum[u] + T[lson(u)].tot + T[rson(u)].tot;
	}
	void Splay(int);
	void Access(int);
	int Calc(int u, int v);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", num + i);
		sum[i] = num[i];
		re[i] = i;
	}

	for (int t, u, v, ff; m--; ) {
		using namespace lct;
		scanf("%d%d%d", &t, &u, &v);	   
		if (t == 1) AddEdge(u, v);
		else if (t == 2) {
			Access(ff = Find(u));
			Splay(ff);
			sum[ff] -= num[u];
			sum[ff] += num[u] = v;
			Maintain(ff);
		} else printf("%d\n", Calc(u, v));
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
		fa(prf) = u; T[u].ch[r ^ 1] = prf;
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
				Rotate(fa(u)); Rotate(u);
			} else {
				Rotate(u); Rotate(u);
			}
		}
		Maintain(u);
	}
	void Access(int u) {
		for (int v = 0; u; v = u, u = fa(v) = Find(fa(u))) {
			Splay(u); rson(u) = v; Maintain(u);
		}
	}
	inline void MakeRoot(int u) {
		Access(u); Splay(u); Reverse(u);
	}
	int FindRoot(int u) {
		Access(u); Splay(u);
		for (; lson(u); u = lson(u));
		Splay(u);
		return u;
	}
	void SetFa(int u, int f) {
		re[u] = f, sum[f] += sum[u];
		if (lson(u)) SetFa(lson(u), f);
		if (rson(u)) SetFa(rson(u), f);
	}
	int Calc(int u, int v) {
		u = Find(u), v = Find(v);
		MakeRoot(u);
		if (FindRoot(v) != u) return -1;
		Access(v); Splay(v);
		return T[v].tot;
	}
}

void AddEdge(int u, int v) {
	using namespace lct;
	u = Find(u), v = Find(v);
	if (u == v) return;
	MakeRoot(u);
	if (FindRoot(v) != u) return (void)(fa(u) = v);
	if (rson(u)) {
		SetFa(rson(u), u);
		rson(u) = 0;
	}
}
