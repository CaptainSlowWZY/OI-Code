#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

#define forto(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)
#define back(_) for (int _ = T; _ != S; _ = prv[_])

const int kMaxv = 1500, kMaxe = 1e4, kInf = 0x3f3f3f3f;
const int kDx[] = {-1, 0, 0, 1, -1, -1, 1, 1};
const int kDy[] = {0, -1, 1, 0, -1, 1, -1, 1};

struct Edge {
	int to, capt, cost, next;
} E[kMaxe << 1];

int n, m, S, T, tote = 1;
int back[kMaxv], cur[kMaxv], D[kMaxv], prv[kMaxv], prve[kMaxv], inq[kMaxv];
char A[25][25], B[25][25], L[25];

inline void AddEdge(int u, int v, int cap, int cst) {
	E[++tote] = (Edge){v, cap, cst, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, 0, -cst, back[v]}, back[v] = tote;
}
void Mcf(int & totf, int & totc);

int main() {
	scanf("%d%d", &n, &m);
	int nm = n * m, cnt1 = 0, cnt2 = 0;
	T = (S = nm * 3) + 1;
	for (int i = 0; i < n; i++) {
		scanf("%s", A[i]);
		for (int j = 0; j < m; j++) {
			if (A[i][j] == '0') continue;
			++cnt1;
			AddEdge(S, i * m + j, 1, 0);
		}
	}
	for (int i = 0; i < n; i++) {
		scanf("%s", B[i]);
		for (int j = 0; j < m; j++) {
			if (B[i][j] == '0') continue;
			++cnt2;
			AddEdge(i * m + j, T, 1, 0);
		}
	}
	if (cnt1 != cnt2) {
		puts("-1");
		return 0;
	}
	for (int i = 0; i < n; i++) {
		scanf("%s", L);
		for (int j = 0, Li, cur; j < m; j++) {
			Li = L[j] ^ '0', cur = i * m + j;
			if (A[i][j] == B[i][j]) {
				AddEdge(nm + cur, cur, Li >> 1, 0);
				AddEdge(cur, nm * 2 + cur, Li >> 1, 0);
			} else {
				if (A[i][j] == '1') {
					AddEdge(nm + cur, cur, Li >> 1, 0);
					AddEdge(cur, nm * 2 + cur, Li + 1 >> 1, 0);
				} else {
					AddEdge(nm + cur, cur, Li + 1 >> 1, 0);
					AddEdge(cur, nm * 2 + cur, Li >> 1, 0);
				}
			}
			for (int k = 0, x, y; k < 8; k++) {
				x = i + kDx[k], y = j + kDy[k];
				if (x >= 0 && x < n && y >= 0 && y < m) {
					AddEdge(nm * 2 + x * m + y, nm + cur, kInf, 1);
					AddEdge(nm * 2 + cur, nm + x * m + y, kInf, 1);
				}
			}
		}
	}
	int flow, ans;
	Mcf(flow, ans);

	printf("%d\n", flow == cnt1 ? ans : -1);
	return 0;
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
