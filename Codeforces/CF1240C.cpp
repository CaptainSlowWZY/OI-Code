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
// const double kPie = acos(-1), kEps = 1e-9;

template <typename T> inline
void UMin(T & x, const T & y) { if (x > y) x = y; }
template <typename T> inline
void UMax(T & x, const T & y) { if (x < y) x = y; }
inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

void Solve();

int main() {
	int q;
	scanf("%d", &q);
	while (q--) Solve();
	return 0;
}

const int kMaxn = 5e5 + 5;

int n, k;
LL DP[kMaxn][2];
std::vector<Pii> G[kMaxn];

void Dfs(int u, int fa) {
	for (auto & p : G[u]) {
		if (p.fir == fa) continue;
		Dfs(p.fir, u);
	}
	std::vector<Pli> buf;
	LL sum = 0;
	for (auto & p : G[u]) {
		if (p.fir == fa) continue;
		sum += DP[p.fir][0];
		buf.pb({DP[p.fir][0] - DP[p.fir][1] - p.sec, p.fir});
	} SORT(buf);
	for (int i = 0; i + 1 < k && i < SZ(buf); ++i) {
		if (buf[i].fir >= 0) break;
		sum -= buf[i].fir;
	} DP[u][1] = sum;
	if (k - 1 < SZ(buf) && buf[k - 1].fir < 0)
		sum -= buf[k - 1].fir;
	DP[u][0] = sum;
}

void Solve() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i)
		G[i].clear();
	for (int i = 1, u, v, c; i < n; ++i) {
		scanf("%d%d%d", &u, &v, &c);
		G[u].pb({v, c}); G[v].pb({u, c});
	}
	Dfs(1, 0);
	printf("%lld\n", std::max(DP[1][0], DP[1][1]));
}
