#include <algorithm>
#include <cstdio>
#include <map>

const int kMaxn = 1e4 + 5;

struct Node {
	int val, maxv;
	int fa, ch[2], rev;
	Node() {}
	Node(int v_) : 
		val(v_), maxv(v_) { fa = ch[1] = ch[0] = rev = 0; }
};
struct LinkCutTree {
	Node T[kMaxn];
#define fa(_) (T[_].fa)
#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])
/*	void debug() const {
		for (int i = 1; i <= 4; i++) {
			printf(" %d val %d, maxv %d; fa %d, ls %d, rs %d; rev %d\n",
					i, T[i].val, T[i].maxv, fa(i), lson(i), rson(i), T[i].rev);
		}
	}*/
	void access(int u);
	int findroot(int u);
	bool link(int u, int v);
	void pushdown(int u);
	void rotate(int u);
	void splay(int u);
	bool isroot(int u) const {
		return lson(fa(u)) != u && rson(fa(u)) != u;
	}
	int relat(int u) const { return rson(fa(u)) == u; }
	void reverse(int u) {
		std::swap(lson(u), rson(u)); T[u].rev ^= 1;
	}
	void maintain(int u) {
		T[u].maxv = std::max(T[u].val,
				std::max(T[lson(u)].maxv, T[rson(u)].maxv));
	}
	void makeroot(int u) { access(u); splay(u); reverse(u); }
	void split(int u, int v) { makeroot(u); access(v); splay(v); }
	void cut(int u, int v) {
		split(u, v); lson(v) = fa(u) = 0; maintain(v);
	}
} lct[10];

int n, m, C, K;
int deg[10][kMaxn];
std::map<int, int> G[kMaxn];

int main() {
	scanf("%d%d%d%d", &n, &m, &C, &K);
	for (int i = 1, vi; i <= n; i++) {
		scanf("%d", &vi);
		for (int j = 0; j < C; j++)
			lct[j].T[i] = Node(vi);
	}
	for (int u, v, w; m--; ) {
		scanf("%d%d%d", &u, &v, &w);
		if (u > v) std::swap(u, v);
		G[u][v] = w;
		lct[w].link(u, v);
		++deg[w][u], ++deg[w][v];
	}

	for (int o, tp, u, v, w; K--; ) {
		scanf("%d", &tp);
		switch (tp) {
			case 0 :
				scanf("%d%d", &u, &w);
				for (int i = 0; i < C; i++) {
					lct[i].split(u, u);
					lct[i].T[u].val = w;
				}
				break;
			case 1 :
				scanf("%d%d%d", &u, &v, &w);
			//	if (u == v) { puts("Success."); break; }
				if (u > v) std::swap(u, v);
				if (!G[u].count(v)) {
					puts("No such edge.");
					break;
				}
				if (G[u][v] == w) { puts("Success."); break; }
				if (deg[w][u] == 2 || deg[w][v] == 2) {
					puts("Error 1.");
					break;
				}
				if (lct[w].link(u, v)) {
					lct[o = G[u][v]].cut(u, v);
					--deg[o][u], --deg[o][v];
					++deg[G[u][v] = w][u], ++deg[w][v];
					puts("Success.");
				} else puts("Error 2.");
				break;
			default :
				scanf("%d%d%d", &w, &u, &v);
			//	printf(" lct[%d] makeroot %d\n", w, u);
				lct[w].makeroot(u);
			//	printf(" lct[%d] find root (%d) %d\n", w, v,
			//			lct[w].findroot(v));
				if (lct[w].findroot(v) != u) {
					puts("-1");
				} else printf("%d\n", lct[w].T[u].maxv);
		}
	}
	return 0;
}

void LinkCutTree::rotate(int u) {
	int prf = fa(u), ff = fa(prf), r = relat(u);
	if (!isroot(prf)) T[ff].ch[relat(prf)] = u;
	if (T[u].ch[r ^ 1]) fa(T[u].ch[r ^ 1]) = prf;
	T[prf].ch[r] = T[u].ch[r ^ 1], T[u].ch[r ^ 1] = prf;
	fa(prf) = u, fa(u) = ff; maintain(prf);
}

void LinkCutTree::pushdown(int u) {
	if (!T[u].rev) return;
	if (lson(u)) reverse(lson(u));
	if (rson(u)) reverse(rson(u));
	T[u].rev = 0;
}

void LinkCutTree::splay(int u) {
	static int S[kMaxn];
	int top = 0;
	S[top++] = u;
	for (int v = u; !isroot(v); v = fa(v)) S[top++] = fa(v);
	while (top) pushdown(S[--top]);
	while (!isroot(u)) {
		if (isroot(fa(u))) rotate(u);
		else if (relat(u) == relat(fa(u))) {
			rotate(fa(u)); rotate(u);
		} else {
			rotate(u); rotate(u);
		}
	}
	maintain(u);
}

void LinkCutTree::access(int u) {
	for (int v = 0; u; u = fa(v = u)) {
		splay(u); rson(u) = v; maintain(u);
	}
}

int LinkCutTree::findroot(int u) {
	access(u); splay(u);
	for (; lson(u); u = lson(u)) pushdown(u);
	splay(u);
	return u;
}

bool LinkCutTree::link(int u, int v) {
	makeroot(u);
	if (findroot(v) == u) return false;
	fa(u) = v;
	return true;
}
