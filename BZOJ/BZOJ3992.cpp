// SDOI2015
// Good Problem with NTT
#include <algorithm>
#include <cstdio>

const int kLen = 1 << 14, kMod = 1004535809;

typedef long long LL;
typedef LL Poly[kLen];

int n, m, x, sz, g = 2, deg, invl;
int fac[200], log[8005];
Poly G, bs, res;

LL FPow(LL bs, int ex, int mod) {
	LL res = 1;
	for (; ex; (bs *= bs) %= mod, ex >>= 1) {
		if (ex & 1) (res *= bs) %= mod;
	}
	return res;
}
void Init();
void Mul(Poly, Poly); 

int main() {
	scanf("%d%d%d%d", &n, &m, &x, &sz);

	// find primitive root
	int totf = 0;
	for (int i = 2; i < m - 1; i++) {
		if ((m - 1) % i == 0) fac[totf++] = i;
	}
	for (int fail; ; g++) {
		for (int i = fail = 0; i < totf; i++) {
			if (FPow(g, fac[i], m) == 1) { fail = 1; break; }
		}
		if (!fail) break;
	}

	LL pwg = 1;
	for (int i = 0; i < m - 1; i++, (pwg *= g) %= m) {
		log[pwg] = i;
	}
	x = log[x];

	for (int si; sz--; ) {
		scanf("%d", &si);
		if (si) bs[log[si]] = 1;
	}

	for (deg = 1; deg < (m << 1); deg <<= 1);
	Init();
	res[log[1]] = 1, invl = FPow(deg, kMod - 2, kMod);
	for (; n; Mul(bs, bs), n >>= 1) {
		if (n & 1) Mul(res, bs);
	}

	printf("%lld\n", (res[x] + kMod) % kMod);
	return 0;
}

void Init() {
	LL per = FPow(3, (kMod - 1) / kLen, kMod);
	for (int i = G[0] = 1; i < kLen; i++) {
		G[i] = G[i - 1] * per % kMod;
	}
}

void Dnt(Poly a) {
	for (int i = 0, j = 0; i < deg; i++) {
		if (i > j) std::swap(a[i], a[j]);
		for (int l = deg >> 1; (j ^= l) < l; l >>= 1);
	}
	for (int i = 2, h, d = kLen >> 1; i <= deg;
			i <<= 1, d >>= 1) {
		h = i >> 1;
		for (int j = 0; j < deg; j += i) {
			for (int k = 0, tmp, o = 0; k < h;
					k++, o += d) {
				tmp = a[j + h + k] * G[o] % kMod;
				a[j + h + k] = (a[j + k] - tmp) % kMod;
				(a[j + k] += tmp) %= kMod;
			}
		}
	}
}

void Mul(Poly a0, Poly b0) { // 0 ~ m - 2 
	static Poly a, b;
	for (int i = 0; i < m - 1; i++) a[i] = a0[i];
	for (int i = 0; i < m - 1; i++) b[i] = b0[i];
	for (int i = m - 1; i < deg; i++) a[i] = b[i] = 0;
	Dnt(a), Dnt(b);
	for (int i = 0; i < deg; i++) (a[i] *= b[i]) %= kMod;
	std::reverse(a + 1, a + deg);
	Dnt(a);
	for (int i = deg - 1; i >= 0; i--) (a[i] *= invl) %= kMod;
	for (int i = 0; i < m - 1; i++) {
		a0[i] = (a[i] + a[i + m - 1]) % kMod;
	}
}
