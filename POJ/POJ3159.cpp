// POJ 3159
// This problem requires SPFA+stack
#include <cstdio>
#include <cstring>
const int MAXN = 30005;
const int MAXM = 150005;

int N, M;

namespace FastIO {
	template <typename T>
	void read(T & x) {
		x = 0; register char ch = getchar();
		for (; ch < '0' || ch > '9'; ch = getchar());
		for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
	}
}
namespace Graph {
	struct Edge {
		int to, cost, next;
	} E[MAXM];
	int last[MAXN], tote, D[MAXN];

	inline void add_edge(int u, int v, int c) {
		E[++tote].to = v, E[tote].cost = c, E[tote].next = last[u], last[u] = tote;
	}
	void SPFA();
}

int main() {
	using FastIO::read;
	read(N), read(M);
	for (int i = 0, a, b, c; i < M; i++) {
		read(a), read(b), read(c);
		Graph::add_edge(a, b, c);
	}
	Graph::SPFA();
	printf("%d\n", Graph::D[N]);
	return 0;
}

namespace Graph {
	int in_stk[MAXN], st[MAXM + MAXN];

	void SPFA() {
		memset(D, 0x7f, sizeof D);
		int top = 0;
		st[top++] = 1, in_stk[1] = 1, D[1] = 0;
		while (top) {
			int u = st[--top];
			for (int e = last[u], v; e; e = E[e].next)
				if (D[u] + E[e].cost < D[v = E[e].to]) {
					D[v] = D[u] + E[e].cost;
					if (!in_stk[v]) st[top++] = v, in_stk[v] = 1;
				}
			in_stk[u] = 0;
		}
	}
}

// AC!!!
