// tab
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
#define gch getchar
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

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			rg char ch = gch();
			while (!isdigit(ch)) ch = gch();
			for (x = 0; isdigit(ch); ch = gch())
				x = (x << 1) + (x << 3) + (ch ^ '0');
		}
	template <typename T>
		void Write(T x) {
			rg int a[20], len = 0;
			for (; x; x /= 10) a[len++] = x % 10;
			while (len) pch(a[--len] ^ '0');
		}
	template <typename T> inline
		void Writeln(T & x) { Write(x); pch('\n'); }
}

const int kR = 2e5, kMaxn = 1e5 + 5;

/* namespace smt {
	Pil T[kR + 5 << 1];
	void Modify(int l, int r, int p, int d);
	Pil Query(int l, int r, int ql, int qr);
} */
template <typename T>
struct Bit {
	T A[kR + 5];
	void add(int p, T x) {
		for (; p <= kR; p += p & -p) A[p] += x;
	}
	T sum(int p) {
		T res = 0;
		for (; p; p &= p - 1) res += A[p];
		return res;
	}
};

int n, q;
int A[kMaxn], cnt[kR + 5];
LL sum[kR + 5];
Bit<int> b1;
Bit<LL> b2;

inline void Modify(int p, int d) {
	b1.add(p, d); b2.add(p, p * d);
}

int main() {
	using fast_io::Read;
//	scanf("%d%d", &n, &q);
	Read(n); Read(q);
	for (int i = 1; i <= n; ++i) {
	//	scanf("%d", A + i);
		Read(A[i]);
	//	smt::Modify(1, kR, A[i], 1);
		Modify(A[i], 1);
		++cnt[A[i]], sum[A[i]] += A[i];
	}
	for (int i = 1; i <= kR; ++i) {
		cnt[i] += cnt[i - 1];
		sum[i] += sum[i - 1];
	}
	int flag = 1;
	for (int op, p, x, y; q--; ) {
	//	scanf("%d", &op);
		Read(op);
		if (op == 1) {
		//	scanf("%d%d", &p, &x);
			Read(p); Read(x);
			flag = 0;
		//	smt::Modify(1, kR, A[p], -1);
		//	smt::Modify(1, kR, A[p] = x, 1);
			Modify(A[p], -1); Modify(A[p] = x, 1);
		} else {
		//	scanf("%d", &y);
			Read(y);
			LL ans = 1ll * n * y, la2 = 0, t2;
			int la1 = 0, t1;
			for (int i = 1, j; i <= y; i = j + 1) {
				j = y / (y / i); // [i, j] : y / i
				if (flag) {
					t1 = cnt[j], t2 = sum[j];
				} else {
					t1 = b1.sum(j); t2 = b2.sum(j);
				}
				ans += (LL)(y / i) * ((LL)t1 - la1 - t2 + la2);
				la1 = t1, la2 = t2;
			}
		//	printf("%lld\n", ans);
			fast_io::Writeln(ans);
		}
	} return 0;
}

/* namespace smt {
	inline int Id(int l, int r) { return l + r | l != r; }
	void Modify(int l, int r, int p, int d) {
		int cur = Id(l, r);
		if (l == r) {
			T[cur].fir += d, T[cur].sec += 1ll * d * l;
			return;
		} int mid = l + r >> 1;
		if (p <= mid) Modify(l, mid, p, d);
		else Modify(mid + 1, r, p, d);
		T[cur] = T[Id(l, mid)] + T[Id(mid + 1, r)];
	}
	Pil Query(int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr)
			return T[Id(l, r)];
		int mid = l + r >> 1;
		if (qr <= mid) return Query(l, mid, ql, qr);
		if (ql > mid) return Query(mid + 1, r, ql, qr);
		return Query(l, mid, ql, qr) + Query(mid + 1, r, ql, qr);
	}
} */
