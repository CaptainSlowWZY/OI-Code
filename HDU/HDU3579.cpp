// HDU 3579
#include <cstdio>
#include <utility>

#define fir first
#define sec second

typedef long long LL;
typedef std::pair<int, int> Pii;

int N;
Pii eqt[10];

namespace FastIO {
	template <typename T>
		void read(T & x) {
			x = 0; register char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
}
void solve();

int main() {
	int T;
	for (FastIO::read(T); T--; ) solve();
	return 0;
}

LL extgcd(LL a, LL b, LL &x, LL &y) {
	if (b) {
		LL ret = extgcd(b, a % b, y, x);
		y -= a / b * x;
		return ret;
	}
	else {
		x = 1, y = 0;
		return a;
	}
}

void solve() {
	using FastIO::read;
	static int ks;

	read(N);
	for (int i = 0; i < N; i++) read(eqt[i].fir);
	for (int i = 0; i < N; i++) read(eqt[i].sec);

	LL m0 = eqt[0].fir, a0 = eqt[0].sec;
	for (int i = 1; i < N; i++) {
		LL x, y, gd = extgcd(m0, eqt[i].fir, x, y);
		if ((eqt[i].sec - a0) % gd) return (void)printf("Case %d: -1\n", ++ks);
		x *= (eqt[i].sec - a0) / gd;
		LL mii = eqt[i].fir / gd;
		x = (x % mii + mii) % mii;
		a0 += m0 * x, m0 *= mii, a0 %= m0;
	}
	a0 = (a0 + m0) % m0;
	
	printf("Case %d: %lld\n", ++ks, !a0 ? m0 : a0);
}

// AC!!!
