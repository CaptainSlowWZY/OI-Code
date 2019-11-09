#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <vector>

#define fi first
#define se second
#define pb push_back
#define rg register
#define SZ(_) (int)_.size()

typedef long long LL;
typedef std::pair<int, int> Pii;
typedef std::pair<Pii, int> Ppi;
typedef std::vector<Ppi> Vp;

const int kMaxn = 1e5 + 5;
const Pii kPn(1, 0);

int fea, n, m, q, cntm, ans;
int A[kMaxn];

inline int Add(LL a, int b) { return (a += b) >= m ? a - m : a; }
inline int Sub(LL a, int b) { return (a -= b) < 0 ? a + m : a; }
inline int Mul(int a, int b) { return 1ll * a * b % m; }

namespace fast_io {
	template <typename T> void Read(T & x);
	template <typename T> void Write(T x);
	void Flush();
	void Put(char);
}
namespace smt {
	void Modify(int l, int r, int ql, int qr, const Pii & p);
	void Query(int l, int r, int ql, int qr, int x);
}

int main() {
	using fast_io::Read;
	Read(fea); Read(n); Read(m);
	for (int i = 1; i <= n; ++i) Read(A[i]);
	Read(q);
	int tn = std::min(q, (int)1e5);
	for (int o, l, r, x, y, la = 0; q--; ) {
		Read(o); Read(l); Read(r); Read(x);
		if (fea & 1) { l ^= la, r ^= la; }
		if (o == 1) {
			Read(y); ++cntm;
			smt::Modify(1, tn, l, r, Pii(x, y));
		} else {
			if (fea & 1) x ^= la;
			ans = A[x];
			smt::Query(1, tn, l, r, x);
			assert(ans >= 0);
			fast_io::Write(la = ans); fast_io::Put('\n');
		}
	} fast_io::Flush(); return 0;
}

inline Pii operator+(const Pii & a, const Pii & b) { return Pii(Mul(a.fi, b.fi), Add(Mul(a.se, b.fi), b.se)); }
inline bool CmP(const Ppi & a, const Ppi & b) { return a.se < b.se; }

namespace smt {
	Vp T[kMaxn << 1];

	inline int Id(int l, int r) { return l + r | l != r; }
#define LSON Id(l, mid)
#define RSON Id(mid + 1, r)
	void Merge(Vp & tr, const Vp & L, const Vp & R) {
		int i = 0, j = 0;
//		printf(" L: "); for (int i = 0; i < SZ(L); ++i) printf("*%d+%d, r=%d; ", L[i].fi.fi, L[i].fi.se, L[i].se); puts("");
//		printf(" R: "); for (int i = 0; i < SZ(R); ++i) printf("*%d+%d, r=%d; ", R[i].fi.fi, R[i].fi.se, R[i].se); puts("");
		while (i < SZ(L) && j < SZ(R)) {
			Pii mix = L[i].fi + R[j].fi;
//			printf(" *%d+%d, r=%d MIX *%d+%d, r=%d-> *%d+%d\n", L[i].fi.fi, L[i].fi.se, L[i].se, R[j].fi.fi, R[j].fi.se, R[j].se, mix.fi, mix.se);
			tr.pb(Ppi(mix, std::min(L[i].se, R[j].se)));
			if (L[i].se == R[j].se) ++i, ++j; else if (L[i].se < R[j].se) ++i; else ++j;
		}
	}
	void Modify(int l, int r, int ql, int qr, const Pii & p) {
		int cur = Id(l, r);
		if (l == r) {
			T[cur].pb(Ppi(kPn, ql - 1)); T[cur].pb(Ppi(p, qr));
//			printf(" mod %d, *%d + %d\n", l, p.fi, p.se);
			if (qr < n) T[cur].pb(Ppi(kPn, n));
			return;
		}
		int mid = l + r >> 1;
		if (cntm <= mid) Modify(l, mid, ql, qr, p); else Modify(mid + 1, r, ql, qr, p);
		if (cntm == r) {
			Merge(T[cur], T[LSON], T[RSON]);
//			printf(" see [%d, %d]: ", l, r);
//			for (int i = 0; i < SZ(T[cur]); ++i) printf("*%d+%d, r=%d; ", T[cur][i].fi.fi, T[cur][i].fi.se, T[cur][i].se);
//			puts("");
		}
	}
	void Query(int l, int r, int ql, int qr, int x) {
		if (ql <= l && r <= qr) {
			Vp & cur = T[Id(l, r)];
			Vp::iterator it = std::lower_bound(cur.begin(), cur.end(), Ppi(kPn, x), CmP);
		//	assert(it->fi.fi >= 0 && it->fi.se >= 0);
//			printf(" modify %d ~ %d, r %d\n", l, r, it->se);
//			printf("   *%d + %d\n", it->fi.fi, it->fi.se);
			ans = Add(Mul(ans, it->fi.fi), it->fi.se);
			return;
		} int mid = l + r >> 1;
		if (ql <= mid) Query(l, mid, ql, qr, x);
		if (qr > mid) Query(mid + 1, r, ql, qr, x);
	}
}

namespace fast_io {
	const int kSize = 1 << 15;
	char *ih, *it, ibf[kSize], obf[kSize], *ot = obf;

	char Get() {
		if (ih == it) {
			ih = ibf, it = ih + fread(ibf, 1, kSize, stdin);
			if (ih == it) return EOF;
		} return *ih++;
	}
	template <typename T>
		void Read(T & x) {
			rg char ch = Get(); 
			for (; !isdigit(ch); ch = Get());
			for (x = 0; isdigit(ch); ch = Get()) x = (x << 1) + (x << 3) + (ch ^ '0');
		}
	void Flush() { fwrite(obf, 1, ot - obf, stdout); ot = obf; }
	void Put(char ch) {
		if (ot == obf + kSize) Flush();
		*ot++ = ch;
	}
	template <typename T>
		void Write(T x) {
			static int ar[20];
			rg int len = 0;
			if (!x) return Put('0');
			for (; x; x /= 10) ar[len++] = x % 10;
			while (len) Put('0' ^ ar[--len]);
		}
}
