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
typedef std::vector<Pii> Vp;
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

const int kMaxn = 1e5 + 5;

int n;
int A[kMaxn];
Vp odd, eve;
Vi ep, op;

LL Calc(int a0);
void Solve(Vp & vec, Vi & pos);

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", A + i);
		if (A[i] & 1) odd.pb({A[i], i}); else eve.pb({A[i], i});
	}
	int la = SZ(odd) > SZ(eve) ? 0 : (SZ(odd) < SZ(eve) ? 1 :
			(Calc(0) <= Calc(1) ? 0 : 1));
	for (int i = 0; i < n; ++i, la ^= 1)
		if (la & 1) ep.pb(i); else op.pb(i);
	Solve(odd, op); Solve(eve, ep);
	for (int i = 0; i < n; ++i) printf("%d ", A[i]); pch('\n');
	return 0;
}

LL Calc(int a0) {
	LL res = 0;
	for (int i = 0, e = 0, o = 0; i < n; ++i) {
		if (a0 & 1) res += abs(eve[e++].sec - i);
		else res += abs(odd[o++].sec - i);
		a0 ^= 1;
	} return res;
}

inline int Dirc(int x, int y) {
	return x == y ? 0 : (x > y ? -1 : 1);
}

void Solve(Vp & vec, Vi & pos) {
	int ld = -2, la = 0, n = SZ(vec),
		t = Dirc(vec[n - 1].sec, pos[n - 1]);
	vec.pb({0, t ? 0 : kInf}); pos.pb(0);
	for (int d, i = 0; i <= n; ++i) {
		d = Dirc(vec[i].sec, pos[i]);
		if (d != ld) {
			Si P;
			if (ld == -1) {
				for (int j = la; j < i; ++j) P.insert(pos[j]);
				std::sort(vec.begin() + la, vec.begin() + i,
					std::greater<Pii>());
				for (int j = la; j < i; ++j) {
					auto it = P.upper_bound(vec[j].sec);				
					A[*(--it)] = vec[j].fir; P.erase(it);
				}
			}
			if (ld == 1) {
				for (int j = la; j < i; ++j) P.insert(pos[j]);
				std::sort(vec.begin() + la, vec.begin() + i);
				for (int j = la; j < i; ++j) {
					auto it = P.lower_bound(vec[j].sec);				
					A[*it] = vec[j].fir; P.erase(it);
				}
			}
			if (!ld) {
				for (int j = la; j < i; ++j)
					A[pos[j]] = vec[j].fir;
			}
			ld = d, la = i;
		}
	}
}
