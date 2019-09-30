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

const int kMaxn = 2e5 + 5;

int n, top, dfs_clock;

namespace smt {
	struct Node { int max, tag; } T[kMaxn << 2];
	inline int Id(int l, int r) { return l + r | l != r; }
	inline int Query() { return T[Id(1, n * 2)].max; }
	void Modify(int l, int r, int ql, int qr, int d);
}

int A[kMaxn << 1], S[kMaxn << 1], idfn[kMaxn << 1];
int ch[kMaxn << 1][2], fa[kMaxn << 1], odfn[kMaxn << 1];

void Dfs(int u);

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", A + i);
		A[n + i] = A[i];
	}
	
	for (int i = 1, la; i <= n * 2; ++i) {
		la = -1;
		for (int v; top; ) {
			if (A[v = S[top - 1]] <= A[i]) {
				if (ch[v][1]) {
					ch[i][0] = ch[v][1];
					fa[ch[v][1]] = i;
				} fa[ch[v][1] = i] = v;
				break;
			} la = S[--top];
		} if (!top && ~la)
			fa[ch[i][0] = la] = i;
		S[top++] = i;
	}
	Dfs(S[0]);
	for (int i = 1; i <= n; i++)
		smt::Modify(1, n << 1, idfn[i], odfn[i], 1);
	int ans = smt::Query(), k = 0;
	for (int i = n + 1; i <= n * 2; i++) {
		smt::Modify(1, n << 1, idfn[i - n], odfn[i - n], -1);
		smt::Modify(1, n << 1, idfn[i], odfn[i], 1);
		if (smt::Query() < ans) {
			ans = smt::Query(), k = i - n;
		}
	} printf("%d %d\n", ans, k);
	return 0;
}

namespace smt {
#define LSON Id(l, mid)
#define RSON Id(mid + 1, r)
	void PushDown(int l, int mid, int r) {
		int cur = Id(l, r);
		if (T[cur].tag) {
			int ls = LSON, rs = RSON;
			T[ls].max += T[cur].tag, T[ls].tag += T[cur].tag;
			T[rs].max += T[cur].tag, T[rs].tag += T[cur].tag;
			T[cur].tag = 0;
		}
	}
	void Modify(int l, int r, int ql, int qr, int d) {
		int cur = Id(l, r);
		if (ql <= l && r <= qr) {
			T[cur].max += d, T[cur].tag += d;
			return;
		} int mid = l + r >> 1;
		PushDown(l, mid, r);
		if (ql <= mid) Modify(l, mid, ql, qr, d);
		if (qr > mid) Modify(mid + 1, r, ql, qr, d);
		T[cur].max = std::max(T[LSON].max, T[RSON].max);
	}
}

void Dfs(int u) {
	idfn[u] = ++dfs_clock;
	if (ch[u][0]) Dfs(ch[u][0]);
	if (ch[u][1]) Dfs(ch[u][1]);
	odfn[u] = dfs_clock;
}
