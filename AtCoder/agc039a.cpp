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

char S[105];
int k;
std::vector<Pii> st;

int main() {
	scanf("%s%d", S, &k);
	int lens = strlen(S);
	int all = 1;
	for (int i = 1; i < lens; ++i)
		all &= S[i] == S[i - 1];
	if (all) {
		printf("%lld\n", 1ll * lens * k >> 1);
		return 0;
	}
	int cur = 0, cnt = 1;
	for (int i = 1; i < lens; i++) {
		if (S[i] == S[i - 1]) ++cnt;
		else {
			st.pb({S[cur] - 'a', cnt});
			cur = i, cnt = 1;
		}
	} st.pb({S[cur] - 'a', cnt});
	LL ans = 0;
	for (int i = 1; i + 1 < SZ(st); ++i)
		ans += st[i].sec >> 1;
	ans *= k;
	if (st[SZ(st) - 1].fir == st[0].fir) {
		ans += st.begin()->sec / 2 + st.rbegin()->sec / 2 +
			(LL)(st.begin()->sec + st.rbegin()->sec) / 2 * (k - 1);
	} else {
		ans += (LL)(st.begin()->sec / 2 + st.rbegin()->sec / 2) * k;
	}
	printf("%lld\n", ans);
	return 0;
}