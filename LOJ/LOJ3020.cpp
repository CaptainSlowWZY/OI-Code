#include <algorithm>
// #include <cassert>
#include <cctype>
#include <cmath>
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

const int kMaxn = 4e6 + 5, kSqrt = 2e3 + 100;

typedef int Blc[kSqrt];
typedef int IAr[kMaxn];

LL x;
int m, n, bsz, totp, a, b, k;
Blc sum0[kSqrt], beg, sum1;
IAr P, sum2, phi, np, bel;

inline int Id(int x) { return (x + bsz - 1) / bsz; }
inline int Pos(int x) { return x - beg[bel[x]] + 1; }
int Sum(int l, int r);

int main() {
	scanf("%d%d", &m, &n);
	bsz = (int)floor(sqrt(n + 0.5));
//	printf(" BLOCK SIZE = %d\n", bsz);
	memset(beg, 0xff, sizeof beg);
	for (int i = 1; i <= n; ++i) {
		if (beg[bel[i] = Id(i)] == -1) beg[bel[i]] = i;
		sum0[bel[i]][Pos(i)] =
			Add(sum0[bel[i]][Pos(i) - 1], Mul(i, i));
	}
	for (int i = 1; i <= bel[n]; ++i)
		sum1[i] = Add(sum1[i - 1], (i < bel[n] ?
			sum0[i][bsz] : sum0[i][Pos(n)]));
	sum2[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!np[i]) { P[totp++] = i, phi[i] = i - 1; }
		for (int j = 0, d; j < totp && (d = i * P[j]) <= n; ++j) {
			np[d] = 1;
			if (i % P[j] == 0) { phi[d] = phi[i] * P[j]; break; }
			phi[d] = phi[i] * (P[j] - 1);
		} sum2[i] = Add(sum2[i - 1], Mul(phi[i], Mul(i, i)));
	}
	while (m--) {
		scanf("%d%d%lld%d", &a, &b, &x, &k);
		int g = std::__gcd(a, b), id = bel[g], p = Pos(g), 
			o = Sub(sum0[id][p], sum0[id][p - 1]), 
			d = Sub(x / (1ll * a / g * b / g) % kMod, o);
	//	printf(" id %d, p %d, o %d, d = %d\n", id, p, o, d);
		for (int i = p, la = id == bel[n] ? Pos(n) : bsz;
			i <= la; ++i) sum0[id][i] = Add(sum0[id][i], d);
		for (int i = id; i <= bel[n]; ++i)
			sum1[i] = Add(sum1[i], d);
		int ans = 0;
		for (int i = 1, j; i <= k; i = j + 1) {
			j = k / (k / i);
		//	printf(" [%d, %d] sum %d\n", i, j, Sum(i, j));
			ans = Add(ans, Mul(Sum(i, j), sum2[k / i]));
		} printf("%d\n", ans);
	} return 0;
}

int Sum(int l, int r) {
	int idl = bel[l], idr = bel[r];
/*	printf(" id%d %d, pos %d; id%d %d, pos %d\n",
		l, idl, Pos(l), r, idr, Pos(r)); */
	if (idl == idr) 
		return Sub(sum0[idl][Pos(r)], sum0[idl][Pos(l) - 1]);
	return Add(Add(Sub(sum0[idl][bsz], sum0[idl][l - beg[idl]]),
		sum0[idr][Pos(r)]), Sub(sum1[idr - 1], sum1[idl]));
}
