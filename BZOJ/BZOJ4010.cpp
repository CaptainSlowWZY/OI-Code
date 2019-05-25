// HNOI2015
#include <cstdio>
#include <cstring>
#include <queue>

#define forto(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)

const int kMaxn = 1e5 + 5;

struct Edge {
	int to, next;
} E[kMaxn];

int n, m, cnte;
int back[kMaxn], ideg[kMaxn], ans[kMaxn];
std::priority_queue<int> hp;

inline void AddEdge(int u, int v) {
	E[++cnte] = (Edge){v, back[u]}, back[u] = cnte, ++ideg[v];
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		cnte = 0;
		memset(back, 0, sizeof back);
		memset(ideg, 0, sizeof ideg);

		scanf("%d%d", &n, &m);
		for (int x, y; m--; ) {
			scanf("%d%d", &x, &y);
			AddEdge(y, x);
		}

		for (; !hp.empty(); hp.pop());
		for (int i = 1; i <= n; i++) {
			if (!ideg[i]) hp.push(i);
		}
		int cur = 0;
		for (int u; !hp.empty(); ) {
			ans[cur++] = u = hp.top();
			hp.pop();
			forto(u) {
				if (--ideg[v] == 0) {
					hp.push(v);
				}
			}
		}
		if (cur < n) puts("Impossible!");
		else {
			for (int i = n - 1; i >= 0; i--) printf("%d ", ans[i]);
			putchar('\n');
		}
	}
	return 0;
}
