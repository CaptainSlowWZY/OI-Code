#include <bits/stdc++.h>
#define pb push_back
#define SZ(_) (int)_.size()
#define JUMP(U, _, __) for (int _ = kLg - 1; _ >= 0; --_) \
		if (F[U][_] && __) U = F[U][_];
const int kMaxn = 3e5 + 5, kLg = 19;

int n, m, D[kMaxn], dep[kMaxn], F[kMaxn][kLg];
std::vector<int> G[kMaxn], d1, nxt;
std::set<int> B;

void Dfs(int u);
void ErLev(int lim = -1);
int Lca(int u, int v);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		G[u].pb(v), G[v].pb(u); ++D[u], ++D[v];
	} dep[1] = 1; Dfs(1);
	for (int i = 1; i <= n; ++i) {
		B.insert(i); if (D[i] == 1) d1.pb(i);
	}
	for (int p, l, u; m--; ) {
		scanf("%d", &p);
		if (B.count(p)) ErLev(p);
		else if (B.count(l = Lca(u = *B.begin(), p))) {
			JUMP(p, i, dep[F[p][i]] >= dep[l] && !B.count(F[p][i]))
			++D[F[p][0]], D[p] = 1; ErLev(F[p][0]);
			d1.pb(p); B.insert(p);
		} else {
			JUMP(u, i, dep[F[p][i]] >= dep[u] && B.count(F[u][i]))
			++D[u]; ErLev(u); D[F[u][0]] = 1;
			d1.pb(F[u][0]); B.insert(F[u][0]);
		} 
		if (SZ(B) == 1) break;
	} printf("%d\n", SZ(B));
	return 0;
}

void ErLev(int lim) {
	for (auto u : d1) {
		if (u == lim) { if (D[u] <= 1) nxt.pb(u); continue; }
		for (auto v : G[u]) if (B.count(v)) {
			if (--D[v] <= 1) nxt.pb(v); break;
		} B.erase(u), D[u] = 0;
	} std::swap(nxt, d1); nxt.clear();
}
int Lca(int u, int v) {
	if (dep[u] < dep[v]) std::swap(u, v);
	int d = dep[u] - dep[v]; JUMP(u, i, d >> i & 1)
	if (u == v) return u;
	for (int i = kLg - 1; i >= 0; --i) 
		if (F[u][i] != F[v][i]) { u = F[u][i], v = F[v][i]; }
	return F[u][0];
}
void Dfs(int u) {
	for (int i = 1; i < kLg && F[u][i - 1]; ++i)
		F[u][i] = F[F[u][i - 1]][i - 1];
	for (auto v : G[u]) {
		if (v == F[u][0]) continue;
		dep[v] = dep[u] + 1, F[v][0] = u; Dfs(v);
	}
}
