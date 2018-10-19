// lkf
#include <cstdio>
#include <algorithm>
typedef long long LL;

const int MAXN = 3400;
const int INF = 0x3f3f3f3f;
const int MOD = 19260817;

int N, K, A[MAXN];

namespace FastIO {
	template <typename T>
		void read(T & x) {
			x = 0; register char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
}
namespace Subtask2 {
	void solve();
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("lkf.in", "r", stdin);
	freopen("lkf.out", "w", stdout);
#endif
	using FastIO::read;
	read(N), read(K);
	for (int i = 1; i <= N; i++) read(A[i]);
	Subtask2::solve();
#ifndef ONLINE_JUDGE
	fclose(stdin); fclose(stdout);
#endif
	return 0;
}

namespace Subtask2 {
	struct Edge {
		int to, next;
	} E[MAXN << 1];

	int tote, last[MAXN];

	inline void add_edge(int u, int v) {
		E[++tote].to = v, E[tote].next = last[u], last[u] = tote;
		E[++tote].to = u, E[tote].next = last[v], last[v] = tote;
	}
	inline void add(int & x, LL d) { x = ((LL)x + d) % MOD; }
	inline void sub(int & x, LL d) { x = (LL(x - d) % MOD + MOD) % MOD; }
	int dfs(int u, int fa, int x) {
		int res = 1;
		for (int v, e = last[u]; e; e = E[e].next) {
			if ((v = E[e].to) == fa) continue;
			if ((A[x] != A[v] || v > x) && A[x] >= A[v] && A[x] - A[v] <= K)
				res = (LL)res * (dfs(v, u, x) + 1) % MOD;
		}
		return res;
	}

	void solve() {
		for (int i = 1, x, y; i < N; i++) {
			using FastIO::read;
			read(x), read(y);
			add_edge(x, y);
		}
		int ans = 0;
		for (int i = 1; i <= N; i++) {
			add(ans, dfs(i, 0, i));
			if (K > 0) {
				--K;
				sub(ans, dfs(i, 0, i));
				++K;
			}
		}
		printf("%d\n", ans);
	}
}
