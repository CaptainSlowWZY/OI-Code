// ZJOI 2016
#include <cstdio>
#include <cctype>
#include <algorithm>

#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])
#define fa(_) (T[_].fa)

const int kMaxn = 2e5 + 10;

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			register char ch = getchar(); x = 0;
			for (; !isdigit(ch); ch = getchar());
			for (; isdigit(ch); ch = getchar())
				x = (x << 3) + (x << 1) + (ch ^ '0');
		}
}
namespace lct {
	struct Node {
		int val, sz, fa, ch[2];
	} T[kMaxn << 1];
	int size;

#ifdef DEBUG
	void Debug() {
		puts("\n ###### DEBUG ######");
		for (int i = 1; i <= size; i++) {
			printf("   Node %d: val %d, sz %d, fa %d, lson %d, rson %d\n",
					i, T[i].val, T[i].sz, T[i].fa, lson(i), rson(i));
		}
		puts(" -------------------\n");
	}
#endif
	inline int NewNode(int v) {
		T[++size].val = v;
		T[size].sz = v;
		return size;
	}
	inline void Maintain(int u) {
		T[u].sz = T[u].val + T[lson(u)].sz + T[rson(u)].sz;
	}
	void Splay(int u);
	int Access(int u);
	inline void Cut(int u) {
		Access(u);
		Splay(u);
		fa(lson(u)) = 0, lson(u) = 0;
		Maintain(u);
	}
	inline void Link(int u, int v) {
		Splay(u);
		fa(u) = v;
	}
}

struct Oper {
	int pos, tag, u, v;
	
	bool operator<(const Oper & o) const {
		return pos == o.pos ? tag < o.tag : pos < o.pos;
	}
} O[kMaxn];

int n, m, last, totp, totq, toto, vir[kMaxn], L[kMaxn], R[kMaxn], ans[kMaxn];

int main() {
	using fast_io::Read;

	Read(n), Read(m);
	vir[totp = 1] = lct::NewNode(1);
	last = lct::NewNode(0);
	lct::Link(2, 1);
	L[1] = 1, R[1] = n;
	for (int i = 0, o, x, y, z; i < m; i++) {
		Read(o);
		using namespace lct;
		if (!o) {
			Read(x), Read(y);
			vir[++totp] = NewNode(1);
			Link(vir[totp], last);
			L[totp] = x, R[totp] = y;
		}
		else if (o == 1) {
			Read(x), Read(y), Read(z);
			x = std::max(x, L[z]);
			y = std::min(y, R[z]);
			if (x > y) continue;
			int np = NewNode(0);
			Link(np, last);
			O[toto++] = (Oper){x, -1, np, vir[z]};
			O[toto++] = (Oper){y + 1, -1, np, last};
			last = np;
		}
		else {
			Read(x), Read(y), Read(z);
			O[toto++] = (Oper){x, totq++, vir[y], vir[z]};
		}
	}
	
	std::sort(O, O + toto);
	int j = 0;
	for (int i = 1; i <= n; i++) {
		for (int ret, l; j < toto && O[j].pos == i; j++) {
			using namespace lct;
//			printf(" O[%d], pos = %d, tag = %d, u = %d, v = %d\n", j, O[j].pos, O[j].tag, O[j].u, O[j].v);
			if (O[j].tag < 0) {
				Cut(O[j].u);
				Link(O[j].u, O[j].v);
			}
			else {
				Access(O[j].u), Splay(O[j].u), ret = T[O[j].u].sz;
				l = Access(O[j].v), Splay(O[j].v), ret += T[O[j].v].sz;
	//			printf(" lca(%d, %d) = %d\n", O[j].u, O[j].v, l);
				Access(l), Splay(l), ans[O[j].tag] = ret - 2 * T[l].sz;
			}
		}
	}

	for (int i = 0; i < totq; i++) printf("%d\n", ans[i]);
	return 0;
}

namespace lct {
	inline bool IsRoot(int u) {
		return lson(fa(u)) != u && rson(fa(u)) != u;
	}
	inline int Relat(int u) {
		return rson(fa(u)) == u;
	}
	void Rotate(int u) {
		int prf = fa(u), ff = fa(prf), r = Relat(u);
		fa(u) = ff;
		if (!IsRoot(prf)) T[ff].ch[Relat(prf)] = u;
		if (T[u].ch[r ^ 1]) fa(T[u].ch[r ^ 1]) = prf;
		T[prf].ch[r] = T[u].ch[r ^ 1];
		T[prf].fa = u, T[u].ch[r ^ 1] = prf;
		Maintain(prf);
	}
	void Splay(int u) {
		while (!IsRoot(u)) {
			if (IsRoot(fa(u))) Rotate(u);
			else if (Relat(fa(u)) == Relat(u)) {
				Rotate(fa(u)), Rotate(u);
			}
			else {
				Rotate(u), Rotate(u);
			}
		}
		Maintain(u);
	}
	int Access(int u) {
		int v = 0;
		for (; u; u = fa(v = u)) {
			Splay(u);
			rson(u) = v;
			Maintain(u);
		}
		return v;
	}
}
