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

const int kInf = 0x3f3f3f3f, kMod = 2333, P = 2333;
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

int C[P + 5][P + 5], F[P + 5][P + 5];
LL n, k;

int Solve(LL n, LL k);

int main() {
	C[0][0] = 1;
	for (int i = 0; i < P; ++i) F[0][i] = 1;
	for (int i = 1; i < P; ++i) {
		for (int j = C[i][0] = F[i][0] = 1; j <= i; ++j) {
			C[i][j] = Add(C[i - 1][j], C[i - 1][j - 1]);
			F[i][j] = Add(F[i][j - 1], C[i][j]);
		}
		for (int j = i + 1; j < P; ++j)
			F[i][j] = F[i][j - 1];
	}
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%lld%lld", &n, &k);
		printf("%d\n", Solve(n, k));
	} return 0;
}

int Comb(LL n, LL r) {
	if (n < P && r < P) return C[n][r];
	return Mul(Comb(n / P, r / P), C[n % P][r % P]);
}

int Solve(LL n, LL k) {
	if (k < 0) return 0;
	if (n < P && k < P) return F[n][k];
	return Add(Mul(Solve(n % P, P - 1),
		Solve(n / P, k / P - 1)), Mul(Comb(n / P, k / P),
		Solve(n % P, k % P)));
}
