// BZOJ 3566
// SHOI 2014
#include <cstdio>
const int MAXN = 5e5 + 10;

struct Edge {
	int to, next;
	double p;
} E[MAXN << 1];

int N, tote, last[MAXN];
double F[MAXN], G[MAXN], q[MAXN];

namespace FastIO {
	template <typename T>
		void read(T & x) {
			x = 0; register char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
}
inline void add_edge(int u, int v, double p_) {
	E[++tote].to = v, E[tote].p = p_, E[tote].next = last[u], last[u] = tote;
	E[++tote].to = u, E[tote].p = p_, E[tote].next = last[v], last[v] = tote;
}
void dfs1(int u, int fa);
void dfs2(int u, int fa);

int main() {
	using FastIO::read;
	read(N);
	for (int i = 1, a, b, p; i < N; i++) {
		read(a), read(b), read(p);
		add_edge(a, b, p / 100.0);
	}
	for (int i = 1, qi; i <= N; i++) read(qi), q[i] = qi / 100.0;
	dfs1(1, 0);
	G[1] = 1, dfs2(1, 0);
	double ans = 0;
	for (int i = 1; i <= N; i++) ans += 1 - F[i] * G[i] * (1 - q[i]);
	printf("%.6f\n", ans);
	return 0;
}

void dfs1(int u, int fa) {
	F[u] = 1;
	for (int v, e = last[u]; e; e = E[e].next) {
		if ((v = E[e].to) == fa) continue;
		dfs1(v, u);
		F[u] *= 1 - E[e].p + E[e].p * (1 - q[v]) * F[v];
	}
}

void dfs2(int u, int fa) {
	for (int v, e = last[u]; e; e = E[e].next) {
		if ((v = E[e].to) == fa) continue;
		G[v] = 1 - E[e].p + E[e].p * (1 - q[u]) * G[u] * F[u] / (1 - E[e].p + E[e].p * (1 - q[v]) * F[v]);
		dfs2(v, u);
	}
}

// AC!!!
