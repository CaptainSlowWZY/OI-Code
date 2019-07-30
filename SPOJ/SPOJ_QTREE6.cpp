#include <algorithm>
#include <cstdio>
#include <vector>

#define pb push_back
#define C (col[x])

const int kMaxn = 1e5 + 10;

int n, m;
int col[kMaxn], fa[kMaxn];
std::vector<int> G[kMaxn];

struct LinkCutTree {
	struct Node {
		int fa, ch[2], sz, vsz;
	} T[kMaxn];
#define fa(_) (T[_].fa)
#define lson(_) (T[_].ch[0])
#define rson(_) (T[_].ch[1])
	int relat(int u) { return rson(fa(u)) == u; }
	bool isroot(int u) {
		return lson(fa(u)) != u && rson(fa(u)) != u;
	}
	void maintain(int u) {
		T[u].sz = 1 + T[lson(u)].sz + T[rson(u)].sz + T[u].vsz;
	}
	int findroot(int u);
	void access(int u);
	void cut(int u);
	void link(int u);
	void splay(int u);
	void rotate(int u);
} lct[2];

void Dfs(int);

int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		G[u].pb(v), G[v].pb(u);
	}

	G[n + 1].pb(1);
	Dfs(n + 1);
	scanf("%d", &m);
	for (int tp, x; m--; ) {
		scanf("%d%d", &tp, &x);
		if (tp) {
		//	if (x == 1) continue;
			lct[C].cut(x);
			lct[C ^= 1].link(x);
		} else {
			int rt = lct[C].findroot(x);
			printf("%d\n", lct[C].T[lct[C].T[rt].ch[1]].sz);
		}
	}
	return 0;
}

void Dfs(int u) {
	for (auto v : G[u]) {
		if (v == fa[u]) continue;
		lct[0].T[v].fa = u, fa[v] = u;
		Dfs(v);
		lct[0].T[u].vsz += lct[0].T[v].sz;
	}
	lct[0].maintain(u);
}

int LinkCutTree::findroot(int u) {
	access(u); splay(u);
	for (; lson(u); u = lson(u));
	splay(u);
	return u;
}

void LinkCutTree::rotate(int u) {
	int prf = fa(u), ff = fa(prf), r = relat(u);
	fa(u) = ff;
	if (!isroot(prf)) T[ff].ch[relat(prf)] = u;
	if (T[u].ch[r ^ 1]) fa(T[u].ch[r ^ 1]) = prf;
	T[prf].ch[r] = T[u].ch[r ^ 1];
	T[u].ch[r ^ 1] = prf, fa(prf) = u;
	maintain(prf);
}

void LinkCutTree::splay(int u) {
	while (!isroot(u)) {
		if (isroot(fa(u))) rotate(u);
		else if (relat(u) == relat(fa(u))) {
			rotate(fa(u)), rotate(u);
		} else {
			rotate(u), rotate(u);
		}
	}
	maintain(u);
}

void LinkCutTree::access(int u) {
	for (int v = 0; u; u = fa(v = u)) {
		splay(u);
		T[u].vsz += T[rson(u)].sz - T[v].sz;
		rson(u) = v; maintain(u);
	}
}

void LinkCutTree::link(int u) {
	splay(u);
	int f = fa(u) = fa[u];
	access(f); splay(f);
	T[f].vsz += T[u].sz;
	maintain(f);
}

void LinkCutTree::cut(int u) {
	access(u); splay(u);
	fa(lson(u)) = 0, lson(u) = 0;
	maintain(u);
}
