#include <algorithm>
#include <cstdio>

int n, back;
int deg[60], G[60][60], ans[10000];
char IN[10];

inline int Id(char ch) {
	return ch <= 'Z' ? ch - 'A' : ch - 'a' + 26;
}
void Dfs(int);

int main() {
	scanf("%d", &n);
	int rt = 100;
	for (int i = 0, u, v; i < n; i++) {
		scanf("%s", IN);
		u = Id(IN[0]), v = Id(IN[1]);
		if (G[u][v]) continue;
		G[u][v] = G[v][u] = 1;
		++deg[u], ++deg[v];
		rt = std::min(u, rt);
	}

	int odd = 0;
	for (int i = 0; i < 52; i++)
		if (deg[i] & 1) ++odd;
	if (!odd) Dfs(rt);
	else if (odd == 2) {
		for (int i = 0; i < 52; i++)
			if (deg[i] & 1) {
				Dfs(i); break;
			}
	} else {
		puts("No Solution");
		return 0;
	}
	
	while (back--) {
		putchar((ans[back] < 26 ? 'A' : 'a' - 26) + ans[back]);
	} putchar('\n');
	return 0;
}

void Dfs(int u) {
	for (int v = 0; v < 52; v++) {
		if (!G[u][v]) continue;
		G[u][v] = G[v][u] = 0;
		Dfs(v);
	}
	ans[back++] = u;
}
