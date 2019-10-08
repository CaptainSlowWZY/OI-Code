// movie
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

struct Seg {
	int edp, tp, len, r, d;
	bool operator<(const Seg & s) const {
		return d == s.d ? (r == s.r ?
			edp > s.edp : r > s.r) : d > s.d;
	}
	friend Seg Min(const Seg & a, const Seg & b) {
		return a.d == b.d ? (a.r == b.r ?
			(a.edp < b.edp ? a : b) :
			(a.r < b.r ? a : b)) :
			(a.d < b.d ? a : b);
	}
};

const Seg kInfSeg = {0, 0, kInf, 0, kInf};
const int kMaxk = 300005;

int n, k;

namespace smt {
	Seg Query(int l, int r, int low);
	void Build(int l, int r);
	void Insert(int l, int r, const Seg & s);
	void Pop(int l, int r, int p);
}

int main() {
	scanf("%d%d", &n, &k);
	int cps = k + 1 >> 1, ub, lb;
	lb = cps, ub = cps + 1;
	smt::Build(1, k);
	for (int mi, l, r; n--; ) {
		scanf("%d", &mi);
		l = (mi >> 1), r = mi - 1 - (mi >> 1);
	//	printf("  all [%d, %d]\n", l, r);
		LL ans1, ans2, ans3, ans;
		ans1 = lb ? LL(cps - lb) * mi + (LL(l + 1) * l +
			LL(r + 1) * r >> 1) : kInf64;
		ans2 = ub <= k ? LL(ub - cps) * mi + (LL(l + 1) * l +
			LL(r + 1) * r >> 1) : kInf64;
		Seg nxt = smt::Query(1, k, mi);
	//	printf(" nxt.d = %d, r = %d, p %d, t %d, mi = %d\n", nxt.d, nxt.r, nxt.edp, nxt.tp, mi);
		if (nxt.d == kInf) ans3 = kInf64;
		else ans3 = (nxt.d * 2ll + mi - 1) * mi >> 1;
	//	printf(" ans1 %lld, ans2 %lld, ans3 %lld\n",
	//			ans1, ans2, ans3);
	//	printf("  lb = %d, ub = %d\n", lb, ub);
		ans = std::min({ans1, ans2, ans3});
		if (ans == kInf64) {
			puts("-1");
			continue;
		} l = cps - l, r += cps;
		if (ans1 == ans) {
		//	puts(" case 1");
		//	printf("   d1 = %d\n", (cps << 1) - lb - l + 1);
			if (l) smt::Insert(1, k, {l - 1, 0, l - 1, lb,
					(cps << 1) - lb - l + 1});
		//	printf("   d2 = %d\n", r + 1 - lb);
			if (r < k) smt::Insert(1, k, {r + 1, 1, k - r,
					lb, r + 1 - lb});
			printf("%d %d %d\n", lb--, l, r);
		} else if (ans3 == ans) {
			smt::Pop(1, k, nxt.len);
			nxt.len -= mi;
			if (nxt.tp) {
				l = nxt.edp, r = nxt.edp + mi - 1;
				if ((nxt.edp += mi) <= k) {
					nxt.d = abs(nxt.r - cps) + abs(nxt.edp - cps);
					smt::Insert(1, k, nxt);
				}
			} else {
				l = nxt.edp - mi + 1, r = nxt.edp;
				if (nxt.edp -= mi) {
					nxt.d = abs(nxt.r - cps) + abs(nxt.edp - cps);
					smt::Insert(1, k, nxt);
				}
			} printf("%d %d %d\n", nxt.r, l, r);
		} else {
		//	puts(" case 2");
			if (l) smt::Insert(1, k, {l - 1, 0, l - 1, ub,
					ub - l + 1});
			if (r < k) smt::Insert(1, k, {r + 1, 1, k - r,
					ub, ub + r + 1 - (cps << 1)});
			printf("%d %d %d\n", ub++, l, r);
		}
	} return 0;
}

namespace smt {
	Seg T[kMaxk << 1];
	std::priority_queue<Seg> lef[kMaxk];

	inline int Id(int l, int r) { return l + r | l != r; }
	void Build(int l, int r) {
		if (l == r) return (void)(lef[l].push(kInfSeg));
		int mid = l + r >> 1;
		Build(l, mid); Build(mid + 1, r);
		T[Id(l, r)] = kInfSeg;
	}
	void Insert(int l, int r, const Seg & s) {
		if (l == r) return (void)(lef[l].push(s));
		int mid = l + r >> 1, cur = Id(l, r);
		if (s.len <= mid) Insert(l, mid, s);
		else Insert(mid + 1, r, s);
		Seg ls = l == mid ? lef[l].top() : T[Id(l, mid)],
			rs = mid + 1 == r ?	lef[r].top() : T[Id(mid + 1, r)];
		T[Id(l, r)] = Min(ls, rs);
	}
	Seg Query(int l, int r, int low) {
		if (l >= low) return l == r ? lef[l].top() : T[Id(l, r)];
		int mid = l + r >> 1;
		if (low > mid) return Query(mid + 1, r, low);
		return Min(Query(l, mid, low), Query(mid + 1, r, low));
	}
	void Pop(int l, int r, int p) {
		if (l == r) return (void)(lef[l].pop());
		int mid = l + r >> 1;
		if (p <= mid) Pop(l, mid, p);
		else Pop(mid + 1, r, p);
		Seg ls = l == mid ? lef[l].top() : T[Id(l, mid)],
			rs = mid + 1 == r ?	lef[r].top() : T[Id(mid + 1, r)];
		T[Id(l, r)] = Min(ls, rs);
	}
}
