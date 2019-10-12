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

const int kInf = 0x3f3f3f3f, kMod = 998244353;
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

/* NOTICE! The default mod number is 1e9 + 7 ! */

const int kMaxn = 1005;

typedef int IAr[kMaxn];

int n, m;
IAr A, ideg, way, num, sum, tot, out, in;
Vi G[kMaxn], prv[kMaxn];
std::priority_queue<int, Vi, std::greater<int> > hap;

int main() {
	// freopen("out", "w", stdout);
	scanf("%d%d", &n, &m);
	int s = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", A + i); s = Add(s, A[i]);
	}
	for (int x, y; m--; ) {
		scanf("%d%d", &x, &y);
		if (x > y) std::swap(x, y);
		G[y].pb(x); ++ideg[x];	// x < y -> hx > hy
	}
	for (int i = 1; i <= n; ++i)
		if (!ideg[i]) hap.push(i);
	int x = 0;
	while (!hap.empty()) {
		int u = hap.top(); hap.pop();
		num[u] = ++x;
		for (auto v : G[u])
			if (!(--ideg[v])) hap.push(v);
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1, la = kInf; j <= n; ++j) {
			if (num[i] < num[j] && num[j] < la) {
				prv[j].pb(i); la = num[j];
				out[i] = in[j] = 1;
			}
		}
	}
	for (int i = 0; i <= n; ++i) {
		if (!in[i]) {
			way[i] = 1, sum[i] = A[i];
			tot[i] = Mul(Sub(s, A[i]), A[i]);
		}
		for (auto j : prv[i]) {
			sum[i] = Add(sum[i], Add(sum[j], Mul(A[i], way[j])));
			tot[i] = Add(tot[i], Sub(Add(tot[j],
				Mul(A[i], Sub(Mul(way[j], s), Mul(2, sum[j])))),
				Mul(way[j], Mul(A[i], A[i]))));
			way[i] = Add(way[i], way[j]);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (out[i]) continue;
		ans = Add(ans, tot[i]);
	} printf("%d\n", ans);
	return 0;
}