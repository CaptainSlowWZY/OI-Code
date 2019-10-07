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

const int kMaxn = 2e5 + 5;

int n, a, b, x, y;
int A[kMaxn];
LL k;

bool Check(int m) {
	LL lcm = 1ll * a * b / std::__gcd(a, b);
	int cd = m / lcm, ca = m / a - cd, cb = m / b - cd;
	LL sum = 0;
	for (int i = 0; i < m; ++i) {
		if (cd) { sum += (LL)A[i] * (x + y); --cd; }
		else if (ca) { sum += (LL)A[i] * x; --ca; }
		else if (cb) { sum += (LL)A[i] * y; --cb; }
		else break;
	}
//	printf(" check %d, %lld\n", m, sum);
	return sum >= k;
}

void Solve() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", A + i); A[i] /= 100;
	}
	std::sort(A, A + n, std::greater<int>());
	scanf("%d%d%d%d%lld", &x, &a, &y, &b, &k);
	if (x < y) { std::swap(x, y); std::swap(a, b); }
	if (!Check(n)) { puts("-1"); return; }
	int lb = 0, ub = n;
	while (ub - lb > 1) {
		int mid = lb + ub >> 1;
		if (Check(mid)) ub = mid;
		else lb = mid;
	} printf("%d\n", lb + 1);
}
