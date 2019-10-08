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

const int kMaxn = 3e5 + 5;

void Solve();

int main() {
	int q;
	scanf("%d", &q);
	while (q--) Solve();
	return 0;
}

int n;
int A[kMaxn], nxt[kMaxn], DP[kMaxn], vis[kMaxn];
Mii mp[kMaxn];

void Solve() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", A + i);
		mp[i].clear(); DP[i] = 0, nxt[i] = -1;
	} mp[n].clear(); DP[n] = 0, nxt[n] = -1;
	LL ans = 0;
	for (int i = n - 1; i >= 0; --i) {
		if (mp[i + 1].count(A[i]))
			nxt[i] = mp[i + 1][A[i]];
		if (~nxt[i]) {
			ans += (DP[i] = DP[nxt[i] + 1] + 1);
			std::swap(mp[i], mp[nxt[i] + 1]);
			if (nxt[i] < n - 1)
				mp[i][A[nxt[i] + 1]] = nxt[i] + 1;
		} mp[i][A[i]] = i;
	} printf("%lld\n", ans);
}
