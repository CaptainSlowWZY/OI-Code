#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define forto(_) for (int e = last[_], v = E[e].to; e; \
						v = E[e = E[e].next].to)
#define forback(_) for (int _ = T; _ ^ S; _ = pre[_])

typedef long long LL;

const int kMaxv = 210;
const int kMaxe = 12000;
const int kInf = 0x3f3f3f3f;

typedef int IAr[kMaxv];

struct Edge {
	int to, capt;
	LL cost;
	int next;
} E[kMaxe << 1];

int n, S, T, tote = 1;
IAr last, pre, pree, A, cnt, C;

inline void AddEdge(int u, int v, int cap, LL cst) {
	E[++tote] = (Edge){v, cap, cst, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, 0, -cst, last[v]}, last[v] = tote;
}
LL Mcf();

int main() {
	scanf("%d", &n);
	T = (S = n + 1) + 1;
	for (int i = 1, ai; i <= n; i++) {
		scanf("%d", A + i);
		ai = A[i];
		for (int j = 2; j * j <= ai; j++) {
			for (; ai % j == 0; ++cnt[i], ai /= j);
		}
		if (ai > 1) ++cnt[i];
	}
	for (int i = 1, Bi; i <= n; i++) {
		scanf("%d", &Bi);
		if (cnt[i] & 1) AddEdge(S, i, Bi, 0);
		else AddEdge(i, T, Bi, 0);
	}
	for (int i = 1; i <= n; i++) scanf("%d", C + i);

	for (int i = 1; i <= n; i++) {
		if (cnt[i] & 1 ^ 1) continue;
		for (int j = 1; j <= n; j++) {
			if (std::abs(cnt[i] - cnt[j]) != 1 || 
				(A[i] > A[j] ? A[i] % A[j] : A[j] % A[i])) continue;
			AddEdge(i, j, kInf, 1ll * C[i] * C[j]);
		}
	}

	printf("%lld\n", Mcf());
	return 0;
}

LL dist[kMaxv];

bool Spfa() {
	static std::queue<int> que;
	static int inque[kMaxv];

	memset(pre, 0xff, sizeof pre);
	memset(dist, 0xc0, sizeof dist);
	for (dist[S] = 0, que.push(S), inque[S] = 1; !que.empty(); ) {
		int u = que.front(); que.pop();
	//	printf(" u = %d, dist[u] = %lld\n", u, dist[u]);
		forto(u) {
			if (E[e].capt > 0 && dist[v] < dist[u] + E[e].cost) {
				dist[v] = dist[u] + E[e].cost;
				pre[v] = u, pree[v] = e;
				if (!inque[v]) que.push(v), inque[v] = 1;
			}
		}
		inque[u] = 0;
	}
	return ~pre[T];
}

LL Mcf() {
	LL sumc = 0, sumf = 0;
	while (Spfa()) {
		int minc = kInf;
		forback(u) minc = std::min(minc, E[pree[u]].capt);
	/*	printf(" minc = %d, dist = %lld\n",
				minc, dist[T]);*/
		if (sumc + (LL)minc * dist[T] < 0) {
			return sumf - sumc / dist[T];
		}
		sumc += (LL)minc * dist[T], sumf += minc;
		forback(u) E[pree[u]].capt -= minc, E[pree[u] ^ 1].capt += minc;
	}
	return sumf;
}
