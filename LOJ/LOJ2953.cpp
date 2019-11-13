// NOIP2018 ReAc
#include <algorithm>
#include <cstdio>
#include <vector>

#define pb push_back
#define FORV(T, I, _) for (std::vector<T>::iterator I = _.begin(); I != _.end(); ++I)

const int kMaxn = 5e3 + 5;

struct Edge { int to, tag, next; } E[kMaxn << 1];

int n, m, eu, ev, dfsc, got, top, vis[kMaxn], onl[kMaxn], ans[kMaxn], buf[kMaxn], S[kMaxn];
std::vector<int> G[kMaxn];

void Find(int, int);
void Dfs(int, int);

int main() {
#ifndef LOCAL
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for (int i = 0, u, v; i < m; ++i) { scanf("%d%d", &u, &v); G[u].pb(v); G[v].pb(u); }
	for (int i = 1; i <= n; ++i) { std::sort(G[i].begin(), G[i].end()); ans[i - 1] = n; }
	if (m == n) {
		Find(1, 0);
		for (int i = 1, fail; i <= n; ++i) if (onl[i]) FORV(int, v, G[i]) if (*v > i && onl[*v]) {
		//	printf(" - %d, %d\n", i, *v);
			eu = i, ev = *v, dfsc = 0; Dfs(1, 0);
			if (dfsc < n) continue;
			for (int j = fail = 0; j < n; ++j) if (buf[j] > ans[j]) { fail = 1; break; } else if (buf[j] < ans[j]) break;
			if (!fail) {
				for (int j = 0; j < n; ++j) ans[j] = buf[j];
			}
		}
	} else {
		Dfs(1, 0);
		for (int i = 0; i < n; ++i) ans[i] = buf[i];
	}
	for (int i = 0; i < n; ++i) printf("%d%c", ans[i], i + 1 == n ? '\n' : ' ');
#ifndef LOCAL
	fclose(stdin); fclose(stdout);
#endif
	return 0;
}

void Find(int u, int fa) {
	vis[S[top++] = u] = 1;
	FORV(int, v, G[u]) if (*v != fa) {
		if (vis[*v]) {
			for (onl[*v] = 1; top && S[top - 1] != *v; ) onl[S[--top]] = 1; 
			--top; got = 1; return;
		} Find(*v, u);
		if (got) return;
	} if (top && S[top - 1] == u) --top;
}

void Dfs(int u, int fa) {
	buf[dfsc++] = u;
	FORV(int, v, G[u]) {
		if (*v == fa || u == eu && *v == ev || u == ev && *v == eu) continue;
		Dfs(*v, u);
	}
}
