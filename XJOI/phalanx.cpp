// phalanx
#pragma GCC diagnostic error "-std=c++11"
#include <cstdio>
#include <cstring>
#include <vector>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__) 
#else
	#define debug(format, ...) 0
#endif
#define pb push_back

const int MAXN = 1005;
const int MAXX = 4005;

int N, X, fr[MAXN], fc[MAXN], vis[MAXN], match[MAXN];
std::vector<int> G[MAXN];

bool dfs(int u);

int main() {
	scanf("%d%d", &N, &X);
	for (int i = 0, xi, yi; i < X; i++) {
		scanf("%d%d", &xi, &yi);
		G[xi].pb(yi);
		fr[xi] = fc[yi] = 1;
	}
	
	int ans = N * N << 1;
	for (int i = 1; i <= N; i++) {
		memset(vis, 0, sizeof vis);
		if (dfs(i)) ans -= N;
	}
	
	printf("%d\n", ans);
	return 0;
}

bool dfs(int u) {
	for (auto v : G[u]) {
		if (vis[v]) continue;
		vis[v] = 1;
		if (!match[v] || dfs(match[v])) {
			match[v] = u;
			return true;
		}
	}
	return false;
}

// AC!!!
