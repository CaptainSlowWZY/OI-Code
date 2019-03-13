// BZOJ 1086
// SCOI 2005
#include <cstdio>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int kMaxn = 1010;

typedef int IAr[kMaxn];

struct Edge {
	int to, next;
} E[kMaxn << 1];

int N, B, tote, totpr, top;
IAr last, blg, capt, S;

inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, last[v]}, last[v] = tote;
}
void Dfs(int u, int fa);

int main() {
	scanf("%d%d", &N, &B);
	for (int i = 1, u, v; i < N; i++) {
		scanf("%d%d", &u, &v);
		AddEdge(u, v);
	}

	Dfs(1, 0);
	while (top) {
		blg[S[--top]] = totpr;
	}

	printf("%d\n", totpr);
	for (int i = 1; i <= N; i++) printf("%d%c", blg[i], i == N ? '\n' : ' ');
	for (int i = 1; i <= totpr; i++) printf("%d%c", capt[i], i == totpr ? '\n' : ' ');
	return 0;
}

void Dfs(int u, int fa) {
	S[top++] = u;
	int bot = top;
	forto(u) {
		if (v == fa) continue;
		Dfs(v, u);
		if (top - bot >= B) {
			for (++totpr; top > bot; ) {
				blg[S[--top]] = totpr;
			}
			capt[totpr] = u;
		}
	}
}
