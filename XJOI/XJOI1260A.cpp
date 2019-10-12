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
typedef double DB;
typedef std::pair<DB, DB> Pdd;
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

/* NOTICE! The default mod number is 1e9 + 7 ! */

const int kMaxm = 2.5e5 + 5;

int n, m, typ;

namespace fhq {
	void Add(int l, int r, int k);
	void Flip(int l, int r);
	void Init();
	LL Sum(int l, int r);
}

int main() {
/*	freopen("ex_dream2.in", "r", stdin);
	freopen("out", "w", stdout);*/
	srand(19260817);
	scanf("%d%d%d", &n, &m, &typ);
	fhq::Init();
	LL la = 0, l, r, k;
	for (int o; m--; ) {
		scanf("%d%lld%lld", &o, &l, &r);
		if (typ) { l ^= la; r ^= la; }
		if (!o) {
			scanf("%lld", &k);
			if (typ) k ^= la;
			fhq::Add(l, r, k);
		} if (o == 1) {
			fhq::Flip(l, r);
		} if (o == 2) {
			printf("%lld\n", la = fhq::Sum(l, r));
		}
	}
	return 0;
}

namespace fhq {
	struct Node {
		int len, rkey, rev, sz, ch[2];
		LL per, tot, tag;
		Node() {}
		Node(int l, LL p) : len(l), sz(l), per(p) {
			tag = ch[0] = ch[1] = rev = 0;
			tot = per * len; rkey = rand();
		}
		void reverse() { std::swap(ch[0], ch[1]); rev ^= 1; }
		void add(int d) {
			per += d, tot += 1ll * sz * d, tag += d;
		}
	} T[kMaxm << 2];

#define LSON(_) T[_].ch[0]
#define RSON(_) T[_].ch[1]

	int size, root;

	inline int NewNode(int len, LL per) {
		T[++size] = Node(len, per);
		return size;
	}
	void Init() {
		root = NewNode(n, 0);
	}
	void PushDown(int u) {
		if (T[u].rev) {
			if (LSON(u)) T[LSON(u)].reverse();
			if (RSON(u)) T[RSON(u)].reverse();
			T[u].rev = 0;
		}
		if (T[u].tag) {
			if (LSON(u)) T[LSON(u)].add(T[u].tag);
			if (RSON(u)) T[RSON(u)].add(T[u].tag);
			T[u].tag = 0;
		}
	}
	inline void Maintain(int u) {
		T[u].sz = T[u].len + T[LSON(u)].sz + T[RSON(u)].sz;
		T[u].tot = T[u].len * T[u].per + T[LSON(u)].tot + T[RSON(u)].tot;
	}
	int Merge(int u, int v) {
		if (!u || !v) return u + v;
		PushDown(u); PushDown(v);
		if (T[u].rkey < T[v].rkey) {
			RSON(u) = Merge(RSON(u), v); Maintain(u);
			return u;
		} else {
			LSON(v) = Merge(u, LSON(v)); Maintain(v);
			return v;
		}
	}
	void Split(int u, int lim, int & r1, int & r2) {
		if (!u) return (void)(r1 = r2 = 0);
		PushDown(u);
		if (T[LSON(u)].sz >= lim) {
			Split(LSON(u), lim, r1, LSON(r2 = u));
		} else if (T[LSON(u)].sz + T[u].len > lim) {
			int h = lim - T[LSON(u)].sz,
				v = NewNode(T[u].len - h, T[u].per);
			T[u].len = h; r2 = Merge(v, RSON(u));
			RSON(u) = 0; r1 = u;
		} else {
			lim -= T[LSON(u)].sz + T[u].len;
			Split(RSON(u), lim, RSON(r1 = u), r2);
		} Maintain(u);
	}
	inline int Merge(int r1, int r2, int r3) {
		return Merge(r1, Merge(r2, r3));
	}

#define SPL(L, R) int rt1, rt2, rt3; \
	Split(root, R, rt1, rt3); Split(rt1, L - 1, rt1, rt2);

	void Add(int l, int r, int k) {
		SPL(l, r) T[rt2].add(k);
		root = Merge(rt1, rt2, rt3);
	}
	void Flip(int l, int r) {
		SPL(l, r) T[rt2].reverse();
		root = Merge(rt1, rt2, rt3);
	}
	LL Sum(int l, int r) {
		SPL(l, r)
		LL res = T[rt2].tot;
		root = Merge(rt1, rt2, rt3);
		return res;
	}
}