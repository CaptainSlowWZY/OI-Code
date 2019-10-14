#pragma GCC optimize(2)
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
#include <bitset>

#define fir first
#define sec second
#define pb push_back
#define pch putchar
#define rg register
#define SZ(_) (int)_.size()
#define SORT(_) std::sort(_.begin(), _.end())
#define LB(_, __) std::lower_bound(_.begin(), _.end(), __)
#define UB(_, __) std::upper_bound(_.begin(), _.end(), __)
#ifdef DEBUG
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif

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

const int kR = 1e8, kTs = 1e5;

int n;

namespace fast_io {
	inline char read() {
		static const int IN_LEN = 1000000;
		static char buf[IN_LEN], *s, *t;
		return (s==t?t=(s=buf)+fread(buf,1,IN_LEN,stdin),(s==t?-1:*s++):*s++);
	}

	template <typename T>
		inline void read(T &x) {
			static bool iosig;
			static char c;
			for (iosig=false, c=read(); !isdigit(c); c=read()) {
				if (c == '-') iosig=true;
				if (c == -1) return;
			}
			for (x=0; isdigit(c); c=read()) x=((x+(x<<2))<<1)+(c^'0');
			if (iosig) x=-x;
		}

	const int OUT_LEN = 10000000;
	char obuf[OUT_LEN], *ooh = obuf;

	inline void print(char c) {
		if (ooh == obuf + OUT_LEN) fwrite(obuf, 1, OUT_LEN, stdout), ooh = obuf;
		*ooh++ = c;
	}

	template <typename T>
		inline void print(T x) {
			static int buf[30], cnt;
			if (x == 0) print('0');
			else {
				if (x < 0) print('-'), x = -x;
				for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + 48;
				while (cnt) print((char)buf[cnt--]);
			}
		}

	inline void flush() { fwrite(obuf, 1, ooh - obuf, stdout); }
}

namespace solver1 {
	void Solve();
}
namespace solver2 {
	void Solve();
}

int main() {
	fast_io::read(n);
//	scanf("%d", &n);
	if (n <= kTs)
		solver1::Solve();
	else
		solver2::Solve();
	return 0;
}

namespace solver1 {
	Si S;

	void Solve() {
		S.insert(0); S.insert(kR + 1);
		for (int o, x; n--; ) {
			fast_io::read(o); fast_io::read(x);
		//	scanf("%d%d", &o, &x);
			if (o == 1) S.insert(x);
			if (o == 2) {
				auto it = S.lower_bound(x);
				--it;
				fast_io::print(*it);
				fast_io::print('\n');
			//	printf("%d\n", *it);
			}
			if (o == 3) {
				auto it = S.upper_bound(x);
				fast_io::print(*it);
				fast_io::print('\n');
			//	printf("%d\n", *it);
			}
		} fast_io::flush();
	}
}

namespace solver2 {
	int v[kR + 10];

#define CHECK(_) if (v[i + _]) { flag = 1; fast_io::print(i + _); break; }

	void Solve() {
		v[0] = v[kR + 1] = 1;
		for (int o, x; n--; ) {
		//	scanf("%d%d", &o, &x);
			fast_io::read(o); fast_io::read(x);
			if (o == 1) v[x] = 1;
			int flag = 0;
			if (o == 3) {
				for (int i = x + 1; i <= kR + 1; i += 4) {
					CHECK(0)
					CHECK(1)
					CHECK(2)
					CHECK(3)
				} fast_io::print('\n');
				assert(flag);
			}
			if (o == 2) {
				int i;
				for (i = x - 1; i >= 3; i -= 4) {
					CHECK(0)
					CHECK(-1)
					CHECK(-2)
					CHECK(-3)
				}
				if (!flag) {
					for (; i >= 0; --i) CHECK(0)
				} fast_io::print('\n');
			//	assert(flag);
			}
		} fast_io::flush();
	}
}
