#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

#define forto(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)

const int kMaxn = 110, kMaxe = 2e4, kInf = 0x3f3f3f3f;

typedef int IAr[kMaxn];

struct Edge {
	int to, capt, next;
} E[kMaxe << 1];

int n, tote = 1, S, T, VS, VT;
IAr back, cur, D, A;

inline void AddEdge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, 0, back[v]}, back[v] = tote;
}
inline void NewEdge(int u, int v, int lb, int ub) {
	AddEdge(u, v, ub - lb);
	A[u] -= lb, A[v] += lb;
}
int MinFlow();

int main() {
	scanf("%d", &n);
	S = 0, T = n + 1;
	for (int i = 1, mi; i <= n; i++) {
		scanf("%d", &mi);
		for (int to; mi--; ) {
			scanf("%d", &to);
			NewEdge(i, to, 1, kInf);
		}
		NewEdge(S, i, 0, kInf);
		NewEdge(i, T, 0, kInf);
	}

	printf("%d\n", MinFlow());
	return 0;
}

bool Build(int src, int trg) {
	std::queue<int> que;
	memset(D, 0, sizeof D);
	D[src] = 1, que.push(src);
	for (int u; !que.empty(); ) {
		u = que.front(), que.pop();
		forto(u) {
			if (E[e].capt <= 0 || D[v]) continue;
			D[v] = D[u] + 1;
			que.push(v);
		}
	}
	return D[trg];
}

int end;

int Dfs(int u, int flow) {
	if (u == end) return flow;
	int rem = flow, del;
	for (int & e = cur[u], v = E[e].to; e && rem;
			v = E[e = E[e].next].to) {
		if (D[v] != D[u] + 1 || E[e].capt <= 0) continue;
		del = Dfs(v, std::min(rem, E[e].capt));
		E[e].capt -= del, E[e ^ 1].capt += del;
		rem -= del;
	}
	return flow - rem;
}

int Dinic(int src, int trg) {
	int sum = 0;
	end = trg;
	while (Build(src, trg)) {
		for (int i = 0; i <= VT; i++) cur[i] = back[i];
		sum += Dfs(src, kInf);
	}
	return sum;
}

int MinFlow() {
	VT = (VS = T + 1) + 1;
	int sumd = 0;
	for (int i = 0; i <= T; i++) {
		if (A[i] > 0) AddEdge(VS, i, A[i]);
		else if (A[i] < 0) AddEdge(i, VT, -A[i]);
		sumd += abs(A[i]);
	}
	NewEdge(T, S, 0, kInf);
	Dinic(VS, VT);
	int res = E[tote].capt;
	E[tote].capt = E[tote - 1].capt = 0;
	return res - Dinic(T, S);
}
