#include <algorithm>
#include <cstdio>
#include <cmath>

#define fir first
#define sec second

typedef long long LL;
typedef std::pair<LL, LL> Pii;

const int kMod = 1e9 + 7;

LL FPow(LL bs, int ex = kMod - 2);
Pii Pos(LL a);
LL Val(const Pii & p);
inline LL Sqr(LL x) { return x * x; }
inline LL Sum(LL a1, LL d, LL k) {
	return (k * (k + 1) / 2 % kMod * (a1 % kMod) % kMod +
			d * (k - 1) % kMod * k % kMod * (k + 1) % kMod *
			FPow(6) % kMod) % kMod;
}
inline void Add(LL & x, LL y) { (x += y) %= kMod; }

LL n;

int main() {
	scanf("%lld", &n);
	
	Pii pn = Pos(n);
	LL ans, sh, sv, sn;
	ans = sh = sv = sn = 0;
	for (LL i = 1; i <= pn.fir && i <= pn.sec; i++) {
		LL a1 = Val(Pii(1, i)),
		   d = i & 1 ? -1 : 1;
		Add(sv, (sn + Sum(a1, d, i - 1)) % kMod);
		a1 = Val(Pii(i, 1)); 
		Add(sh, (sn + Sum(a1, -d, i - 1)) % kMod);
		LL sqr = Sqr(i) % kMod;
		Add(ans, (sv + sh +
			(sn = (1 + sqr) * sqr % kMod * FPow(2) % kMod)) % kMod);
	//	printf(" i %d, sver %lld, shor %lld, sn %lld\n",
	//			i, sv, sh, sn);
	}
//	printf(" ans = %lld\n", (ans + kMod) % kMod);
	if (pn.fir < pn.sec) {
		for (LL i = pn.fir + 1; i <= pn.sec; i++) {
			LL a1 = Val(Pii(1, i)), d = i & 1 ? -1 : 1;
		//	printf(" i %d, a1 %lld, d %lld\n", i, a1, d);
		//	printf("  sum %lld\n",
		//			Sum(a1, d, pn.fir));
			Add(sv, (sn + Sum(a1, d, pn.fir)) % kMod); 
			sn = 0;
		//	printf(" i %d, sver %lld\n", i, sv);
			Add(ans, sv);
		}
	} else {
		for (LL i = pn.sec + 1; i <= pn.fir; i++) {
			LL a1 = Val(Pii(i, 1)), d = i & 1 ? 1 : -1;
			Add(sh, (sn + Sum(a1, d, pn.sec)) % kMod);
			sn = 0;
			Add(ans, sh);
		}
	}
	Add(ans, kMod);
	printf("%lld\n", ans);
	return 0;
}

LL FPow(LL bs, int ex) {
	LL res = 1;
	for (bs %= kMod; ex; (bs *= bs) %= kMod, ex >>= 1) {
		if (ex & 1) (res *= bs) %= kMod;
	} return res;
}

Pii Pos(LL a) {
	LL r = floor(sqrt(a - 0.5)) + 1,
	   m = Sqr(r - 1) + 1 + Sqr(r) >> 1;
	return a <= m ? (r & 1 ? Pii(r, r - m + a) : Pii(r - m + a, r)) :
		(r & 1 ? Pii(r - a + m, r) : Pii(r, r - a + m));
}

LL Val(const Pii & p) {
	LL r = std::max(p.fir, p.sec),
	   m = Sqr(r - 1) + 1 + Sqr(r) >> 1;
	return p.fir == r ? (r & 1 ? m - r + p.sec : m + r - p.sec) :
		(r & 1 ? m + r - p.fir : m - r + p.fir);
}
/*
void TestMan() {
	for (int i = 1; i <= 25; i++) {
		Pii p = Pos(i);
		printf(" %2d (%d, %d)\n", i, p.fir, p.sec);
	}
	for (int i = 1; i <= 5; i++) {
		for (int j = 1; j <= 5; j++) {
			printf("%4lld ", Val(Pii(i, j)));
		}
		putchar('\n');
	}
}*/

/*
 * 9999711114
 * 798696105
 */
