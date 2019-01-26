// Luogu P3806
#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>
#include <vector>

#define pb push_back
#define fir first
#define sec second
#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif

typedef long long LL;
typedef std::pair<int, int> Pii;

const int MAXN = 1e4 + 10;
const int MAXK = 1e7 + 10;

int N, M, K, sz[MAXN], vis[MAXN], cnt[MAXK], D[MAXN];
std::vector<Pii> G[MAXN];

void Div(int, int);

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1, u, v, c; i < N; i++) {
		scanf("%d%d%d", &u, &v, &c);
		G[u].pb(Pii(v, c)), G[v].pb(Pii(u, c));
	}

	Div(1, N);
	for (; M--; ) {
		scanf("%d", &K);
		puts(cnt[K] > 0 ? "AYE" : "NAY");
	}

	return 0;
}

namespace find_cntr {
	int cntr, totsz;

	void dfs(int u, int fa) {
		sz[u] = 1;
		int mx = 0;
		for (auto e : G[u]) {
			if (vis[e.fir] || e.fir == fa) continue;
			dfs(e.fir, u);
			mx = std::max(mx, sz[e.fir]);
			sz[u] += sz[e.fir];
		}
		if (std::max(mx, totsz - sz[u]) * 2 <= totsz) cntr = u;
	}

	int find(int u, int usz) {
		totsz = usz;
		dfs(u, -1);
#ifdef DEBUG_MD
		debug(" Find Center%c", '\n');
		for (int i = 1; i <= N; i++) debug(" sz[%d] : %d\n", i, sz[i]);
#endif
		return cntr;
	}
}

namespace calcer {
	int totp;

	void dfs(int u, int fa, int dep) {
		D[totp++] = dep;
		for (auto e : G[u]) {
			if (vis[e.fir] || e.fir == fa) continue;
			dfs(e.fir, u, dep + e.sec);
		}
	}

	void calc(int u, int init_dis, int val = 1) {
		totp = 0;
		dfs(u, 0, init_dis);
		for (int i = 0; i < totp; i++)
			for (int j = i + 1; j < totp; j++) 
				cnt[D[i] + D[j]] += val;
	}
}

void Div(int u, int usz) {
	debug(" root : %d, size : %d\n", u, usz);
	u = find_cntr::find(u, usz);
	find_cntr::dfs(u, 0);
	vis[u] = 1;
	debug("   center : %d\n", u);

	calcer::calc(u, 0);
	for (auto e : G[u]) {
		if (vis[e.fir]) continue;
		calcer::calc(e.fir, e.sec, -1);
		Div(e.fir, sz[e.fir]);
	}
}
