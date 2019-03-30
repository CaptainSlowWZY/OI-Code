#include <cstdio>
#include <algorithm>

typedef std::pair<int, int> Pii;

const int kMaxn = 1e6 + 10;

int n, totid, totr, tote, id[kMaxn << 1], fa[kMaxn << 1];
Pii R[kMaxn], E[kMaxn];

inline int Find(int x) {
	return fa[x] == x ? x : fa[x] = Find(fa[x]);
}
inline void Merge(int x, int y) {
	x = Find(x), y = Find(y), fa[x] = y;
}
inline int Id(int x) {
	return std::lower_bound(id, id + totid, x) - id + 1;
}

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d", &n);
		totid = tote = totr = 0;
		for (int i, j, e; n--; ) {
			scanf("%d%d%d", &i, &j, &e);
			id[totid++] = i, id[totid++] = j;
			if (e) E[tote++] = Pii(i, j);
			else R[totr++] = Pii(i, j);
		}
		std::sort(id, id + totid);
		totid = std::unique(id, id + totid) - id;
		for (int i = 1; i <= totid; i++) fa[i] = i;
		for (int i = 0; i < tote; i++) {
			Merge(Id(E[i].first), Id(E[i].second));
		}
		int fail = 0;
		for (int i = 0; i < totr; i++) {
			if (Find(Id(R[i].first)) == Find(Id(R[i].second))) {
				fail = 1;
				break;
			}
		}
		puts(fail ? "NO" : "YES");
	}
	return 0;
}
