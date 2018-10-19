// Codeforces 711 D
// Round #369 (Div. 2)
#pragma GCC diagnostic error "-std=c++11"
#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#define pb push_back
typedef long long LL;
const int MAXN = 2e5 + 10;
const int MOD = 1e9 + 7;
struct Edge {
	int to, tag, next;
} E[MAXN];

int N, last[MAXN], tote, vis[MAXN];
std::vector<int> loop;
std::stack<int> lnk;

namespace FastIO {
	template <typename T>
		void read(T & x) {
			x = 0; register char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
}
inline void add_edge(int u, int v) {
	E[++tote].to = v, E[tote].next = last[u], last[u] = tote;
}
LL fast_pow(LL bs, int ex) {
	LL res = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1) if (ex & 1) (res *= bs) %= MOD;
	return res;
}
void dfs(int u, int col);

int main() {
	using FastIO::read;
	read(N);
	for (int i = 1, ai; i <= N; i++) {
		read(ai);
		add_edge(i, ai);
	}
	for (int i = 1, col = 0; i <= N; i++)
		if (!vis[i]) dfs(i, ++col);
	LL ans = 1;
	for (auto sz : loop) (ans *= fast_pow(2, sz) - 2) %= MOD, N -= sz;
	(ans *= fast_pow(2, N)) %= MOD;
	std::cout << ans << std::endl;
	return 0;
}

void dfs(int u, int col) {
	vis[u] = col, lnk.push(u);
	for (int v, e = last[u]; e; e = E[e].next) {
		if (vis[v = E[e].to]) {
			if (vis[v] != col) continue;
			int sz = 0;
			for (; !lnk.empty() && lnk.top() != v; lnk.pop()) ++sz;
			if (!lnk.empty() && lnk.top() == v) ++sz, lnk.pop();
			loop.pb(sz);
			continue;
		}
		dfs(v, col);
	}
	if (!lnk.empty() && lnk.top() == u) lnk.pop();
}

// AC!!!
