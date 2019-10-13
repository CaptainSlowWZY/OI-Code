// also see CF762F
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

const int kMaxn = 2005;
const int kPr[] = {2, 3, 5, 7, 9, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43};

int n, m;
int DP[kMaxn][13], son[13], hash[13], prv[13], sz[13];
Vi G[kMaxn], T[13];

void Dfs(int, int);
void Gao(int, int);

int main() {
	scanf("%d", &n);
	for (int i = 1, x, y; i < n; ++i) {
		scanf("%d%d", &x, &y);
		G[x].pb(y), G[y].pb(x);
	} scanf("%d", &m);
	for (int i = 1, x, y; i < m; ++i) {
		scanf("%d%d", &x, &y);
		--x, --y;
		T[x].pb(y), T[y].pb(x);
	} scanf("%d", &mod);
	int ans = 0;
	Si S;
	for (int i = 0; i < m; ++i) {
		std::fill(prv, prv + m, -1);
		std::fill(son, son + m, 0);
		Dfs(i, -1);
		if (S.count(hash[i])) continue;
		S.insert(hash[i]);
	//	printf(" rt %d\n", i);
		Gao(1, 0);
		for (int u = 1; u <= n; ++u) ans = Add(ans, DP[u][i]);
	} printf("%d\n", ans);
	return 0;
}

void Gao(int u, int fa) {
	for (auto v : G[u]) {
		if (v == fa) continue;
		Gao(v, u);
	}
	static int nxt[(1 << 12) + 5], pre[(1 << 12) + 5];
	for (int i = 0; i < m; ++i) {
	//	printf(" u %d match %d, son %d\n", u, i, son[i]);
		for (int s = son[i]; s; s = s - 1 & son[i]) nxt[s] = 0;
		nxt[0] = 1;
		for (auto v : G[u]) {
			if (v == fa) continue;
			for (int s = son[i]; s; s = s - 1 & son[i]) pre[s] = nxt[s];
			pre[0] = nxt[0];
			for (int j = 0; j < m; ++j) {
				if (son[i] >> j & 1 && DP[v][j]) {
			//	printf("    v %d match j %d, DP[v][j] %d\n",
			//			v, j, DP[v][j]);
					for (int s = son[i]; s; s = s - 1 & son[i]) {
					//	printf("      %d ^ 1 << %d = %d, pre %d\n", s, j, s ^ 1 << j, pre[s ^ 1 << j]);
						if (s >> j & 1 && (prv[j] == -1 || s >> prv[j] & 1))
							nxt[s] = Add(nxt[s], Mul(pre[s ^ 1 << j], DP[v][j]));
					}
				}
			}
		} DP[u][i] = nxt[son[i]]; // printf("   DP[%d][%d] %d\n", u, i, DP[u][i]);
	}
}

inline bool CmpHash(int u, int v) { return hash[u] < hash[v]; }

void Dfs(int u, int fa) {
	hash[u] = sz[u] = 1;
	Vi vec;
	for (auto v : T[u]) {
		if (v == fa) continue;
		Dfs(v, u); sz[u] += sz[v];
		vec.pb(v); son[u] |= 1 << v;
	} std::sort(vec.begin(), vec.end(), CmpHash);
	int la = -1;
	for (auto v : vec) {
		hash[u] = Add(hash[u], Mul(hash[v], kPr[sz[v] - 1]));
		if (~la && hash[v] == hash[la]) prv[v] = la;
		la = v;
	}
//	printf(" son[%d] %d\n", u, son[u]);
}
