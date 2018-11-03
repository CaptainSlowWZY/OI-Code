#pragma GCC diagnostic error "-std=c++11"
#include <cstdio>
#include <vector>

#define rg register
#define gch getchar
#define pb push_back

const int MAXN = 1e6 + 10;

int N;
std::vector<int> G[MAXN];

namespace FastIO {
	template <typename T>
	void read(T & x) {
		rg char ch = gch();
		for (; ch < '0' || ch > '9'; ch = gch());
		for (x = 0; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = gch());
	}
}
int dfs(int, int);

int main() {
	using FastIO::read;

	read(N);
	if (N == 1) return puts("0"), 0;
	for (int i = 1, ui, vi; i < N; i++) {
		read(ui), read(vi);
		G[ui].pb(vi), G[vi].pb(ui);
	}

	for (int i = 1; i <= N; i++)
		if (G[i].size() > 2) return printf("%d\n", dfs(i, 0)), 0;
	
	puts("1");
	return 0;
}

int dfs(int u, int fa) {
	int ret = 0, f = 0;
	for (auto v : G[u]) {
		if (v == fa) continue;
		int tmp = dfs(v, u);
		ret += tmp;
		if (!tmp) f ? ++ret : f = 1;
	}
	return ret;
}