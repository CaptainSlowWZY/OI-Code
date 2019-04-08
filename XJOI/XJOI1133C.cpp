#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>
 
typedef long long LL;
 
LL n, P[1000];
int k, MOD, totp, cnt[1000];
 
inline void Add(LL & x, LL y, LL mod = MOD) {
	(x += y) >= mod ? (x -= mod) : 0;
}
LL FPow(LL bs, LL ex = MOD - 2);
void Fac(LL n);

int main() {
	srand(time(NULL));
    int t;
    for (scanf("%d", &t); t--; totp = 0) {
        scanf("%lld%d%d", &n, &k, &MOD);
		if (n == 1) {
			puts("1");
			continue;
		}

		Fac(n);
		std::sort(P, P + totp);
		cnt[0] = 1;
		int ptr = 0;
		for (int i = 1; i < totp; i++) {
			if (P[i] ^ P[ptr]) {
				P[++ptr] = P[i];
				cnt[ptr] = 1;
			} else ++cnt[ptr];
		}
		totp = ptr + 1;

        LL ans = 1, phin = n % MOD;
        for (int i = 0; i < totp; i++) {
            LL p = P[i] % MOD, t = cnt[i], 
			   cur = (FPow(p, (t - 1) * k) * FPow(p - 1, k) % MOD +
                	  FPow(p, 2 * t - 1) * (p - 1) % MOD) % MOD;
            if (t > 1) {
                LL tmp = FPow(p, 2 - k);
                Add(cur, FPow(p, t * k - k - 1) *
                 FPow(p - 1, k + 1) % MOD *
                 ((tmp - FPow(p, t * (2 - k))) % MOD) % MOD *
                 FPow(1 - tmp) % MOD);
            }
            (ans *= cur) %= MOD;
            (phin *= LL(p - 1) * FPow(p) % MOD) %= MOD;
        }
        ans = (ans + FPow(phin, k)) % MOD * (n % MOD) % MOD * FPow(2) % MOD;
		Add(ans, MOD);
		printf("%lld\n", ans);
    }
}

LL Mul(LL x, LL y, LL mod) {
	LL ret = 0;
	for (x %= mod, y %= mod; y; y >>= 1) {
		y & 1 ? Add(ret, x, mod) : (void)0;
		(x <<= 1) >= mod ? (x -= mod) : 0;
	}
	return ret;
}

LL FPow(LL bs, LL ex) {
//	assert(ex >= 0);
	ex = (ex % (MOD - 1) + MOD - 1) % (MOD - 1);
	LL ret = 1;
	for (bs %= MOD; ex; (bs *= bs) %= MOD, ex >>= 1) {
		ex & 1 ? (ret *= bs) %= MOD : 0;
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
	if (MillerRabin(n)) return (void)(P[totp++] = n);
	LL p = n;
	for (; p >= n; ) p = PollardsRho(p, rand() % (n - 1) + 1);
	Fac(p), Fac(n / p);
}
