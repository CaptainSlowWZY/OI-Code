// Luogu P2762
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <queue>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int MAXV = 110;
const int MAXE = 2600;
const int INF = 0x7f7f7f7f;
const int SIZE = 200;

struct Edge {
	int to, capt, next;
} E[MAXE << 1];

int N, M, S, T, tote = 1, totw, last[MAXV], cur[MAXV], D[MAXV];
char st[SIZE];

inline void add_edge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, 0, last[v]}, last[v] = tote;
}
int read(char *&st) {
	for (; !isdigit(*st); ++st)
		if (*st == '\n' || *st == '\0') return -1;
	int ret = 0;
	for (; isdigit(*st); ++st) ret = (ret << 3) + (ret << 1) + (*st ^ '0');
	return ret;
}

int max_flow();

int main() {
	scanf("%d%d", &M, &N);
	T = (S = N + M) + 1;
	for (char ch; (ch = getchar()) != '\n'; );
	for (int i = 0; i < M; i++) {
		fgets(st, SIZE, stdin);
		char * cur = st;
		int tmp = read(cur);
		add_edge(S, i, tmp);
		totw += tmp;
		for (; ~(tmp = read(cur)); add_edge(i, M + tmp - 1, INF));
	}
	for (int i = 0, cost; i < N; i++) {
		scanf("%d", &cost);
		add_edge(M + i, T, cost);
	}

	int ans = totw - max_flow();
	for (int i = 0; i < M; i++)
		if (D[i]) printf("%d ", i + 1);
	putchar('\n');
	for (int i = M; i < M + N; i++)
		if (D[i]) printf("%d ", i - M + 1);
	printf("\n%d\n", ans);
	return 0;
}

bool build() {
	std::queue<int> que;
	memset(D, 0, sizeof D);
	for (D[S] = 1, que.push(S); !que.empty(); ) {
		int u = que.front(); que.pop();
		forto(u)
			if (!D[v] && E[e].capt > 0) D[v] = D[u] + 1, que.push(v);
	}
	return D[T];
}

int dinic(int u, int flow) {
	if (u == T) return flow;
	int rem = flow;
	for (int &e = cur[u], v = E[e].to; e && rem > 0; v = E[e = E[e].next].to)
		if (D[v] == D[u] + 1 && E[e].capt > 0) {
			int delta = dinic(v, std::min(rem, E[e].capt));
			E[e].capt -= delta, E[e ^ 1].capt += delta, rem -= delta;
		}
	return flow - rem;
}

int max_flow() {
	int sumf = 0;
	while (build()) {
		for (int i = 0; i <= T; i++) cur[i] = last[i];
		sumf += dinic(S, INF);
	}
	return sumf;
}
