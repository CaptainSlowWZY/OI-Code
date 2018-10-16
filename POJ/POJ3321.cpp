// POJ 3321
#include <cstdio>
#include <vector>
#include <cassert>

// #define DEBUGMD

const int MAXN = 1e5 + 10;
typedef int IntAr[MAXN];
struct Edge {
	int to, next;
} E[MAXN];

int Q, N, dfs_clock, tote;
IntAr bgt, edt, flag, last;

namespace BIT {
	int T[MAXN];
	
	inline int lowbit(int x) { return x & -x; }
	void modify(int p, int d) {
		for (; p <= N; p += lowbit(p)) T[p] += d;
	}
	int query(int p) {
		int res = 0;
		for (; p > 0; p &= p - 1) res += T[p];
		return res;
	}
}
inline void add_edge(int u, int v) {
	E[++tote].to = v, E[tote].next = last[u], last[u] = tote;
}
void dfs(int u, int fa);

int main() {
	scanf("%d", &N);
	for (int i = 1, ui, vi; i < N; i++) {
		scanf("%d%d", &ui, &vi);
		add_edge(ui, vi);
	}
	dfs(1, 0);
	assert(dfs_clock == N);
	for (int i = 1; i <= N; i++) BIT::modify(bgt[i], 1), flag[i] = 1;
	char input[5];
	scanf("%d", &Q);
	for (int x; Q--; ) {
		scanf("%s%d", input, &x);
		if (input[0] == 'Q') printf("%d\n", BIT::query(edt[x]) - BIT::query(bgt[x] - 1));
		else BIT::modify(bgt[x], flag[x] ? -1 : 1), flag[x] ^= 1;
	}
	return 0;
}

void dfs(int u, int fa) {
	bgt[u] = ++dfs_clock;
	for (int e = last[u]; e; e = E[e].next) {
		if (E[e].to == fa) continue;
		dfs(E[e].to, u);
	}	
	edt[u] = dfs_clock;
}
