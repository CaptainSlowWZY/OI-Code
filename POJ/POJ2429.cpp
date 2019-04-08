
#include <cstdio>
#include <cstdlib>
#include <algorithm>

typedef long long LL;

int totp, cnt[1000];
LL P[1000], pow[1000];

LL FPow(LL bs, LL ex, LL mod);
bool MillerRabin(LL n);
void Fac(LL n);

int main() {
	srand(19260817);
	for (LL gcd, lcm, t; ~scanf("%lld%lld", &gcd, &lcm); ) {
		if (gcd == lcm) {
			printf("%lld %lld\n", gcd, gcd);
			continue;
		}
		totp = 0;
		Fac(t = lcm / gcd);

		std::sort(P, P + totp);
		cnt[0] = 1;
		int ptr = 1;
		for (int i = 1; i < totp; i++) {
			if (P[i] ^ P[ptr - 1]) {
				cnt[ptr] = 1;
				P[ptr++] = P[i];
			} else ++cnt[ptr - 1];
		}
		totp = ptr;
		for (int i = 0; i < totp; i++) {
			pow[i] = FPow(P[i], cnt[i], t);
		}

		LL ans = -1, a, b;
		for (int mask = (1 << totp) - 1; mask >= 0; --mask) {
			LL prdc1 = 1, prdc2 = 1;
			for (int i = 0; i < totp; i++) {
				mask >> i & 1 ? prdc1 *= pow[i] :
								prdc2 *= pow[i];
			}
			if (ans == -1 || prdc1 + prdc2 < ans) {
				ans = prdc1 + prdc2;
				a = prdc1, b = prdc2;
			}
		}
		if (a > b) std::swap(a, b);
		a *= gcd, b *= gcd;
		printf("%lld %lld\n", a, b);
	}
	return 0;
}

inline void Add(LL & x, LL y, LL mod) {
	(x += y) >= mod ? (x -= mod) : 0;
}

LL Mul(LL a, LL b, LL mod) {
	LL ret = 0;
	for (a %= mod, b %= mod; b; b >>= 1) {
		b & 1 ? Add(ret, a, mod) : (void)0;
		(a <<= 1) >= mod ? (a -= mod) : 0;
	}
	return ret;
}

LL FPow(LL bs, LL ex, LL mod) {
	LL ret = 1;
	for (; ex; bs = Mul(bs, bs, mod), ex >>= 1) {
		ex & 1 ? ret = Mul(ret, bs, mod) : 0;
	}
	return ret;
}

bool Witness(LL a, LL n) {
	int k = 0;
	LL q = n - 1;
	for (; q & 1 ^ 1; ++k, q >>= 1);
	LL tmp = FPow(a, q, n);
	if (tmp == 1 || tmp == n - 1) return false;
	for (; k--; ) {
		tmp = Mul(tmp, tmp, n);
		if (tmp == n - 1) return false;
	}
	return true;
}

bool MillerRabin(LL n) {
	if (n == 2) return true;
	if (n & 1 ^ 1) return false;
	for (int i = 0; i < 50; i++) {
		LL a = rand() % (n - 1) + 1;
		if (Witness(a, n)) return false;
	}
	return true;
}

inline LL abs(LL x) { return x < 0 ? -x : x; }

LL PollardsRho(LL n, LL cd) {
	for (LL x = rand() % n, y = x, d, cnt = 1, pow2 = 2; ; ) {
		x = Mul(x, x, n);
		Add(x, cd, n);
		if (y == x) return n;
		d = std::__gcd(abs(y - x), n);
		if (1 < d && d < n) return d;
		if (++cnt == pow2) {
			y = x, pow2 <<= 1;
		}
	}
}

void Fac(LL n) {
	if (MillerRabin(n)) return (void)(P[totp++] = n);
	LL p = n;
	for (; p >= n; p = PollardsRho(p, rand() % (n - 1) + 1));
	Fac(p), Fac(n / p);
}
