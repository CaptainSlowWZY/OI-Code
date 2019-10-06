// card
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

const int kMaxn = 1005;

int n;
int C[kMaxn];
Vi W, rc;

int Count(int);

int main() {
	scanf("%d", &n);
	W.resize(n);
	for (int i = 0; i < n; ++i) scanf("%d", C + i);
	for (int i = 0; i < n; ++i) scanf("%d", &W[i]);

	for (int j = 0; j < n; ++j) rc.pb(C[j]);
	SORT(W); SORT(rc);
	int rem = Count(-1);
	// printf(" rem = %d\n", rem);
	for (int i = 0; i < n; ++i) {
		rc.clear();
		for (int j = i + 1; j < n; ++j) rc.pb(C[j]);
		SORT(rc);
		Vi::iterator it = UB(W, C[i]);
		int lb, ub = SZ(W);
		if (it == W.end()) lb = 0;
		else lb = it - W.begin();
		while (ub - lb > 1) {
			int mid = lb + ub >> 1;
			// printf(" [%d, %d) mid %d\n", lb, ub, mid);
			if (Count(mid) + (C[i] < W[mid]) == rem) lb = mid;
			else ub = mid;
		}
		rem -= (C[i] < W[lb]);
		printf("%d ", W[lb]);
		W.erase(W.begin() + lb);
	} pch('\n');
	return 0;
}

int Count(int inv) {
	int res = 0;
	for (int i = SZ(W) - 1, j = SZ(rc) - 1; i >= 0; --i) {
		if (i == inv) continue;
		while (j >= 0 && rc[j] >= W[i]) --j;
		if (j < 0) break;
		--j, ++res;
	}
	// printf(" count %d, %d(w %d) = %d\n", avi, inv, W[inv], res);
	return res;
}

/*

5
1 2 3 4 5
2 4 6 8 10

6
132 4 5 2 3 1
2 4 6 8 10 23

6
21 43 5 7 1 4
6 3 88 2 8 2
*/
