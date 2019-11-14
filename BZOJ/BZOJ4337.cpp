#include <algorithm>
#include <cstdio>
#include <vector>

#define pb push_back
#define FORV(TP, I, _) for (std::vector<TP>::iterator I = _.begin(); I != _.end(); ++I)
#define FORCV(TP, I, _) for (std::vector<TP>::const_iterator I = _.begin(); I != _.end(); ++I)

typedef unsigned UI;

const int kMaxn = 55;
const int kP[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
	31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
	73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
	127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
	179, 181, 191, 197, 199, 211, 223, 227, 281, 283,
	293, 307, 311, 313, 317};

struct Tree {
	int n, sz[kMaxn];
	std::vector<int> G[kMaxn], ct;
	std::vector<UI> ha;
	void in();
	void dfs(int, int);
	UI hash(int, int);
	bool operator==(const Tree & t) const;
} T[kMaxn];

int m, fa[kMaxn];

inline int Find(int x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }

int main() {
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) { T[i].in(); fa[i] = i; }
	for (int i = 0; i < m; ++i) {
		if (Find(i) != i) continue;
		for (int j = i + 1; j < m; ++j) if (T[i] == T[j]) fa[Find(j)] = fa[Find(i)];
	}
	for (int i = 0; i < m; ++i) printf("%d\n", Find(i) + 1);
	return 0;
}

void Tree::dfs(int u, int fa) {
	sz[u] = 1;
	int mx = 0;
	FORV(int, v, G[u]) if (*v != fa) { dfs(*v, u); sz[u] += sz[*v], mx = std::max(mx, sz[*v]); }
	mx = std::max(mx, n - sz[u]);
	if (mx * 2 <= n) ct.pb(u);
}

UI Tree::hash(int u, int fa) {
	sz[u] = 1;
	UI val = 1;
	FORV(int, v, G[u]) if (*v != fa) { val += hash(*v, u) * kP[sz[*v] - 1], sz[u] += sz[*v]; }
	return val;
}
		
void Tree::in() {
	scanf("%d", &n);
	int rt = 1;
	for (int i = 1, fa; i <= n; ++i) {
		scanf("%d", &fa);
		if (!fa) { rt = i; continue; }
		G[fa].pb(i); G[i].pb(fa);
	} dfs(rt, 0);
	FORV(int, u, ct) ha.pb(hash(*u, 0));
}

bool Tree::operator==(const Tree & t) const {
	FORCV(UI, i, ha) FORCV(UI, j, t.ha) if (*i == *j) return true;
	return false;
}
