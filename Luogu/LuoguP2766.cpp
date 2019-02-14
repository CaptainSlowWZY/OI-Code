#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)
#define forback(_) for (int _ = T; _ ^ S; _ = pre[_])

const int MAXE = 2e5, INF = 0x3f3f3f3f;

typedef int IntAr[1005];

struct Edge {
	int to, capt, next;
} E[MAXE << 1];

int N, tote = 1, S, T;
IntAr A, last, cur, DP, D;
std::vector<int> V[505];

inline void add_edge(int u, int v, int cap) {
	E[++tote] = (Edge){v, cap, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, 0, last[v]}, last[v] = tote;
}
int Dinic();

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) scanf("%d", A + i);

	int L = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < i; j++)
			if (A[j] <= A[i]) DP[i] = std::max(DP[i], DP[j] + 1);
		L = std::max(L, DP[i]);
		V[DP[i]].push_back(i);
	}
	printf("%d\n", L);

	T = (S = N * 2 + 1) + 1;
	for (int i = 1; i <= N; i++) {
		add_edge(i, i + N, 1);
		if (DP[i] == 1) add_edge(S, i, 1);
		if (DP[i] == L) add_edge(i + N, T, 1);
		if (DP[i] > 1) {
			for (auto j : V[DP[i] - 1]) {
				if (j > i || A[j] > A[i]) continue;
				add_edge(j + N, i, 1);
			}
		}
	}
	printf("%d\n", Dinic());

	tote = 1;	
	memset(last, 0, sizeof last);
	for (int i = 1; i <= N; i++) {
		add_edge(i, i + N, i > 1 && i < N ? 1 : INF);
		if (DP[i] == 1) add_edge(S, i, i == 1 ? INF : 1);
		if (DP[i] == L) add_edge(i + N, T, i == N ? INF : 1);
		if (DP[i] > 1) {
			for (auto j : V[DP[i] - 1]) {
				if (j > i || A[j] > A[i]) continue;
				add_edge(j + N, i, 1);
			}
		}
	}
	printf("%d\n", Dinic());
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

int dfs(int u, int cap) {
	if (u == T) return cap;
	int rem = cap;
	for (int & e = cur[u], v = E[e].to; e; v = E[e = E[e].next].to)
		if (E[e].capt > 0 && D[v] == D[u] + 1) {
			int del = dfs(v, std::min(E[e].capt, rem));
			E[e].capt -= del, E[e ^ 1].capt += del;
			if (!(rem -= del)) break;
		}
	return cap - rem;
}

int Dinic() {
	int sumf = 0;
	while (build()) {
		for (int i = 1; i <= T; i++) cur[i] = last[i];
		sumf += dfs(S, INF);
	}
	return sumf;
}
