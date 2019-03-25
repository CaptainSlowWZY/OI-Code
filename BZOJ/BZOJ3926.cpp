// ZJOI 2015
#include <cstdio>
#include <cstring>

const int kMaxn = 1e5 + 10;

struct Edge {
	int to, next;
} E[kMaxn << 1];

int n, c, tote, col[kMaxn], deg[kMaxn << 1], last[kMaxn];

namespace sam {
	int Extend(int ch, int last);
	long long Calc();
}
inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, last[v]}, last[v] = tote;
	++deg[u], ++deg[v];
}
void Dfs(int u, int fa, int lst = 1);

int main() {
	scanf("%d%d", &n, &c);
	for (int i = 1; i <= n; i++) scanf("%d", col + i);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		AddEdge(u, v);
	}

	for (int i = 1; i <= n; i++) {
		if (deg[i] == 1) {
			Dfs(i, 0);
		}
	}
	
	printf("%lld\n", sam::Calc());
	return 0;
}

void Dfs(int u, int fa, int lst) {
	lst = sam::Extend(col[u], lst);
	for (int e = last[u], v = E[e].to; e;
			v = E[e = E[e].next].to) {
		if (v == fa) continue;	
		Dfs(v, u, lst);
	}
}

namespace sam {
	const int kSize = 2e6 + 10;
	int size = 1, A[kSize][10], par[kSize], max[kSize];

	int Extend(int ch, int last) {
		int p = last, np = ++size;
		max[last = np] = max[p] + 1;
		for (; p && !A[p][ch]; p = par[p]) A[p][ch] = np;
		if (!p) return par[np] = 1, last;
		int q = A[p][ch];
		if (max[q] == max[p] + 1) par[np] = q;
		else {
			int nq = ++size;
			max[nq] = max[p] + 1;
			par[nq] = par[q], par[np] = par[q] = nq;
			memcpy(A[nq], A[q], sizeof A[q]);
			for (; A[p][ch] == q; p = par[p]) A[p][ch] = nq;
		}
		return last;
	}
	long long Calc() {
		long long ans = 0;
		for (int i = 1; i <= size; i++) {
			ans += max[i] - max[par[i]];
		}
		return ans;
	}
}
