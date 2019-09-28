#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <set>
#include <vector>

#define fir first
#define sec second
#define pb push_back
#define pch putchar
#define rg register
#define SZ(_) (int)_.size()

typedef long long LL;
typedef std::pair<int, int> Pii;
typedef std::pair<LL, int> Pli;
typedef std::pair<int, LL> Pil;
typedef std::pair<LL, LL> Pll;
typedef std::vector<int> Vi;
typedef std::vector<LL> Vl;
typedef std::map<int, int> Mii;
typedef std::map<LL, int> Mli;
typedef std::map<int, LL> Mil;
typedef std::map<LL, LL> Mll;
typedef std::set<int> Si;
typedef std::set<LL> Sl;

const int kInf = 0x3f3f3f3f, kMod = 1e9 + 7;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;

template <typename T> inline
void UMin(T & x, const T & y) {
	if (x > y) x = y;
}
template <typename T> inline
void UMax(T & x, const T & y) {
	if (x < y) x = y;
}
inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

const int kMaxn = 5e5 + 5, kMaxd = 22;

int n, d, m;
int W[kMaxn], vis[kMaxn];
int F[kMaxn][kMaxd], G[kMaxn][kMaxd];
Vi T[kMaxn];

void Dfs(int u, int fa);

int main() {
	scanf("%d%d", &n, &d);
	for (int i = 1; i <= n; i++) scanf("%d", W + i);
	scanf("%d", &m);
	for (int v; m--; ) {
		scanf("%d", &v);
		vis[v] = 1;
	}
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		T[u].pb(v), T[v].pb(u);
	}
	
	Dfs(1, 0);
	printf("%d\n", G[1][0]);
	return 0;
}

void Dfs(int u, int fa) {
	if (vis[u]) F[u][0] = G[u][0] = W[u];
	for (int i = 1; i <= d; i++) G[u][i] = W[u];
	G[u][d + 1] = kInf;
	for (auto v : T[u]) {
		if (v == fa) continue;
		Dfs(v, u);	// G - cover up, F - uncover
		for (int i = d; i >= 0; i--)
			G[u][i] = std::min(G[u][i] + F[v][i],
				G[v][i + 1] + F[u][i + 1]);
		for (int i = d; i; i--)
			UMin(G[u][i - 1], G[u][i]);
		F[u][0] = G[u][0];
		for (int i = 1; i <= d + 1; i++)
			F[u][i] += F[v][i - 1];
		for (int i = 0; i <= d; i++)
			UMin(F[u][i + 1], F[u][i]);
	}
}
