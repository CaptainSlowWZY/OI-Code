// JLOI 2015
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define fir first
#define sec second
#define forto(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)

typedef std::pair<int, int> Pii;

const int kMaxn = 1005, kMaxm = 3005, kInf = 0x3f3f3f3f;

struct Edge {
	int to, cost, next; 
} E[kMaxm << 1];

int n, m, p, tote;
int back[kMaxn], inq[kMaxn];
int DP[kMaxn][1 << 10], F[1 << 10];
Pii spe[15];

int Steiner(int);
inline void AddEdge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, c, back[v]}, back[v] = tote;
}
inline void UMin(int & x, int y) { x > y ? x = y : 0; }

int main() {
	scanf("%d%d%d", &n, &m, &p);
	for (int u, v, w; m--; ) {
		scanf("%d%d%d", &u, &v, &w);
		AddEdge(u, v, w);
	}
	for (int i = 0; i < p; i++) scanf("%d%d", &spe[i].fir, &spe[i].sec);

	std::sort(spe, spe + p);
	int totc = 0, k = 0;
	for (int i = 1; i < p; i++) {
		if (spe[i].fir != spe[k].fir) {
			for (int j = k; j < i; j++) spe[j].fir = totc;
			totc++, k = i;
		}
	}
	for (int i = k; i < p; i++) spe[i].fir = totc;
	totc++;

	for (int mask = 1, cnt; mask < 1 << totc; mask++) {
		memset(DP, 0x3f, sizeof DP);
		for (int i = cnt = 0; i < p; i++) {
			if (mask >> spe[i].fir & 1) DP[spe[i].sec][1 << cnt++] = 0;
		}
		F[mask] = Steiner(1 << cnt);
	}
	for (int mask = 1; mask < 1 << totc; mask++) {
		for (int T = mask - 1 & mask; T; T = T - 1 & mask) {
			UMin(F[mask], F[T] + F[T ^ mask]);
		}
	}

	printf("%d\n", F[(1 << totc) - 1]);
	return 0;
}

std::queue<int> que;

int Steiner(int U) {
	for (int S = 1; S < U; S++) {
		for (int i = 1; i <= n; i++) {
			for (int T = S - 1 & S; T; T = T - 1 & S) {
				UMin(DP[i][S], DP[i][T] + DP[i][S ^ T]);
			}
			if (DP[i][S] != kInf) {
				que.push(i);
				inq[i] = 1;
			}
		}
		for (int u; !que.empty(); que.pop()) {
			u = que.front();
			forto(u) {
				if (DP[v][S] > DP[u][S] + E[e].cost) {
					DP[v][S] = DP[u][S] + E[e].cost;
					if (!inq[v]) {
						que.push(v);
						inq[v] = 1;
					}
				}
			}
			inq[u] = 0;
		}
	}
	int ret = kInf;
	for (int i = 1; i <= n; i++) UMin(ret, DP[i][U - 1]);
	return ret;
}
