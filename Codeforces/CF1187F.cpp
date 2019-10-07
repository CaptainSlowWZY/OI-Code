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

const int kMaxn = 2e5 + 5;

int n;
int L[kMaxn], R[kMaxn], Q[kMaxn], E[kMaxn];

inline int EqProb(int i) {
	int ale = 0;
	if (i) {
		ale = Mul(std::max(0, std::min({R[i - 1], R[i], R[i + 1]}) -
			std::max({L[i - 1], L[i], L[i + 1]})),
			FPow(Mul(R[i - 1] - L[i - 1], Mul(R[i] - L[i], R[i + 1] - L[i + 1]))));
	} return Add(Sub(1, Add(Q[i], Q[i + 1])), ale);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", L + i);
	int sume = 0;
	for (int i = 1, v; i <= n; i++) {
		scanf("%d", R + i); ++R[i];
		v = std::min(R[i], R[i - 1]) - std::max(L[i], L[i - 1]);
		if (v > 0) {
			Q[i] = Mul(v, FPow(Mul(R[i - 1] - L[i - 1], R[i] - L[i])));
			if (i == 1) Q[1] = 1;
		} E[i] = Sub(1, Q[i]), sume = Add(sume, E[i]);
	}
	int ans = 0;
	for (int i = 1, me; i <= n; ++i) {
		me = Sub(sume, E[i]);
		if (i > 1) {
			me = Sub(me, E[i - 1]);
			ans = Add(ans, EqProb(i - 1));
		}
		if (i < n) {
			me = Sub(me, E[i + 1]);
			ans = Add(ans, EqProb(i));
		}
		ans = Add(ans, Add(E[i], Mul(E[i], me)));
	} printf("%d\n", ans);
	return 0;
}