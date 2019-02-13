// BZOJ 4027
// HEOI 2015
#pragma GCC optimize(2)
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>

#define rg register
#define gch getchar
#define forto(_) for (rg int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int MAXN = 2e6 + 5;

struct Edge {
	int to, next;
} E[MAXN << 1];

int N, M, tote, ans, C[MAXN], last[MAXN];

namespace FastIO {
	template <typename T>
		void read(T & x) {
			x = 0; rg char ch = gch();
			for (; !isdigit(ch); ch = gch());
			for (; isdigit(ch); ch = gch()) x = (x << 3) + (x << 1) + (ch ^ '0');
		}
}
inline void add_edge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, last[v]}, last[v] = tote;
}
int dfs(int u, int fa);

int main() {
	using FastIO::read;
	read(N), read(M);
	for (rg int i = 0; i < N; i++) read(C[i]); 
	for (rg int i = 0, Ki; i < N; i++) {
		read(Ki);
		for (rg int v; Ki--; ) {
			read(v);
			add_edge(i, v);
		}
	}

	dfs(0, -1);

	printf("%d\n", ans);
	return 0;
}

int dfs(int u, int fa) {
	int mass = C[u]; 
	std::vector<int> V;
	forto(u) {
		if (v == fa) continue;
		++mass;
		V.push_back(dfs(v, u));
	}
	std::sort(V.begin(), V.end());
	for (rg int i = 0, sz = (int)V.size(); i < sz; i++)
		if (mass - 1 + V[i] <= M) {
			mass += V[i] - 1;
			++ans;
		}
	return mass;
}
