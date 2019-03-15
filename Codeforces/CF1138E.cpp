#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int kMaxv = (int)5e6 + 10, kMaxe = (int)6e6 + 10;

typedef int IntArr[kMaxv];
typedef std::pair<int, int> Pii;

struct Edge {
	int to, next;
} E[kMaxe];

int n, m, d, totscc, dfs_clock, top, tote;
IntArr dfn, low, last, val, sumv, col, DP, S;
Pii E0[kMaxe];
char IN[60];

inline void Umin(int & x, int y) {
	x > y ? x = y : 0;
}
inline void Umax(int & x, int y) {
	x < y ? x = y : 0;
}
inline int Id(int u, int day) {
	return (u - 1) * d + day;
}
inline int Node(int u) {
	return u / d + 1;
}
inline void AddEdge(int u, int v) {
	E[++tote].to = v, E[tote].next = last[u];
	last[u] = tote;
}
void Tarjan(int u);
int Dfs(int);

int main() {
	scanf("%d%d%d", &n, &m, &d);
	int flag = 0;
	for (int i = 0, u, v; i < m; i++) {
		scanf("%d%d", &u, &v);
		for (int j = 0; j < d; j++) {
			AddEdge(Id(u, j), Id(v, (j + 1) % d));
		}
	}
	if (flag) return puts("Fuck you!"), 0;
	for (int i = 1; i <= n; i++) {
		scanf("%s", IN);
		for (int j = 0; j < d; j++) {
			val[Id(i, j)] = IN[j] ^ '0';
		}
	}

	int tot = Id(n, d - 1);
	for (int i = 0; i <= tot; i++)
		if (!dfn[i]) Tarjan(i);
	tote = 0;
	for (int i = 0, cur; i <= tot; i++) {
		cur = col[i];
		forto(i) {
			if (cur == col[v]) continue;
			E0[tote++] = Pii(cur, col[v]);
		}
	}
	std::sort(E0, E0 + tote);
	int tote0 = std::unique(E0, E0 + tote) - E0;
	tote = 0;
	memset(last, 0, sizeof last);
	for (int i = 0; i < tote0; i++) {
		AddEdge(E0[i].first, E0[i].second);
	}

	memset(DP, 0xff, sizeof DP);
	printf("%d\n", Dfs(col[0]));
	return 0;
}

int Dfs(int u) {
	if (~DP[u]) return DP[u];
	DP[u] = 0;
	forto(u) Umax(DP[u], Dfs(v));
	return DP[u] += sumv[u];
}

void Tarjan(int u) {
	dfn[u] = low[u] = ++dfs_clock;
	S[top++] = u;
	forto(u) { 
		if (!dfn[v]) {
			Tarjan(v);
			Umin(low[u], low[v]);
		}
		else if (!col[v]) {
			Umin(low[u], dfn[v]);
		}
	}
	if (dfn[u] == low[u]) {
		int top0 = top;
		col[u] = ++totscc;
		sumv[totscc] = DP[Node(u)] = val[u];
		for (int cur; (cur = S[top - 1]) != u; --top) {
			if (val[cur] && !DP[Node(cur)]) {
				++sumv[totscc];
				DP[Node(cur)] = 1;
			}
			col[cur] = totscc;
		}
		--top;
		for (int i = top0 - 1; i >= top; i--) {
			DP[Node(S[i])] = 0;
		}
	}
}