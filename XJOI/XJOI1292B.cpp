#include <algorithm>
#include <cstdio>
#include <vector>

#define pb push_back
#define SZ(_) (int)_.size()
#define IN inline

typedef long long LL;

const int kMaxn = 5e5 + 5, kMod = 998244353;

IN int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
IN int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
IN int Mul(int a, int b) { return 1ll * a * b % kMod; }

int n, q, p, p2, cntc;
int ctr[kMaxn], com[kMaxn], fa[kMaxn];
std::vector<int> G[kMaxn];
LL prs;

void Dfs(int);
void Tag(int, int);

int main() {
	scanf("%d%d%d", &n, &q, &p);
	for (int x, y, i = 1; i < n; ++i) {
		scanf("%d%d", &x, &y); G[y].pb(x); G[x].pb(y);
	} Dfs(1); p2 = Mul(p, p);
	for (int o, x, ex2, e2x; q--; ) {
		scanf("%d", &o);
		if (o == 1) {
			scanf("%d", &x);
			Tag(x, x), Tag(fa[x], x);
			for (int i = 0; i < SZ(G[x]); ++i) Tag(G[x][i], x);
			G[x].clear();
		} else {
			ex2 = Add(Mul((1ll * cntc * cntc -
				prs) % kMod, p2), Mul(prs % kMod, p));
			e2x = Mul(cntc, p), e2x = Mul(e2x, e2x);
			printf("%d\n", Sub(ex2, e2x));
		}
	}
	return 0;
}

void Tag(int u, int v) {
	if (!u || ctr[u] == v) return;
	if (!ctr[u]) { ++cntc, ++prs; }
	else {
		prs -= --com[ctr[u]] * 2ll;
		if (ctr[u] == fa[u]) G[fa[u]].pb(u);
	} prs += com[ctr[u] = v]++ * 2ll;
}

void Dfs(int u) {
	for (int i = 0, v; i < SZ(G[u]); ++i) {
		if ((v = G[u][i]) == fa[u]) continue;
		fa[v] = u; Dfs(v);
	}
}
