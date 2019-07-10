#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

#define forto(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)
#define back(_) for (int _ = T; _ != S; _ = prv[_])

const int kMaxn = 105, kInf = 0x3f3f3f3f;

typedef int IAr[kMaxn << 1];

struct Edge {
	int to, capt, cost, next;
} E[kMaxn << 3];

int n, m, tote = 1, S, T;
char NA[kMaxn][20], S1[20], S2[20];
IAr back, D, prv, prve, inq;

inline void AddEdge(int u, int v, int cap, int cst) {
	E[++tote] = (Edge){v, cap, cst, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, 0, -cst, back[v]}, back[v] = tote;
}
int Find(char st[]);
void Mcf(int &, int &);
void Dfs1(int);
void Dfs2(int);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%s", NA[i]);

	T = (S = n * 2 + 1) + 1;
	int fspe = 0;
	for (int u, v; m--; ) {
		scanf("%s%s", S1, S2);
		u = Find(S1), v = Find(S2);
		if (u > v) std::swap(u, v);
		fspe |= u == 1 && v == n;
		AddEdge(u, n + v, 1, -1);	// u - out, n + u - in
	}
	for (int i = 2; i < n; i++) AddEdge(n + i, i, 1, 0);
	AddEdge(S, 1, 2, 0);
	AddEdge(n * 2, T, 2, 0);

	int totc, totf;
	Mcf(totf, totc);

	if (!totf || totf == 1 && !fspe) {
		puts("No Solution!");
		return 0;
	}
	if (totf == 1 && fspe) {
		printf("2\n%s\n%s\n%s\n", NA[1], NA[n], NA[1]);
		return 0;
	}
	printf("%d\n", -totc);
	Dfs1(1);
	Dfs2(1);
	return 0;
}

void Dfs1(int u) {
	if (u > n) u -= n;
	puts(NA[u]);
	if (u == n) return;
	forto(u) {
		if (!E[e].capt) {
			E[e].capt = 1;
			Dfs1(v);
			break;
		}
	}
}

void Dfs2(int u) {
	if (u > n) u -= n;
	if (u == n) return;
	forto(u) {
		if (!E[e].capt) {
			E[e].capt = 1;
			Dfs2(v);
			break;
		}
	}
	puts(NA[u]);
}

int Find(char st[]) {
	for (int i = 1; i <= n; i++) {
		if (!strcmp(NA[i], st)) return i;
	}
	return -1;
}

bool Spfa() {
	std::queue<int> que;
	memset(prv, 0xff, sizeof prv);
	memset(D, 0x7f, sizeof D);
	D[S] = 0, que.push(S), inq[S] = 1;
	for (int u; !que.empty(); ) {
		u = que.front(), que.pop();
		forto(u) {
			if (E[e].capt > 0 && D[v] > D[u] + E[e].cost) {
				D[v] = D[u] + E[e].cost;
				prv[v] = u,	prve[v] = e;
				if (!inq[v]) {
					que.push(v);
					inq[v] = 1;
				}
			}
		}
		inq[u] = 0;
	}
	return ~prv[T];
}

void Mcf(int & totf, int & totc) {
	totf = totc = 0;
	for (int flow; Spfa(); ) {	
		flow = kInf;
		back(v) flow = std::min(flow, E[prve[v]].capt);
		totc += flow * D[T], totf += flow;
		back(v) {
			E[prve[v]].capt -= flow;
			E[prve[v] ^ 1].capt += flow;
		}
	}
}
