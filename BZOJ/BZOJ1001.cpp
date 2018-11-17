// BZOJ 1001
#pragma GCC optimize(2)
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <functional>
#include <vector>
#include <queue>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif
#define rg register
#define gch getchar
#define fir first
#define sec second
#define forto(_) for (rg int v, e = last[_]; e; e = E[e].next)

typedef long long LL;
typedef std::pair<LL, int> Pli;

const int MAXP = 1800000;

struct Edge {
	int to, cost, next;
} E[MAXP << 2];

int N, M, S, T, tote, last[MAXP], vis[MAXP];
LL D[MAXP];

namespace FastIO {
	template <typename T>
		void read(T & x);
}
LL Dijkstra(int s, int t);
inline void add_edge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, c, last[v]}, last[v] = tote;
}

int main() {
	using FastIO::read;

	read(N), read(M);
/* 3*4          0
 * |---|---|---|
 * |\ 1|\ 2|\ 3|
 * |4 \|5 \|6 \|
 * |---|---|---|
 * |\ 7|\ 8|\ 9|
 * |10\|11\|12\|
 * |---|---|---|
 * 13
 */
	if (N == 1 || M == 1) {
		int ans = 0x7f7f7f7f;
		for (rg int i = 0; i < N; i++)
			for (rg int wij, j = 1; j < M; j++) {
				read(wij);
				ans = std::min(ans, wij);
			}
		for (rg int i = 1; i < N; i++)
			for (rg int wij, j = 0; j < M; j++) {
				read(wij);
				ans = std::min(ans, wij);
			}
		printf("%d\n", ans);
		return 0;
	}

	int m1 = M - 1, rcnt = m1 << 1;
	S = 0, T = (N - 1) * rcnt + 1;
	// horiznal
	for (rg int i = 0; i < N; i++)	
		for (rg int wij, j = 1; j < M; j++) {
			read(wij);
			add_edge(std::max((i - 1) * rcnt + m1 + j, 0), std::min(T, i * rcnt + j), wij);
		}
	// vertical
	for (rg int i = 1; i < N; i++) {
		rg int fir = (i - 1) * rcnt;
		for (rg int wij, j = 0; j < M; j++) {
			read(wij);
			add_edge(j ? fir + j : T, j + 1 == M ? S : fir + m1 + j + 1, wij);
		}
	}
	// slanting
	for (rg int i = 1; i < N; i++) {
		rg int fir = (i - 1) * rcnt;
		for (rg int wij, j = 1; j < M; j++) {
			read(wij);
			add_edge(fir + j, fir + m1 + j, wij);
		}
	}

	printf("%lld\n", Dijkstra(S, T));

	return 0;
}

std::priority_queue<Pli, std::vector<Pli>, std::greater<Pli> > hp;

LL Dijkstra(int s, int t) {
	memset(D, 0x7f, sizeof D);
	for (D[s] = 0, hp.push(Pli(0, s)); !hp.empty(); ) {
		Pli now = hp.top(); hp.pop();
		if (vis[now.sec] || now.fir > D[now.sec]) continue;
		vis[now.sec] = 1;
		forto(now.sec) {
			if (vis[v = E[e].to]) continue;
			if (D[v] > now.fir + E[e].cost) {
				D[v] = now.fir + E[e].cost;
				hp.push(Pli(D[v], v));
			}
		}
	}
	return D[t];
}

namespace FastIO {
	template <typename T>
		void read(T & x) {
			rg char ch = gch();
			for (; ch < '0' || ch > '9'; ch = gch());
			for (x = 0; ch >= '0' && ch <= '9'; ch = gch())
				x = (x << 3) + (x << 1) + (ch ^ '0');
		}
}
