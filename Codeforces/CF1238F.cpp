#include <algorithm>
// #include <cassert>
#include <cctype>
// #include <cmath>
#include <cstdio>
// #include <cstdlib>
#include <cstring>
// #include <ctime>
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
#define SORT(_) std::sort(_.begin(), _.end())
#define LB(_, __) std::lower_bound(_.begin(), _.end(), __)
#define UB(_, __) std::upper_bound(_.begin(), _.end(), __)
#ifdef DEBUG
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif

typedef long long LL;
typedef double DB;
typedef std::pair<DB, DB> Pdd;
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
// const double kPie = acos(-1), kEps = 1e-9;

int mod;

template <typename T> inline
void UMin(T & x, const T & y) { if (x > y) x = y; }
template <typename T> inline
void UMax(T & x, const T & y) { if (x < y) x = y; }
inline int Add(int a, int b) { return (a += b) >= mod ? a - mod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + mod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % mod; }
int FPow(int bs, int ex = mod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

/* NOTICE! The default mod number is 1e9 + 7 ! */

const int kMaxn = 3e5 + 5;

int n, deg[kMaxn], DP[kMaxn][2];
Vi G[kMaxn];

void Dfs(int, int);

int main() {
	int q; scanf("%d", &q);
	while (q--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			G[i].clear(); deg[i] = 0;
		}
		for (int x, y, i = 1; i < n; ++i) {
			scanf("%d%d", &x, &y);
			G[x].pb(y); G[y].pb(x); ++deg[x], ++deg[y];
		}
		Dfs(1, 0);
		printf("%d\n", std::max(DP[1][0], DP[1][1]));
	} return 0;
}

void Dfs(int u, int fa) {
	int max1 = 0, max2 = 0;
	DP[u][0] = DP[u][1] = 0;
	for (auto v : G[u]) {
		if (v == fa) continue;
		Dfs(v, u);
		UMax(DP[u][0], DP[v][0]);
		if (DP[v][1] > max1) {
			max2 = max1; max1 = DP[v][1];
		} else if (DP[v][1] > max2) max2 = DP[v][1];
	} UMax(DP[u][0], deg[u] + 1 + max1 + max2);
	DP[u][1] = deg[u] - 1 + max1;
}	
