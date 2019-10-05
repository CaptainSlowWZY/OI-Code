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

int n;
char M[205];
int A[205][205], col[205];

void Dfs(int u);

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%s", M);
		for (int j = 0; j < n; ++j) {
			A[i][j] = M[j] == '1' ? 1 : kInf;
		}
	}
	memset(col, 0xff, sizeof col);
	col[1] = 1;
	Dfs(1);
	for (int i = 0; i < n; ++i) A[i][i] = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k)
				UMin(A[j][k], A[j][i] + A[i][k]);
		}
	} int ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			UMax(ans, A[i][j]);
	} printf("%d\n", ans + 1);
	return 0;
}

void Dfs(int u) {
	for (int i = 0; i < n; ++i) {
		if (A[u][i] == kInf) continue;
		if (~col[i]) {
			if (col[i] == col[u]) {
				puts("-1");
				exit(0);
			}
		} else {
			col[i] = col[u] ^ 1;
			Dfs(i);
		}
	}
}