#include <bits/stdc++.h>

const int MAXM = 2e5 + 10;

struct Edge {
	int to, next;
} E[MAXM << 1];

int N, M, K, tote, tot, last[MAXM << 1], flag[MAXM << 1], O[MAXM << 1], fa[MAXM << 1];

inline void add_edge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, last[v]}, last[v] = tote;
}
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void merge(int x) {
	++tot, flag[x] = 0;
	for (int e = last[x], v = E[e].to; e; v = E[e = E[e].next].to) {
		if (flag[v]) continue;
		v = find(v), x = find(x);
		if (v ^ x) --tot, fa[v] = x;
	}
}

int main() {
	scanf("%d%d", &N, &M);
	for (int u, v; M--; ) {
		scanf("%d%d", &u, &v);
		add_edge(u, v);
	}
	scanf("%d", &K);
	for (int i = 0; i < K; i++) {
		scanf("%d", O + i);
		flag[O[i]] = 1;
	}

	for (int i = 0; i < N; i++) fa[i] = i;
	for (int i = 0; i < N; i++)
		if (!flag[i]) merge(i);
	for (int i = K - 1, cur; i >= 0; i--) {
		cur = O[i], O[i] = tot;
		merge(cur);
	}
	printf("%d\n", tot);
	for (int i = 0; i < K; i++) printf("%d\n", O[i]);

	return 0;
}
