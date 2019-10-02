#include <algorithm>
// #include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>
// #include <cmath>
#include <map>
#include <queue>
#include <set>
#include <vector>

const int kMaxn = 105;

int t, n, m;

void Solve();

int main() {
	int t;
	scanf("%d", &t);
	while (t--) Solve();
	return 0;
}

int deg[kMaxn << 1], fa[kMaxn << 1];
char mp[kMaxn][kMaxn];

inline int Find(int x) { return fa[x] == x ? x : (fa[x] = Find(fa[x])); }
inline void Merge(int x, int y) { fa[Find(x)] = Find(y); }

void Solve() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n + m; i++) {
		deg[i] = 0, fa[i] = i;
		// for (int j = i; j < n + m; j++)
			// A[i][j] = A[j][i] = 0;
	}
	for (int i = 0; i < n; i++) {
		scanf("%s", mp[i]);
		for (int j = 0; j < m; j++) {
			if (mp[i][j] == 'o') {
				Merge(i, n + j);
				// A[i][n + j] = A[n + j][i] = 1;
				++deg[i], ++deg[n + j];
			}
		}
	}
	int odd = 0, fa = -1;
	for (int i = 0; i < n + m; i++) {
		if (!deg[i]) continue;
		if (~fa) {
			if (Find(i) != fa) return (void)puts("Impossible");
		} else fa = Find(i);
		if (deg[i] & 1) ++odd;
	}
	if (odd && odd != 2) puts("Impossible");
	else puts("Possible");
}