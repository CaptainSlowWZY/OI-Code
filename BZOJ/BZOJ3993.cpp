#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>

const int kMaxn = 55;
const double kInf = 1e8, kEps = 1e-8;

typedef int IAr[kMaxn << 1];

struct Edge {
	int to;
	double capt;
	int next;
} E[kMaxn * kMaxn << 1];

int n, m, tote, S, T;
int A[kMaxn], B[kMaxn], M[kMaxn][kMaxn];
IAr D, back, cur;
double suma;

bool Check(double);

int main() {
	scanf("%d%d", &n, &m);
	T = (S = n + m) + 1;
	for (int i = 0; i < n; i++) {
		scanf("%d", A + i);
		suma += A[i];
	}
	for (int i = 0; i < m; i++) scanf("%d", B + i);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) scanf("%d", &M[i][j]);
	}
	
	double lb = 0, ub = 10000, mid;
	for (; fabs(ub - lb) > kEps; ) {
		mid = (lb + ub) / 2;
		if (Check(mid)) ub = mid;
		else lb = mid;
	}

	printf("%.9f\n", ub);
	return 0;
}

#define forto(_) for (int e = back[_], v = E[e].to; e; v = E[e = E[e].next].to)

bool Build() {
	std::queue<int> que;
	memset(D, 0, sizeof D);
	D[S] = 1, que.push(S);
	for (int u; !que.empty(); ) {
		u = que.front(), que.pop();
		forto(u) {
			if (!D[v] && E[e].capt > 0) {
				D[v] = D[u] + 1;
				que.push(v);
			}
		}
	}
	return D[T];
}

double Dinic(int u, double flow) {
	if (u == T) return flow;
	double rem = flow;
	for (int & e = cur[u], v = E[e].to; e && rem > 0; v = E[e = E[e].next].to) {
		if (D[v] == D[u] + 1 && E[e].capt > 0) {
			double del = Dinic(v, std::min(rem, E[e].capt));
			E[e].capt -= del, E[e ^ 1].capt += del;
			rem -= del;
		}
	}
	return flow - rem;
}

double MaxFlow() {
	double sum = 0;
	while (Build()) {
		for (int i = 0; i <= T; i++) cur[i] = back[i];
		sum += Dinic(S, kInf);
	}
	return sum;
}

inline void AddEdge(int u, int v, double c) {
	E[++tote] = (Edge){v, c, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, 0, back[v]}, back[v] = tote;
}

bool Check(double t) {
	tote = 1;
	memset(back, 0, sizeof back);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (!M[i][j]) continue;
			AddEdge(i, m + j, kInf);
		}
	}
	for (int i = 0; i < m; i++) AddEdge(S, i, B[i] * t);
	for (int i = 0; i < n; i++) AddEdge(m + i, T, A[i]);
	return fabs(MaxFlow() - suma) <= kEps;
}
