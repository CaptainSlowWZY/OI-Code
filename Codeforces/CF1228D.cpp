#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
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

int n, m;
int col[100005];
Vi G[100005];

int main () {
	scanf("%d%d", &n, &m);
	for (int i = 0, x, y; i < m; i++) {
		scanf("%d%d", &x, &y);
		G[x].pb(y), G[y].pb(x);
	}

	for (int i = 1; i <= n; ++i) col[i] = 1;
	for (auto v : G[1]) col[v] = 2;
	
	int k = -1, cnt1, cnt2, cnt3;
	for (int i = 1; i <= n; ++i)
		if (col[i] != 1) {
			k = i; break;
		}
	if (k == -1) { puts("-1"); return 0; }
	for (auto v : G[k])
		if (col[v] == 2) col[v] = 3;
	cnt1 = cnt2 = cnt3 = 0;
	for (int i = 1; i <= n; ++i) {
		if (col[i] == 1) ++cnt1;
		if (col[i] == 2) ++cnt2;
		if (col[i] == 3) ++cnt3;
	}
	if (!cnt1 || !cnt2 || !cnt3) { puts("-1"); return 0; }
	if (1ll * cnt1 * cnt2 + 1ll * cnt2 * cnt3 +
		1ll * cnt1 * cnt3 != m) { puts("-1"); return 0; }
	for (int i = 1; i <= n; i++)
		for (auto v : G[i])
			if (col[i] == col[v]) { puts("-1"); return 0; }
	for (int i = 1; i <= n; i++) printf("%d ", col[i]);
	pch('\n');
	return 0;
}
