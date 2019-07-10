#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

#define forto(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)

const int kMaxn = 205;
const int kMaxe = 5e4, kInf = 0x3f3f3f3f;

typedef int IAr[kMaxn << 1];

struct Edge {
	int to, capt, next;
} E[kMaxe << 1];

int n, m, k, tote = 1, S, T, VS, VT, L, R;
int sumr[kMaxn], sumc[kMaxn];
IAr back, cur, D, A;

inline void AddEdge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, 0, back[v]}, back[v] = tote;
}
inline void NewEdge(int u, int v, int lb, int ub) {
	AddEdge(u, v, ub - lb);
	A[u] -= lb, A[v] += lb;
}
bool BFlow();
bool Check(int);

int main() {
	scanf("%d%d", &n, &m);
	T = (S = n + m) + 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0, Aij; j < m; j++) {
			scanf("%d", &Aij);
			sumr[i] += Aij;
			sumc[j] += Aij;
		}
	}
	scanf("%d%d", &L, &R);

	int lb = -1, ub = 500000;
	for (int mid; ub - lb > 1; ) {
		mid = lb + ub >> 1;
		if (Check(mid)) ub = mid;
		else lb = mid;
	}

	printf("%d\n", ub); 
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
	for (int & e = cur[u], v = E[e].to; e;
			v = E[e = E[e].next].to) {
		if (D[v] != D[u] + 1 || E[e].capt <= 0) continue;
		del = Dfs(v, std::min(rem, E[e].capt));
		E[e].capt -= del, E[e ^ 1].capt += del;
		if (!(rem -= del)) break;
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

bool BFlow() {
	VT = (VS = T + 1) + 1;
	int sumd = 0;
	for (int i = 0; i <= T; i++) {
		if (A[i] > 0) {
			AddEdge(VS, i, A[i]);
			sumd += A[i];
		}
		else if (A[i] < 0) AddEdge(i, VT, -A[i]);
	}
	NewEdge(T, S, 0, kInf);
	return sumd == Dinic(VS, VT);
}

bool Check(int maxd) {
	tote = 1;
	memset(A, 0, sizeof A);
	memset(back, 0, sizeof back);
	for (int i = 0; i < n; i++) {
		NewEdge(S, i, std::max(0, sumr[i] - maxd), sumr[i] + maxd);
	}
	for (int i = 0; i < m; i++) {
		NewEdge(n + i, T, std::max(0, sumc[i] - maxd), sumc[i] + maxd);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) NewEdge(i, n + j, L, R);
	}
	return BFlow();
}
