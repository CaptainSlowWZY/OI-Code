#include <algorithm>
#include <cstdio>
#include <queue>

#define fi first
#define se second

typedef std::pair<int, int> Pii;
typedef std::queue<Pii> Que;

const int kMaxn = 505, kInf = 0x3f3f3f3f;

int n, m, rem, ans;
int A[kMaxn][kMaxn], D[kMaxn];
Que Q[kMaxn << 1];

void Extend(int u, int v);
void AddEdge(const Pii & e);

int main() {
	scanf("%d%d", &n, &m);
	rem = (n * (n - 1) >> 1) - m;
	for (int u, v, i = 0; i < m; ++i) {
		scanf("%d%d", &u, &v);
		A[u][v] = A[v][u] = 1, ++D[u], ++D[v];
	} ans = n << 1;
	for (int i = 1; i <= n; ++i) { A[i][i] = 1;
		for (int j = i + 1; j <= n; ++j) Extend(i, j);
	} 
	while (rem) {
		while (ans && Q[ans].empty()) --ans;
		AddEdge(Q[ans].front()); Q[ans].pop();
	} printf("%d\n", ans);
	return 0;
}

void Extend(int u, int v) {
	if (A[u][v]) return;
	if (D[u] + D[v] >= ans) AddEdge({u, v});
	else Q[D[u] + D[v]].push({u, v});
}

void AddEdge(const Pii & e) {
	if (A[e.fi][e.se]) return;
	++D[e.fi], ++D[e.se], --rem;
	A[e.fi][e.se] = A[e.se][e.fi] = 1;
	for (int i = 1; i <= n; ++i) {
		if (i == e.fi || i == e.se) continue;
		Extend(e.fi, i); Extend(e.se, i);
	}
}
