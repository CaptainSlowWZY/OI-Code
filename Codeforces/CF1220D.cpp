#include <algorithm>
// #include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>
// #include <cmath>
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

int n;
Vl B[60];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		LL bi, bi0;
		scanf("%lld", &bi);
		int k = 0;
		for (bi0 = bi; !(bi & 1); bi >>= 1, ++k);
		B[k].pb(bi0);
	}
	int k = 0;
	for (int i = 1; i < 60; i++) {
		if (B[i].size() > B[k].size()) k = i;
	} printf("%d\n", n - SZ(B[k]));
	for (int i = 0; i < 60; i++) {
		if (B[i].empty() || i == k) continue;
		for (auto j : B[i]) printf("%lld ", j);
	} pch('\n');
	return 0;
}
