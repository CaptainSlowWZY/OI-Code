// string
#include <algorithm>
#include <cassert>
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

const int kMaxk = 3e6 + 5, kMaxn = 5005;

char S[kMaxk], ans[kMaxk];
int k, n;
int nxt[kMaxk], prv[kMaxk], fa[kMaxk];
int R[kMaxn], L[kMaxn];

namespace bit {
	void Add(int p, int d);
	void Init(int k);
	int Find(int x);
	int Remain();
}
inline int One(int u) { return nxt[u]; }
inline int Orign(int u) {
	return fa[u] == u ? u : (fa[u] = Orign(fa[u]));
}
inline int Two(int u) { return One(One(u)); }

int main() {
	scanf("%s%d%d", S, &k, &n);
	for (int i = 0; i < n; ++i) scanf("%d%d", L + i, R + i);

	bit::Init(k);
	for (int i = 1; i <= k; i++) {
		nxt[i] = i + 1, prv[i] = i - 1;
	} nxt[k + 1] = k + 1, nxt[0] = 1;
	memset(fa, 0xff, sizeof fa);
	for (int i = n - 1, len, olen, elen, mir,
		l, r, u; i >= 0; --i) {
		if (R[i] > bit::Remain()) continue;
		len = R[i] - L[i] + 1;
		olen = (len >> 1) + (L[i] & 1 ? len & 1 : 0);
		elen = len - olen;
		l = bit::Find(L[i]), r = bit::Find(R[i]);
		mir = L[i] & 1 ? l : One(l), u = One(r);
		while (u <= k && olen--) {
			bit::Add(u, -1); fa[u] = mir;
			nxt[prv[u]] = nxt[u], prv[nxt[u]] = prv[u];
			u = One(u), mir = Two(mir);
		}
		mir = L[i] & 1 ? One(l) : l;
		while (u <= k && elen--) {
			bit::Add(u, -1); fa[u] = mir;
			nxt[prv[u]] = nxt[u], prv[nxt[u]] = prv[u];
			u = One(u), mir = Two(mir);
		}
	}
	for (int i = One(0), j = 0; i <= k; i = One(i))
		ans[i] = S[j++], fa[i] = i;
	for (int i = 1; i <= k; i++) {
		if (fa[i] == -1) { ans[i] = '\0'; break; }
		if (ans[i]) continue;
		ans[i] = ans[Orign(i)];
	} ans[k + 1] = '\0';
	puts(ans + 1);
	return 0;
}

namespace bit {
	int T[1 << 22], sz;

	inline int LowBit(int x) { return x & -x; }
	void Add(int p, int d) {
		for (; p <= sz; p += p & -p) T[p] += d;
	}
	void Init(int k) {
		for (sz = 1; sz < k; sz <<= 1);
		for (int i = 1; i <= k; i++) Add(i, 1);
	}
	int Find(int x) {
		int l = 1, r = sz;
		while (l < r) {
			int mid = l + r >> 1;
			if (T[mid] >= x) r = mid;
			else { x -= T[mid]; l = mid + 1; }
		} return l;
	}
	int Remain() { return T[sz]; }
}