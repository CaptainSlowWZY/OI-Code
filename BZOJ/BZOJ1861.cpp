#include <cstdio>
#include <cstdlib>
#include <cassert>

const int kMaxn = 8e4 + 10;

int n, m;
char IN[20];

namespace treap {
	struct Node {
		int rkey, fa, ch[2], sz;
	} T[kMaxn];
#define FA(_) (T[_].fa)
#define LSON(_) (T[_].ch[0])
#define RSON(_) (T[_].ch[1])
	int root = 0;
	int Merge(int rt1, int rt2);
	int Rank(int u);
	void Split(int u, int k, int & rt1, int & rt2);
	inline int Merge(int rt1, int rt2, int rt3) {
		return Merge(rt1, Merge(rt2, rt3));
	}
	inline void Split(int p, int t, int & rt1, int & rt2, int & rt3) {
		Split(root, p, rt1, rt3); Split(rt1, p - t, rt1, rt2);
	}
}

int main() {
	srand(19260817);
	scanf("%d%d", &n, &m);
	using namespace treap;
	for (int i = 1; i <= n; i++) {
		T[i].rkey = rand(), T[i].sz = 1;
	}
	for (int i = 0, ai; i < n; i++) {
		scanf("%d", &ai); root = Merge(root, ai);
	}

	for (int s, t, rt1, rt2, rt3, rt4, pos; m--; ) {
		scanf("%s%d", IN, &s);
		using namespace treap;
		if (IN[0] != 'Q') pos = Rank(s);
		switch (IN[0]) {
			case 'T' :
				Split(pos, 1, rt1, rt2, rt3);
				assert(rt2 == s);
				root = Merge(s, rt1, rt3);
				break;
			case 'B' :
				Split(pos, 1, rt1, rt2, rt3);
				assert(rt2 == s);
				root = Merge(rt1, rt3, s);
				break;
			case 'I' :
				scanf("%d", &t);
				if (!t) break;
				if (t == -1) {
					Split(pos, 2, rt1, rt2, rt3);
					Split(rt2, 1, rt2, rt4);
					root = Merge(rt1, Merge(s, rt2), rt3);
				} else {
					Split(pos + 1, 2, rt1, rt2, rt3);
					Split(rt2, 1, rt4, rt2);
					root = Merge(rt1, Merge(rt2, s), rt3);
				} break;
			case 'A' :
				printf("%d\n", pos - 1); break;
			case 'Q' :
				Split(s, 1, rt1, rt2, rt3);
				printf("%d\n", rt2);
				root = Merge(rt1, rt2, rt3);
		}
	} return 0;
}

namespace treap {
	void Maintain(int u) {
		T[u].sz = 1 + T[LSON(u)].sz + T[RSON(u)].sz;
		if (LSON(u)) FA(LSON(u)) = u;
		if (RSON(u)) FA(RSON(u)) = u;
	}
	void Split(int u, int k, int & rt1, int & rt2) {
		if (!u) return (void)(rt1 = rt2 = 0);
		if (T[LSON(u)].sz + 1 <= k) {
			rt1 = u; Split(RSON(u), k - T[LSON(u)].sz - 1, RSON(rt1), rt2);
		} else {
			rt2 = u; Split(LSON(u), k, rt1, LSON(rt2));
		} Maintain(u);
	}
	int Merge(int rt1, int rt2) {
		if (!rt1 || !rt2) return rt1 + rt2;
		if (T[rt1].rkey < T[rt2].rkey) {
			RSON(rt1) = Merge(RSON(rt1), rt2); Maintain(rt1);
			return rt1;
		} else {
			LSON(rt2) = Merge(rt1, LSON(rt2)); Maintain(rt2);
			return rt2;
		}
	}
	inline int Relat(int u) { return RSON(FA(u)) == u; }
	int Rank(int u) {
		int res = T[LSON(u)].sz;
		for (; u != root; u = FA(u)) {
			if (Relat(u)) res += 1 + T[LSON(FA(u))].sz;
		} return res + 1;
	}
}
