#include <cstdio>
#include <vector>

#define pb push_back

const int kMaxn = 1e5 + 5, kMod = 998244353;

int n, m;
int slc[kMaxn], slf[kMaxn];
std::vector<int> G[kMaxn];

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }

void Dfs1(int, int);
void Dfs2(int, int);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		G[u].pb(v); G[v].pb(u);
	}
	Dfs1(1, 0); Dfs2(1, 0);
	int la = 0, a0, lr = slc[1];
	for (int i = 1; i <= n; ++i)
		la += slc[i];
	a0 = la;
	printf("%d\n", a0);
	for (int i = 0, k; i < m; ++i) {
		scanf("%d", &k);
		la = Add(Mul(n, la), lr ? 0 : a0);
		if (lr) lr = 0;
		else lr = slc[k] & !slf[k];
		printf("%d\n", la);
	} return 0;
}

void Dfs1(int u, int fa) {
	slc[u] = 1;
	for (auto v : G[u]) {
		if (v == fa) continue;
		Dfs1(v, u);
		slc[u] &= !slc[v];
	}
}

void Dfs2(int u, int fa) {
	int cnt = 0;
	for (auto v : G[u]) {
		if (v == fa) continue;
		cnt += slc[v];
	}
	for (auto v : G[u]) {
		if (v == fa) continue;
		slf[v] = !slf[u] && !(cnt - slc[v]);
		Dfs2(v, u);
	}
}
