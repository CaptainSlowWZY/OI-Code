#include <cstdio>

int n, D[1000010];

int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v); ++D[u], ++D[v];
	}
	for (int i = 1; i <= n; ++i)
		if (!(D[i] & 1)) { puts("Alice"); return 0; }
	puts("Bob"); return 0;
}
