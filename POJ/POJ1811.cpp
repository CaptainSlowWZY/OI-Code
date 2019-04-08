// Pollard's Rho Algorithm Template
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

typedef long long LL;

int totp;
LL ans, P[10000];

bool MillerRabin(LL p);
void Fac(LL n);

int main() {
	srand(19260817);
	int t;
	LL n;
	for (scanf("%d", &t); t--; ) {
		scanf("%lld", &n);
		if (MillerRabin(n)) {
			puts("Prime");
			continue;
		}
		ans = n;
		Fac(n);
		printf("%lld\n", ans);
	}

	return 0;
}

inline void Add(LL & x, LL y, LL mod) {
	(x += y) >= mod ? (x -= mod) : 0;
}

LL Mul(LL x, LL y, LL mod) {
	LL ret = 0;
	for (x %= mod, y %= mod; y; y >>= 1) {
		y & 1 ? Add(ret, x, mod) : (void)0;
		(x <<= 1) >= mod ? (x -= mod) : 0;
	}
	return ret;
}

LL FPow(LL bs, LL ex, LL mod) {
	LL ret = 1;
	for (bs %= mod; ex; bs = Mul(bs, bs, mod), ex >>= 1) {
		ex & 1 ? ret = Mul(ret, bs, mod) : 0;
	}
	return ret;
}

bool Witness(LL a, LL p) {
	int k = 0;
	LL q = p - 1;
	for (; q & 1 ^ 1; ++k, q >>= 1);
	LL tmp = FPow(a, q, p);
	if (tmp == 1 || tmp == p - 1) return false;
	for (; k--; ) {
		tmp = Mul(tmp, tmp, p);
		if (tmp == p - 1) return false;
	}
	return true;
}

bool MillerRabin(LL p) {
	if (p == 2) return true;
	if (p & 1 ^ 1) return false;	
	for (int i = 0; i < 50; i++) {
		LL a = rand() % (p - 1) + 1;
		if (Witness(a, p)) return false;
	}
	return true;
}

inline LL abs(LL x) { return x < 0 ? -x : x; }

LL PollardsRho(LL n, LL seed) {
	for (LL x = rand() % n, y = x, d, cnt = 1, pow2 = 2; ; ) {
		x = Mul(x, x, n);
		Add(x, seed, n);
		if (y == x) return n;
		d = std::__gcd(abs(y - x), n);
		if (1 < d && d < n) return d;
		if (++cnt == pow2) {
			y = x, pow2 <<= 1;
		}
	}
}

void Fac(LL n) {
	if (MillerRabin(n)) return (void)(ans = std::min(ans, n));
	LL p = n;
	for (; p >= n; ) p = PollardsRho(p, rand() % (n - 1) + 1);
	Fac(p), Fac(n / p);
}
