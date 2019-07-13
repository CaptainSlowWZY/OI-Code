#include <cstdio>

const int kMaxn = 1e5 + 10;

int n, deg[kMaxn];

int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		++deg[u], ++deg[v];
	}

	int f = 0;
	for (int i = 1; i <= n; i++) f |= deg[i] == 2;

	puts(f ? "NO" : "YES"); 
	return 0;
}
