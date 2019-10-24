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

#define fi first
#define se second
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

const int kMaxn = 5e5 + 5;

int n, q;
int pw2[kMaxn], sfx[kMaxn], spr[kMaxn];
int fa[kMaxn], ans[kMaxn], A[kMaxn], pre[kMaxn];
LL sum[kMaxn];
std::vector<Pii> Q[kMaxn];

inline int Query(int l, int r) {
/*	printf(" query[%d, %d], sfxl %d, sfxr %d, pw %d\n",
			l, r, sfx[l], sfx[r + 1], pw2[r - l + 1]);
	printf("  res = %d\n", Sub(sfx[l], Mul(sfx[r + 1], pw2[r - l + 1]))); */
	return Sub(sfx[l], Mul(sfx[r + 1], pw2[r - l + 1]));
}
inline int Find(int x) { return x == fa[x] ? x : (fa[x] = Find(fa[x])); }
void Merge(int p, int q);

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", A + i); fa[i] = i, pre[i] = i - 1;
	}
	for (int i = 0, l, r; i < q; ++i) {
		scanf("%d%d", &l, &r);
		Q[r].pb({l, i});
	}
	for (int i = pw2[0] = 1; i <= n; ++i)
		pw2[i] = Mul(pw2[i - 1], 2);
	for (int i = n; i; --i)
		sfx[i] = Add(Mul(sfx[i + 1], 2), Add(kMod, A[i]));
	for (int i = 1; i <= n; ++i) {
		sum[i] = A[i];
		while (pre[i] && sum[i] >= 0) Merge(pre[i], i);
		spr[i] = Add(spr[pre[i]], Query(pre[i] + 1, i));
//		printf(" pre[%d] = %d, spr[%d] = %d\n", i, pre[i], i, spr[i]);
		for (auto & p : Q[i]) {
			int j = Find(p.fi);
//			printf("    spr[%d] %d, spr[%d] %d\n", i, spr[i], j, spr[j]);
//			printf("    Query(%d, %d) = %d\n", p.fi, j, Query(p.fi, j));
			ans[p.se] = Add(Mul(2, Sub(spr[i], spr[j])), Query(p.fi, j));
		}
	}
	for (int i = 0; i < q; ++i) printf("%d\n", ans[i]);
	return 0;
}

void Merge(int p, int q) {
	fa[p] = fa[q], pre[q] = pre[p];
	int len = p - pre[p];
	if (len > 30 && sum[q] > 0 ||
		(sum[q] << len) + sum[p] > kMod) sum[q] = kMod;
	else sum[q] = (sum[q] << len) + sum[p];
}
