// POJ 1275
#include <cstdio>
#include <cstring>
#include <queue>
const int MAXV = 30;

int N, num[MAXV], R[MAXV];

namespace FastIO {
	template <typename T>
	void read(T & x) {
		x = 0; register char ch = getchar();
		for (; ch < '0' || ch > '9'; ch = getchar());
		for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
	}
}
void solve();

int main() {
	int T;
	FastIO::read(T);
	while (T--) solve();
	return 0;
}

namespace Graph {
	struct Edge {
		int to, cost, next;
	} E[1000];
	int tote, last[MAXV], D[MAXV];

	inline void add_edge(int u, int v, int c) {
		E[++tote].to = v, E[tote].cost = c, E[tote].next = last[u], last[u] = tote;
	}
	inline void init() {
		tote = 0;
		memset(last, 0, sizeof last);
	}
	void build(int mid);
	int SPFA();
}

void solve() {
	using FastIO::read;
	for (int i = 0; i < 24; i++) read(R[i]);
	memset(num, 0, sizeof num);
	read(N);
	for (int i = 0, ti; i < N; i++) {
		read(ti);
		++num[ti];
	}
	int lb = -1, ub = N, mid, flag = 0;
	for (; ub - lb > 1; ) { // (lb, ub]
		mid = lb + ub >> 1;
		Graph::build(mid);
		if (Graph::SPFA() == mid) ub = mid, flag = 1;
		else lb = mid;
	}
/*	for (int ans = 0; ans <= N; ans++) {
		Graph::build(ans);
		if (Graph::SPFA() == ans) {
			printf("%d\n", ans);
			return;
		}
	}*/
	if (flag) printf("%d\n", ub);
	else puts("No Solution");
}

namespace Graph {
	void build(int ans) {
		init();
		for (int i = 1; i <= 24; i++) add_edge(i - 1, i, 0), add_edge(i, i - 1, -num[i - 1]);
		add_edge(0, 24, ans);
		for (int i = 9; i <= 24; i++) add_edge(i - 8, i, R[i - 1]);
		for (int i = 1; i <= 8; i++) add_edge(i + 16, i, R[i - 1] - ans);
	}

	int in_que[MAXV], cnt[MAXV];
	
	int SPFA() {
	// S - 0, T - 24
		memset(D, 0x80, sizeof D);
		memset(cnt, 0, sizeof cnt);
		memset(in_que, 0, sizeof in_que);
		std::queue<int> Q;
		Q.push(0), in_que[0] = 1, D[0] = 0;
		while (!Q.empty()) {
			int u = Q.front(); Q.pop();
			for (int e = last[u], v; e; e = E[e].next)
				if (D[u] + E[e].cost > D[v = E[e].to]) {
					D[v] = D[u] + E[e].cost;
					if (!in_que[v]) Q.push(v), in_que[v] = 1;
					if (++cnt[v] > 24) return 0x80808080;
				}
			in_que[u] = 0;
		}
		return D[24];
	}
}

// AC!!!