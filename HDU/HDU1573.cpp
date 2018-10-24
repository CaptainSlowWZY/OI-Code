// HDU 1573
#include <cstdio>

#ifdef LOCAL
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...)
#endif

typedef long long LL;

int R, N, a[15], m[15];

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
	using FastIO::read;
	
	int T;
	for (read(T); T--; ) solve();

	return 0;
}

inline void readAr(int arr[]) {
	for (int i = 0; i < N; i++) FastIO::read(arr[i]);
}

LL extgcd(LL a, LL b, LL & x, LL & y) {
	if (b) {
		LL ret = extgcd(b, a % b, y, x);
		y -= a / b * x;
		return ret;
	}
	else {
		x = 1; y = 0;
		return a;
	}
}

void solve() {
	using FastIO::read;

	read(R), read(N);
	readAr(m), readAr(a);

	// EXCRT
	LL m0 = m[0], a0 = a[0];
	for (int i = 1; i < N; i++) {
		LL x, y, gd = extgcd(m0, m[i], x, y);
		if ((a[i] - a0) % gd) return (void)puts("0");
		debug("gd=%lld, ", gd);
		x *= (a[i] - a0) / gd;
		LL mii = m[i] / gd;
		debug("mii=%lld\n", mii);
		x = (x % mii + mii) % mii;
		a0 += m0 * x, m0 *= mii, a0 %= m0;
	}
	a0 = (a0 + m0) % m0;
	debug("m0=%lld, a0=%lld\n", m0, a0);

	if (a0 >= R) return (void)puts("0");
	if (a0 == 0) printf("%lld\n", R / m0);
	else printf("%lld\n", (R - a0) / m0 + 1);
}

// AC!!!
