#include <cstdio>
#include <set>

typedef std::set<int> Si;

#define SZ(_) (int)_.size()
#define pch putchar
#define FORS(I, _) for (Si::iterator I = _.begin(); I != _.end(); ++I)

const int kMaxn = 1e5 + 5;

int n, m, q, fa[kMaxn];
Si L[kMaxn];

inline int Find(int x) { return fa[x] == x ? x : (fa[x] = Find(fa[x])); }

int main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int x, y; m--; ) { scanf("%d%d", &x, &y); L[x].insert(y); L[y].insert(x); }
	for (int i = 1; i <= n; ++i) fa[i] = i;
	for (int fail, x, y; q--; ) {
		scanf("%d%d", &x ,&y);
		x = Find(x), y = Find(y), fail = 0;
		if (SZ(L[x]) > SZ(L[y])) std::swap(x, y);
		FORS(i, L[x]) if (Find(*i) == y) { fail = 1; break; }
		if (fail) { pch('0'); continue; }
		FORS(i, L[x]) L[y].insert(*i);
		fa[x] = y, pch('1');
	} pch('\n'); return 0;
}
