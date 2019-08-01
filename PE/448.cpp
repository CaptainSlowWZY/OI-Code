#include <cstdio>
#include <algorithm>
#include <map>

#define fir first
#define sec second

typedef long long LL;
typedef std::pair<LL, int> PLi;

const int kLtl = 22000000, kMod = 999999017;

int n0, totp;
int np[kLtl + 10], P[kLtl + 10];
LL pra[kLtl + 10];
std::map<LL, LL> mp;

LL FPow(LL bs, int ex = kMod - 2);
LL Sum(LL n);

int main() {
	pra[1] = 1;
	for (int i = 2; i <= kLtl; i++) {
		if (!np[i]) {
			P[totp++] = i, pra[i] = (i - 1) % kMod; 
		}
		for (int j = 0, d; j < totp &&
				1ll * i * P[j] <= kLtl; j++) {
			np[d = i * P[j]] = 1;
			if (i % P[j] == 0) {
				pra[d] = pra[i] * P[j] % kMod;
				break;
			} pra[d] = pra[i] * (P[j] - 1) % kMod;
		}
	}
	for (int i = 2; i <= kLtl; i++) {
		(pra[i] *= i) %= kMod;
		(pra[i] += pra[i - 1]) %= kMod;
	}

	LL n = 99999999019, ans = 0;
//	n = 25000000;
	for (LL i = 1, j, ls = 0, s; i <= n; i = j + 1) {
		j = n / (n / i);
		s = Sum(j);
		(ans += (s - ls) % kMod * (n / i % kMod) % kMod) %= kMod;
		ls = s;
	}
	ans = (ans * FPow(2) % kMod + n % kMod * FPow(2) % kMod) % kMod;
	(ans += kMod) %= kMod;
	printf("%lld\n", ans);
	return 0;
}

LL FPow(LL bs, int ex) {
	LL res = 1;
	for (; ex; (bs *= bs) %= kMod, ex >>= 1) {
		if (ex & 1) (res *= bs) %= kMod;
	} return res;
}

LL Sum(LL n) {
	if (n <= kLtl) return pra[n];
	if (mp.count(n)) return mp[n];
	LL & res = mp[n];
	res = n % kMod * ((n + 1) % kMod) % kMod * ((2 * n + 1) % kMod) % kMod * FPow(6) % kMod;
	for (LL i = 2, j; i <= n; i = j + 1) {
		j = n / (n / i);
		(res -= (i + j) % kMod * ((j - i + 1) % kMod) % kMod *
			FPow(2) % kMod * Sum(n / i) % kMod) %= kMod;
		if (j >= n) break;
	} return res;
}
